#pragma once

#include <Game/Vector2.h>

#include <SFML/Graphics/VertexArray.hpp>

#include <EASTL/vector.h>

namespace sf
{
	class RenderTarget;
}

using TileID = uint32_t;

class Tilemap
{
	sf::VertexArray m_vertices;

	using Tiles = eastl::vector<TileID>;
	Tiles m_tiles;

	Vector2 m_size;
	Vector2 m_tileSize;

public:

	inline static constexpr size_t kInvalidTileIndex = (size_t)0 - 1;
	inline static constexpr TileID kInvalidTileID = (TileID)0 - 1;

	Tilemap()
		: m_vertices(sf::PrimitiveType::Quads)
		, m_size(0, 0)
	{}

	bool Init(const char* pFile, Vector2 tileSize);

	bool WithinBounds(int x, int y) const;
	bool WithinBounds(Vector2 pos) const { return WithinBounds(pos.x, pos.y); }
	bool WithinBounds(size_t index) const { return index >= 0 && index < m_tiles.size(); }

	size_t GetTileIndex(Vector2 pos) const { return GetTileIndex(pos.x, pos.y); }
	size_t GetTileIndex(int x, int y) const;


	Vector2 GetTilePosition(size_t index) const;

	Vector2 WorldToTilePosition(Vector2f position);

	void SetTile(size_t index, TileID id);
	TileID GetTile(size_t index) const;

	void SetTile(int x, int y, TileID id) { SetTile(GetTileIndex(x, y), id); }
	TileID GetTile(int x, int y) const { return GetTile(GetTileIndex(x, y)); }

	void Draw(sf::RenderTarget* pSfTarget);

private:

	void Resize(Vector2 size);
};