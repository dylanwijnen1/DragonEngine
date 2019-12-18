#include "SfmlTilemapRenderer.h"

#include <Dragon/Graphics/RenderTarget.h>
#include <Dragon/Graphics/Texture.h>

#include <Dragon/Game/Tilemap/Tilemap.h>

#include <Platform/SFML/SfmlHelpers.h>

#include <SFML/Graphics.hpp>


namespace dragon
{
	// TODO: There's still a few bugs in handling the camera changes in zoom.
	//		 It took too long to debug so this will have to happen another time.
	//		 For now draw the entire map.

	/*
	void SfmlTilemapRenderer::Render(RenderTarget& target, const Tilemap& tilemap, const TileLayer& layer)
	{
		Camera camera = target.GetCamera();

		sf::RenderTarget* pTarget = static_cast<sf::RenderTarget*>(target.GetNativeTarget());
		if (pTarget)
		{
			Vector2f tileSize = tilemap.GetTileSize();


			// Calculate the how much of the tilemap we can currently see through the camera.
			RectU mapBounds = tilemap.WorldToMapBounds(camera.GetViewBounds());

			// Always extend by 1 tile so that if we are just below half way of the tile we still draw the tile.
			if (mapBounds.pos.x > 0)
				mapBounds.pos.x -= 1;
			if (mapBounds.pos.y > 0)
				mapBounds.pos.y -= 1;

			mapBounds.size.x += 1;
			mapBounds.size.y += 1;
			

			// Expecting an overflow cancel draw.
			if (mapBounds.pos.x > mapBounds.size.x || mapBounds.pos.y > mapBounds.size.y)
				return;


			const unsigned int width =  mapBounds.size.x - mapBounds.pos.x;
			const unsigned int height = mapBounds.size.y - mapBounds.pos.y;
			const size_t tileCount = width * height;
			
			// Create a vertex array.
			sf::VertexArray vertices;
			vertices.setPrimitiveType(sf::Quads);
			vertices.resize(tileCount * 4);
			
			// Render the tiles we are currently able to see.
			for (unsigned int x = 0; x < width; ++x)
			{
				for (unsigned int y = 0; y < height; ++y)
				{
					sf::Vertex* quad = &vertices[((size_t)x + (size_t)y * (size_t)width) * 4];

					float tileX = (float)mapBounds.pos.x + x;
					float tileY = (float)mapBounds.pos.y + y;

					// define its 4 corners
					quad[0].position = sf::Vector2f(tileX * (float)tileSize.x, tileY * (float)tileSize.y);
					quad[1].position = sf::Vector2f((tileX + 1) * (float)tileSize.x, tileY * (float)tileSize.y);
					quad[2].position = sf::Vector2f((tileX + 1) * (float)tileSize.x, (tileY + 1) * (float)tileSize.y);
					quad[3].position = sf::Vector2f(tileX * (float)tileSize.x, (tileY + 1) * (float)tileSize.y);

					// TODO: Color could become a TileData property.
					quad[0].color = sf::Convert(Colors::Green);
					quad[1].color = sf::Convert(Colors::Red);
					quad[2].color = sf::Convert(Colors::Blue);
					quad[3].color = sf::Convert(Colors::Yellow);

					// TODO: We'll want to do texturing at some point.
					//quad[0].texCoords = sf::Vector2f(tu * (float)m_tileSize.x, tv * (float)m_tileSize.y);
					//quad[1].texCoords = sf::Vector2f((tu + 1) * (float)m_tileSize.x, tv * (float)m_tileSize.y);
					//quad[2].texCoords = sf::Vector2f((tu + 1) * (float)m_tileSize.x, (tv + 1) * (float)m_tileSize.y);
					//quad[3].texCoords = sf::Vector2f(tu * (float)m_tileSize.x, (tv + 1) * (float)m_tileSize.y);
				}
			}

			pTarget->draw(vertices);
		}
	}
	*/

	void SfmlTilemapRenderer::Render(RenderTarget& target, const Tilemap& tilemap, const TileLayer& layer)
	{
		sf::RenderTarget* pTarget = static_cast<sf::RenderTarget*>(target.GetNativeTarget());
		if (pTarget)
		{

			Vector2u mapSize = tilemap.GetSize();
			Vector2f tileSize = tilemap.GetTileSize();

			const Texture* pTileset = tilemap.GetTileset();
			Vector2f texSize = pTileset->GetSize();
			Vector2u tilesetTileSize = tilemap.GetTilesetTileSize();

			Vector2f tiling = { (texSize.x / (float)tilesetTileSize.x), (texSize.y / (float)tilesetTileSize.y) };

			Color color = Colors::White;
			if (!pTileset->IsValid())
			{
				color = Colors::Magenta;
			}

			// Create a vertex array.
			sf::VertexArray vertices;
			vertices.setPrimitiveType(sf::Quads);
			vertices.resize((size_t)mapSize.x * mapSize.y * 4);

			// Render the tiles we are currently able to see.
			for (unsigned int x = 0; x < mapSize.x; ++x)
			{
				for (unsigned int y = 0; y < mapSize.y; ++y)
				{
					sf::Vertex* quad = &vertices[(size_t)tilemap.IndexFromPosition(x, y) * 4];

					// define its 4 corners
					quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
					quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
					quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
					quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

					// Texturing

					// find its position in the tileset texture
					if (pTileset->IsValid())
					{
						const TileID tileId = layer.m_tiles[tilemap.IndexFromPosition(x, y)];

						const int tu = (tileId % (int)tiling.x);
						const int tv = (tileId / (int)tiling.x);

						quad[0].texCoords = sf::Vector2f(tu * tilesetTileSize.x, tv * tilesetTileSize.y);
						quad[1].texCoords = sf::Vector2f((tu + 1) * tilesetTileSize.x, tv * tilesetTileSize.y);
						quad[2].texCoords = sf::Vector2f((tu + 1) * tilesetTileSize.x, (tv + 1) * tilesetTileSize.y);
						quad[3].texCoords = sf::Vector2f(tu * tilesetTileSize.x, (tv + 1) * tilesetTileSize.y);
					}

					// Coloring. Mainly to detect missing textures.
					quad[0].color = sf::Convert(color);
					quad[1].color = sf::Convert(color);
					quad[2].color = sf::Convert(color);
					quad[3].color = sf::Convert(color);
				}
			}

			sf::Texture* pTexture = static_cast<sf::Texture*>(pTileset->GetNativeTexture());
			pTarget->draw(vertices, pTexture);
		}
	}
}
