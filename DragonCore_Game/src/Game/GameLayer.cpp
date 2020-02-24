#include "GameLayer.h"

#include <Game/Config.h>

#include <SFML/Graphics.hpp>

void GameLayer::OnAttach()
{
	m_tilemap.Init("map.png", Vector2(16, 16));
	//m_pathPlan.GetTilePathData();

	m_pathPlan.GetTilePathData(1061735679).m_isNavigable = false;
	m_pathPlan.GetTilePathData(582044927).m_weight = 5.0f;
	// 2164228351
	// 582044927
}

void GameLayer::Update(float dt)
{
	//m_pathingAgent.Update(dt);
	if(m_pathPlan.GetStatus() == PathPlanStatus::kProcessing)
		m_pathPlan.Update();
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

	//m_pathPlan.Draw(pSfTarget);

	m_agent.Draw(pSfTarget);
}

void GameLayer::OnEvent(dragon::ApplicationEvent& ev)
{
	ev.Dispatch<dragon::MouseButtonReleased>(this, &GameLayer::OnMouseReleasedEvent);
	ev.Dispatch<dragon::MouseMoved>(this, &GameLayer::OnMouseMovedEvent);
	ev.Dispatch<dragon::MouseScrolled>(this, &GameLayer::OnMouseWheelScrollEvent);
}

void GameLayer::OnMouseReleasedEvent(dragon::MouseButtonReleased& ev)
{
	dragon::Vector2f mousePos = ev.m_position;

	if (ev.m_button == MouseButton::Left)
	{
		m_start = m_tileMousePosition;
	}
	else if (ev.m_button == MouseButton::Right)
	{
		m_end = m_tileMousePosition;
		//m_pathPlan.Update();
		//m_tilemap.SetTile()
	}
	else if (ev.m_button == MouseButton::Middle)
	{
		m_pathPlan.Init(m_start, m_end, &m_tilemap);
	}
}

void GameLayer::OnMouseMovedEvent(dragon::MouseMoved& ev)
{
	m_mousePosition = Vector2f(ev.m_position.x, ev.m_position.y);
	m_tileMousePosition = m_tilemap.WorldToTilePosition(m_mousePosition);

	m_agent.SetPosition(m_mousePosition);
}

void GameLayer::OnMouseWheelScrollEvent(dragon::MouseScrolled& ev)
{
	
}
