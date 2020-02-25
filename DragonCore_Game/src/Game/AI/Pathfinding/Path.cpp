#include "Path.h"

#include <Game/Config.h>

#include <SFML/Graphics.hpp>

void Path::Draw(sf::RenderTarget* pTarget)
{
	pTarget->draw(m_vertices);
}

void Path::PushWaypoint(Vector2 pos)
{
	const static sf::Color kPathLineColor = sf::Color::Red;

	float screenX = pos.x * g_kTileSize - (g_kTileSize / 2.0f);
	float screenY = pos.y * g_kTileSize - (g_kTileSize / 2.0f);
	m_vertices.append(sf::Vertex(sf::Vector2f(screenX, screenY), kPathLineColor));
	m_waypoints.emplace_back(pos);
}
