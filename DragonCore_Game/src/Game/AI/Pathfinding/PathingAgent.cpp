#include "PathingAgent.h"

#include <Game/Config.h>
#include <SFML/Graphics.hpp>

void PathingAgent::Update(float dt)
{
	// DYLAN: sad state machine ahead.
	PathPlanStatus status = m_pathPlan.GetStatus();
	if (status == PathPlanStatus::kProcessing)
	{
		m_pathPlan.Update();
	}
	else if (status == PathPlanStatus::kFinished)
	{
		// Start following path.
		m_pathPlan.ConstructPath();
	}
	else if (status == PathPlanStatus::kFailed)
	{
		// Struggle Movement.
	}
}

void PathingAgent::Draw(sf::RenderTarget* pTarget)
{
	m_pathPlan.Draw(pTarget);
	
	// DYLAN: Ugly ass drawing code ahead, Can be optimized a lot.

	Vector2f pointOrigin(0.0f, -0.25f);

	Vector2f pointRight = Vector2f(0.5f, .25f) * g_kTileSize;
	pointRight.RotateAroundOrigin(m_location.orientation, pointOrigin);
	pointRight += m_location.position;

	Vector2f pointLeft = Vector2f(-0.5f, .25f) * g_kTileSize;
	pointLeft.RotateAroundOrigin(m_location.orientation, pointOrigin);
	pointLeft += m_location.position;

	Vector2f pointTop = Vector2f(0.0f, -1.f) * g_kTileSize;
	pointTop.RotateAroundOrigin(m_location.orientation, pointOrigin);
	pointTop += m_location.position;

	sf::Vertex vertices[]
	{
		sf::Vertex(sf::Vector2f(pointLeft.x, pointLeft.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(pointRight.x, pointRight.y), sf::Color::Green),
		sf::Vertex(sf::Vector2f(pointTop.x, pointTop.y), sf::Color::Blue)
	};

	pTarget->draw(vertices, 3, sf::PrimitiveType::Triangles);
}
