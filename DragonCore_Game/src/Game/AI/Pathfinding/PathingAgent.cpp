#include "PathingAgent.h"

#include <Game/Config.h>
#include <Game/AI/Pathfinding/Path.h>
#include <SFML/Graphics.hpp>


bool PathingAgent::Init(const Tilemap* pTilemap)
{
	m_pTilemap = pTilemap;
	m_pathPlan.OnFinished([this](Path* pPath) {

		if (m_pPath)
		{
			delete m_pPath;
		}

		m_pPath = pPath;
	});

	return true;
}

void PathingAgent::PathFindTo(Vector2 pos)
{
	//m_pathPlan.Init(m_location.position / g_kTileSize, )
}

void PathingAgent::Update(float dt)
{
	m_pathPlan.Update();

	// DYLAN: sad state machine ahead.
	PathPlanStatus status = m_pathPlan.GetStatus();
	if (m_pPath != nullptr)
	{
		
	}
	else if (status == PathPlanStatus::kProcessing)
	{
		// Continue to rotate (As if its searching.)
	}
	else if (status == PathPlanStatus::kFailed)
	{
		// Struggle Movement.
	}
}

void PathingAgent::Draw(sf::RenderTarget* pTarget)
{
	m_pathPlan.Draw(pTarget);
	if (m_pPath)
		m_pPath->Draw(pTarget);
	
	// DYLAN: Ugly drawing code ahead, Can be optimized a lot.

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
