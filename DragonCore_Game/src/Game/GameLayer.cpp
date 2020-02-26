#include "GameLayer.h"

#include <Game/Config.h>

#include <SFML/Graphics.hpp>

void GameLayer::OnAttach()
{
	m_tilemap.Init("map.png", Vector2(g_kTileSize, g_kTileSize));
	m_agent.SetPosition(m_tilemap.TileToWorldPosition(Vector2(3, 45)));
	m_agent.Init(&m_tilemap);
}

void GameLayer::Update(float dt)
{
	m_agent.Update(dt);
}

void GameLayer::FixedUpdate(float dt)
{
}

void GameLayer::Render(dragon::RenderTarget& target)
{
	sf::RenderTarget* pSfTarget = target.GetNativeTarget<sf::RenderTarget*>();
	m_tilemap.Draw(pSfTarget);

	//sf::RectangleShape rect(sf::Vector2f(g_kTileSize, g_kTileSize));
	//rect.setFillColor(sf::Color::Red);
	//rect.setPosition(m_tileMousePosition.x * (float)g_kTileSize, m_tileMousePosition.y * (float)g_kTileSize);
	//pSfTarget->draw(rect);

	m_agent.Draw(pSfTarget);
}

void GameLayer::OnEvent(dragon::ApplicationEvent& ev)
{
	ev.Dispatch<dragon::MouseButtonReleased>(this, &GameLayer::OnMouseReleasedEvent);
	ev.Dispatch<dragon::MouseMoved>(this, &GameLayer::OnMouseMovedEvent);
}

void GameLayer::OnMouseReleasedEvent(dragon::MouseButtonReleased& ev)
{
	dragon::Vector2f mousePos = ev.m_position;

	if (ev.m_button == MouseButton::Left)
	{
		m_agent.PathFindTo(m_tileMousePosition);
	}
	else if (ev.m_button == MouseButton::Right)
	{

	}
	else if (ev.m_button == MouseButton::Middle)
	{

	}
}

void GameLayer::OnMouseMovedEvent(dragon::MouseMoved& ev)
{
	m_mousePosition = Vector2f(ev.m_position.x, ev.m_position.y);
	m_tileMousePosition = m_tilemap.WorldToTilePosition(m_mousePosition);
}
