#pragma once

#include <Dragon/Generic/Math.h>

#include <Dragon/Graphics/Renderable.h>

#include <Dragon/Graphics/Texture.h>

#include <EASTL/vector.h>

namespace dragon
{
	using TileID = unsigned int;
	constexpr TileID kInvalidTile = 0;

	/// <summary>
	/// Wrapper for the actual tiles.
	/// </summary>
	struct TileLayer
	{
		using Tiles = eastl::vector<TileID>;
		Tiles m_tiles;

		TileLayer() = default;

		TileLayer(Vector2u size)
			: m_tiles((size_t)(size.x * size.y), kInvalidTile)
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
	class Tilemap : public Renderable
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
		~Tilemap() = default;

		// Copying is very slow.
		Tilemap(const Tilemap&) = delete;
		Tilemap& operator=(const Tilemap&) = delete;

		// Moving is ok.
		Tilemap(Tilemap&&) = default;
		Tilemap& operator=(Tilemap&&) = default;



		/// <summary>
		/// A Tilemap must be initialized in order to work.
		/// </summary>
		/// <param name="size"></param>
		/// <param name="tileSize"></param>
		/// <returns></returns>
		bool Init(Vector2u size, Vector2f tileSize);
		bool LoadTileset(eastl::string path);

#pragma region Layer

		void AddLayer() { m_layers.emplace_back(m_size); }
		bool RemoveLayer(size_t index);
		size_t LayerCount() const { return m_layers.size(); }

		
		/// <summary>
		/// Fills the layer with a specific tile.
		/// </summary>
		/// <param name="id"></param>
		void FillLayer(TileID id) { FillLayer(0, id); }
		void FillLayer(size_t layerIndex, TileID id);

#pragma endregion

		Vector2u GetSize() const { return m_size; }
		Vector2f GetTileSize() const { return m_tileSize; }

		// TODO: Possible need to swap layers for layer ordering at runtime.
		//void SwapLayers(size_t from, size_t to);

		// Inherited via Renderable
		virtual void Render(RenderTarget& target) override;

#pragma region Utils

		size_t IndexFromPosition(unsigned int x, unsigned int y) const { return (y * m_size.x) + x; }
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

		// When handling multi tilesets. Return the texture associated with the tileid.
		//Texture GetTileTexture(TileID id);

		const Texture* GetTileSet() const { return &m_tileSet; }

	private:
		TilemapRenderer* GetTileRendererImpl() const;
	};

}