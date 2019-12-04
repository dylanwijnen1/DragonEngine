#pragma once

#include <Dragon/Config.h>

#include <Dragon/Generic/Math.h>

#include <Dragon/Graphics/Renderable.h>
#include <Dragon/Graphics/Texture.h>

#include <EASTL/vector.h>

namespace dragon
{
	using TileID = unsigned int;
	constexpr TileID kInvalidTile = eastl::numeric_limits<TileID>::max();

	/// <summary>
	/// Wrapper for the actual tiles.
	/// </summary>
	struct TileLayer
	{
		using Tiles = eastl::vector<TileID>;
		Tiles m_tiles;

		TileLayer() = default;

		TileLayer(Vector2u size)
			: m_tiles((size_t)size.x * size.y, kInvalidTile)
		{}

		~TileLayer() = default;

		// Copying is slow.
		TileLayer(const TileLayer&) = delete;
		TileLayer& operator=(const TileLayer&) = delete;

		// Move is ok.
		TileLayer(TileLayer&&) = default;
		TileLayer& operator=(TileLayer&&) = default;
	};

	/// <summary>
	/// Very simplified version of a tilemap.
	/// 
	/// TODO: Add Textures (Map TileID to TileSets)
	/// TODO: Add loading functionality of tilemap definitions.
	/// 
	/// Notes: A Tilemap will always have one layer.
	/// </summary>
	class Tilemap 
		: public Renderable
		// If the TileDataType is set, Extend from _TileDataMap
		//, eastl::conditional_t<eastl::is_same_v<TileData, std::nullptr_t>, internal::_NullTileDataMap, internal::_TileDataMap<TileData>>
	{
		Vector2u m_size;
		Vector2f m_tileSize;

		// TODO: Find better suited container if possible.
		using TileLayers = eastl::vector<TileLayer>;
		TileLayers m_layers;

		/// <summary>
		/// Renderer Implementation.
		/// </summary>
		class TilemapRenderer* m_pTileRenderer;

		Texture m_tileSet;

	public:

		Tilemap()
			: m_pTileRenderer(nullptr)
		{}

		// Copying is very slow.
		Tilemap(const Tilemap&) = delete;
		Tilemap& operator=(const Tilemap&) = delete;

		// Moving is ok.
		Tilemap(Tilemap&&) = default;
		Tilemap& operator=(Tilemap&&) = default;

		/// <summary>
		/// A Tilemap must be initialized.
		/// </summary>
		/// <param name="size"></param>
		/// <param name="tileSize"></param>
		/// <returns></returns>
		virtual bool Init(Vector2u size, Vector2f tileSize);

		bool LoadTileset(eastl::string path);

		// When handling multi tilesets. Return the texture associated with the tileid.
		//Texture GetTileTexture(TileID id);

		const Texture* GetTileSet() const { return &m_tileSet; }

		// TODO: Ability to load multiple tilesets.

#pragma region Layer

		void AddLayer() { m_layers.emplace_back(m_size); }

		bool RemoveLayer(size_t index);

		size_t LayerCount() const { return m_layers.size(); }

		/// <summary>
		/// Fills the layer with a specific tile.
		/// </summary>
		/// <param name="id"></param>
		void FillLayer(TileID id) { FillLayer(kInvalidTile, id); }
		void FillLayer(size_t layerIndex, TileID id);

#pragma endregion

		Vector2u GetSize() const { return m_size; }
		Vector2f GetTileSize() const { return m_tileSize; }

		// TODO: Possible need to swap layers for layer ordering at runtime.
		void SwapLayers(size_t from, size_t to)
		{
			eastl::swap(m_layers[from], m_layers[to]);
		}

		// Inherited via Renderable
		virtual void Render(RenderTarget& target) override;

#pragma region Utils

		size_t IndexFromPosition(unsigned int x, unsigned int y) const { return ((size_t)y * m_size.x) + x; }
		Vector2u PositionFromIndex(size_t index) const;

		Vector2u WorldToMapCoordinates(Vector2f worldCoords) const;
		Vector2f MapToWorldCoordinates(Vector2u mapCoords) const;

		/// <summary>
		/// Anything outside of the bounds will be ignored.
		/// E.g : If worldBounds can view outside of the bounds of the tilemap we ignore these values.
		/// </summary>
		/// <param name="worldBounds"></param>
		/// <returns></returns>
		RectU WorldToMapBounds(RectF worldBounds) const;

		/// <summary>
		/// Determine wether or not the given position is within bounds of the map.
		/// </summary>
		/// <param name="x">X-Coordinate</param>
		/// <param name="y">Y-Coordinate</param>
		bool WithinBounds(unsigned int x, unsigned int y) const;
		bool WithinBounds(Vector2u pos) const { WithinBounds(pos.x, pos.y); }
		bool WithinBounds(size_t index) const { return (size_t)m_size.x * m_size.y; }

#pragma endregion

#pragma region Tile Manipulation

		/// <summary>
		/// Set the tile of the default layer.
		/// </summary>
		/// <param name="x">X-Coordinate</param>
		/// <param name="y">Y-Coordinate</param>
		/// <param name="id">The tile to set.</param>
		void SetTile(unsigned int x, unsigned int y, TileID id) { SetTile(0, x, y, id); }
		void SetTile(Vector2u mapCoords, TileID id) { SetTile(0, mapCoords.x, mapCoords.y, id); }

		void SetTileAtIndex(size_t index, TileID id) { SetTileAtIndex(0, index, id); }

		/// <summary>
		/// Get the tile of the default layer.
		/// </summary>
		/// <param name="x">X-Coordinate</param>
		/// <param name="y">Y-Coordinate</param>
		/// <returns></returns>
		TileID GetTile(unsigned int x, unsigned int y) const { return GetTile(0, x, y); }
		TileID GetTile(Vector2u mapCoords) const { return GetTile(0, mapCoords.x, mapCoords.y); }

		TileID GetTileAtIndex(size_t index) const { return GetTileAtIndex(0, index); }

		/// <summary>
		/// Set a tile of a specific layer.
		/// </summary>
		/// <param name="layerName"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="id"></param>
		void SetTile(size_t layerIndex, unsigned int x, unsigned int y, TileID id);
		void SetTile(size_t layerIndex, Vector2u mapCoords, TileID id) { SetTile(layerIndex, mapCoords.x, mapCoords.y, id); }

		void SetTileAtIndex(size_t layerIndex, size_t index, TileID id);
		
		TileID GetTile(size_t layerIndex, unsigned int x, unsigned int y) const;
		TileID GetTile(size_t layerIndex, Vector2u mapCoords) const { return GetTile(layerIndex, mapCoords.x, mapCoords.y); }

		TileID GetTileAtIndex(size_t layerIndex, size_t index) const;

#pragma endregion

	private:
		TilemapRenderer* GetTileRendererImpl() const;
	};


