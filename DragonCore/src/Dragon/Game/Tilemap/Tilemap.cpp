#include "Tilemap.h"

#include <Dragon/Config.h>
#include <Dragon/Application/Debugging/Debug.h>

// Determine the TilemapRenderer Implementation

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN
	#include <Platform/SFML/Game/Tilemap/SfmlTilemapRenderer.h>
	namespace dragon
	{
		using TileRendererImpl = SfmlTilemapRenderer;
	}
#endif

namespace dragon
{

	Tilemap::~Tilemap()
	{
		delete m_pTileRenderer;
		m_pTileRenderer = nullptr;
	}

	bool Tilemap::Init(Vector2u size, Vector2f tileSize)
	{
		return Init(size, tileSize, Vector2u((unsigned int)tileSize.x, (unsigned int)tileSize.y));
	}

	bool Tilemap::Init(Vector2u size, Vector2f tileSize, Vector2u tilesetTileSize)
	{
		// Create the first layer.
		m_layers.emplace_back(size);

		m_size = size;
		m_tileSize = tileSize;
		m_tilesetTileSize = tilesetTileSize;

		// Get the tile renderer implementation.
		m_pTileRenderer = GetTileRendererImpl();

		// We do not care wether or not the tile renderer was initialized.
		// The tilemap can be initialized in a Renderless environment.
		return true;
	}

	bool Tilemap::LoadTileset(eastl::string path)
	{
		return m_tileset.LoadFromFile(path.c_str());
	}

	bool Tilemap::RemoveLayer(size_t index)
	{
		if (index > m_layers.size() - 1)
		{
			DWARN("Attempting to remove a layer out of bounds.");
			return false;
		}

		if (!(m_layers.size() > 1))
		{
			DWARN("Attempting to remove the last layer in Tilemap.");
			return false;
		}

		m_layers.erase(m_layers.begin() + index);
		return true;
	}

	void Tilemap::FillLayer(size_t layerIndex, TileID id)
	{
		if (layerIndex < m_layers.size())
		{
			auto& tiles = m_layers[0].m_tiles;
			eastl::fill(tiles.begin(), tiles.end(), id);
		}
	}

	void Tilemap::Render(RenderTarget& target)
	{
		// We do not have a tile renderer. This could be expected. This depends if a renderskin was selected or not.
#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		if (!m_pTileRenderer)
		{
			DWARN("Tilemap::Render() TilemapRenderer is invalid. Was the Tilemap Initialized ?");
			return;
		}
#elif
		return;
#endif

		for (const TileLayer& layer : m_layers)
		{
			m_pTileRenderer->Render(target, *this, layer);
		}
	}

	Vector2 Tilemap::PositionFromIndex(int index) const
	{
		Vector2 pos;
		pos.x = index % m_size.x;
		pos.y = index / m_size.y;
		return pos;
	}

	bool Tilemap::WithinBounds(int x, int y) const
	{
		return !(x < 0 || x > (int)m_size.x - 1 || y < 0 || y > (int)m_size.y - 1);
	}

	Vector2 Tilemap::WorldToMapCoordinates(Vector2f worldCoords) const
	{
		Vector2f coords = worldCoords / m_tileSize;
		coords.x = dragon::math::Clamp(coords.x, 0.f, (float)m_size.x - 1);
		coords.y = dragon::math::Clamp(coords.y, 0.f, (float)m_size.y - 1);
		return 
		{ 
			(int)dragon::math::Floor(coords.x),
			(int)dragon::math::Floor(coords.y)
		};
	}

	Vector2f Tilemap::MapToWorldCoordinates(Vector2 mapCoords) const
	{
		return static_cast<Vector2f>(mapCoords) * m_tileSize;
	}

	Rect Tilemap::WorldToMapBounds(RectF worldBounds) const
	{
		Vector2 pos = WorldToMapCoordinates({ worldBounds.x, worldBounds.y });
		Vector2 size = WorldToMapCoordinates({ worldBounds.width, worldBounds.height });
		return { pos, size };
	}

	void Tilemap::SetTile(size_t layerIndex, unsigned int x, unsigned int y, TileID id)
	{
		// Check if the layer exists and if the position is within bounds of the tilemap.
		if (layerIndex < m_layers.size() && WithinBounds(x, y))
		{
			// Set the tile.
			m_layers[layerIndex].m_tiles[IndexFromPosition(x, y)] = id;
		}
	}

	void Tilemap::SetTileAtIndex(size_t layerIndex, size_t index, TileID id)
	{
		// Check if the layer exists and if the position is within bounds of the tilemap.
		if (layerIndex < m_layers.size() && index < (size_t)m_size.x * m_size.y)
		{
			// Set the tile.
			m_layers[layerIndex].m_tiles[index] = id;
		}
	}

	TileID Tilemap::GetTile(size_t layerIndex, unsigned int x, unsigned int y) const
	{
		// Check if the layer exists and if the position is within bounds of the tilemap.
		if (layerIndex < m_layers.size() && WithinBounds(x, y))
		{
			// Set the tile.
			return m_layers[layerIndex].m_tiles[IndexFromPosition(x, y)];
		}

		return kInvalidTile;
	}

	TileID Tilemap::GetTileAtIndex(size_t layerIndex, size_t index) const
	{
		// Check if the layer exists and if the position is within bounds of the tilemap.
		if (layerIndex < m_layers.size() && index < (size_t)(m_size.x * m_size.y))
		{
			// Set the tile.
			return m_layers[layerIndex].m_tiles[index];
		}

		return kInvalidTile;
	}

	TilemapRenderer* Tilemap::GetTileRendererImpl() const
	{
#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		return new TileRendererImpl();
#elif
		return nullptr;
#endif
	}

}