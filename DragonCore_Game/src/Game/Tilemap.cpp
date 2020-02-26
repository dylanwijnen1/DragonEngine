#include "Tilemap.h"

#include <SFML/Graphics.hpp>
#include <EASTL/unordered_set.h>

#include <Dragon/Generic/Math/MathFunctions.h>
#include <Dragon/Debug.h>

bool Tilemap::Init(const char* pFile, Vector2 tileSize)
{
	sf::Image image;

	if (!image.loadFromFile(pFile))
		return false;

	auto size = image.getSize();
	Resize(Vector2(size.x, size.y));
	m_tileSize = tileSize;

	// Initialize all the id's
	for (int x = 0; x < (int)size.x; ++x)
	{
		for (int y = 0; y < (int)size.y; ++y)
		{
			TileID id = image.getPixel(x, y).toInteger();
			SetTile(x, y, id);

			size_t offset = GetTileIndex(x, y) * 4;

			// Setup the vertices.
			sf::Vector2f corners[] =
			{
				sf::Vector2f((float)x * tileSize.x, (float)y * tileSize.y), // Top Left
				sf::Vector2f(((float)x + 1) * tileSize.x, (float)y * tileSize.y), // Top Right
				sf::Vector2f(((float)x + 1) * tileSize.x, ((float)y + 1) * tileSize.y), // Bottom Right
				sf::Vector2f((float)x * tileSize.x, ((float)y + 1) * tileSize.y), // Bottom Left
			};

			m_vertices[offset].position = corners[0];
			m_vertices[offset + 1].position = corners[1];
			m_vertices[offset + 2].position = corners[2];
			m_vertices[offset + 3].position = corners[3];
		}
	}

	return true;
}

bool Tilemap::WithinBounds(int x, int y) const
{
	return !(x < 0 || y < 0 || x > m_size.x || y > m_size.y);
}

size_t Tilemap::GetTileIndex(int x, int y) const
{
	if (!WithinBounds(x, y))
		return kInvalidTileIndex;

	return x + (y * (size_t)m_size.x);
}

Vector2 Tilemap::GetTilePosition(size_t index) const
{
	int x = (int)index % m_size.x;
	int y = (int)index / m_size.x;

	x = dragon::math::Clamp(x, 0, m_size.x);
	y = dragon::math::Clamp(y, 0, m_size.y);

	return Vector2(x, y);
}

Vector2 Tilemap::WorldToTilePosition(Vector2f position) const
{
	Vector2 tilePos;
	tilePos.x = (int)position.x - ((int)position.x % m_tileSize.x);
	tilePos.y = (int)position.y - ((int)position.y % m_tileSize.y);
	tilePos.x /= m_tileSize.x;
	tilePos.y /= m_tileSize.y;
	return tilePos;
}

Vector2f Tilemap::TileToWorldPosition(Vector2 tilePos) const
{
	tilePos.x *= (float)m_tileSize.x;
	tilePos.y *= (float)m_tileSize.y;
	return Vector2f((float)tilePos.x, (float)tilePos.y);
}

Vector2f Tilemap::TileToWorldPositionCenter(Vector2 tilePos) const
{
	Vector2f center = TileToWorldPosition(tilePos);
	center.x += (float)m_tileSize.x / 2.0f;
	center.y += (float)m_tileSize.y / 2.0f;
	return center;
}

void Tilemap::SetTile(size_t index, TileID id)
{
	if (!WithinBounds(index))
	{
		DWARN("Tilemap::SetTile, Invalid Index: %i", index);
		return;
	}

	size_t offset = index * 4;

	m_vertices[offset].color = sf::Color(id);
	m_vertices[offset + 1].color = sf::Color(id);
	m_vertices[offset + 2].color = sf::Color(id);
	m_vertices[offset + 3].color = sf::Color(id);

	m_tiles[index] = id;
}

TileID Tilemap::GetTile(size_t index) const
{
	if(index >= 0 && index < m_tiles.size())
		return m_tiles[index];

	return kInvalidTileID;
}

void Tilemap::Draw(sf::RenderTarget* pSfTarget)
{
	pSfTarget->draw(m_vertices);
}

void Tilemap::Resize(Vector2 size)
{
	const size_t count = (size_t)4 * size.x * size.y;

	m_size = size;
	m_vertices.resize(count);
	m_tiles.resize(count, (TileID)0);
}