	template<typename TileData>
	class DataTilemap : public Tilemap
	{
		using TileDataVector = eastl::vector<TileData*>;
		TileDataVector m_tileData;

	public:

		virtual bool Init(Vector2u size, Vector2f tileSize) final override
		{
			m_tileData.resize((size_t)size.x * size.y, nullptr);
			return Tilemap::Init(size, tileSize);
		}

		const TileData& GetTileDataAtIndex(size_t tileIndex) const
		{
			assert(WithinBounds(tileIndex));
			return *m_tileData[tileIndex];
		}

		const TileData& GetTileData(unsigned int x, unsigned int y) const
		{
			return GetTileDataAtIndex(IndexFromPosition(x, y));
		}

		TileData& GetTileDataAtIndex(size_t tileIndex)
		{
			assert(WithinBounds(tileIndex));
			return *m_tileData[tileIndex];
		}

		TileData& GetTileData(unsigned int x, unsigned int y)
		{
			return GetTileDataAtIndex(IndexFromPosition(x, y));
		}

		TileData* GetTileDataSafe(unsigned int x, unsigned int y) const { return GetTileDataSafeAtIndex(IndexFromPosition(x, y)); }
		TileData* GetTileDataSafeAtIndex(size_t tileIndex) const { return m_tileData[tileIndex]; }
	};

}