#include "PathingAgent.h"

#include <Game/Config.h>
#include <Game/AI/Pathfinding/Path.h>
#include <SFML/Graphics.hpp>

#include <Dragon/Debug.h>

bool PathingAgent::Init(const Tilemap* pTilemap)
{
	m_pTilemap = pTilemap;

	m_pathPlan.GetTilePathData(1061735679).m_isNavigable = false;
	m_pathPlan.GetTilePathData(582044927).m_weight = 5.0f;

	m_pathPlan.OnFinished([this](Path* pPath) 
	{
		m_endTime = Clock::now();
		auto duration = Duration(m_endTime - m_startTime);
		DLOG("Path Found: %lf seconds.", duration.count());

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
	Vector2 from = m_pTilemap->WorldToTilePosition(m_location.position);
	m_pathPlan.Init(from, pos, m_pTilemap);
	m_startTime = Clock::now();
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
	Vector2f pos = m_location.position;
	float extents = g_kTileSize / 2.0f;
	pos += Vector2f(extents, extents);
	sf::Vertex vertices[] =
	{
		sf::Vertex(sf::Vector2f(pos.x - extents, pos.y - extents), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(pos.x + extents, pos.y - extents), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(pos.x + extents, pos.y + extents), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(pos.x - extents, pos.y + extents), sf::Color::Blue),
	};

	pTarget->draw(&vertices[0], 4, sf::PrimitiveType::Quads);

	sf::Vertex points[] = { sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::Red) };
	pTarget->draw(&points[0], 1, sf::PrimitiveType::Points);

	//Vector2f pointOrigin(0.0f, -0.25f);

	//Vector2f pointRight = Vector2f(0.5f, .25f) * g_kTileSize;
	//pointRight.RotateAroundOrigin(m_location.orientation, pointOrigin);
	//pointRight += m_location.position;

	//Vector2f pointLeft = Vector2f(-0.5f, .25f) * g_kTileSize;
	//pointLeft.RotateAroundOrigin(m_location.orientation, pointOrigin);
	//pointLeft += m_location.position;

	//Vector2f pointTop = Vector2f(0.0f, -1.f) * g_kTileSize;
	//pointTop.RotateAroundOrigin(m_location.orientation, pointOrigin);
	//pointTop += m_location.position;

	//sf::Vertex vertices[]
	//{
	//	sf::Vertex(sf::Vector2f(pointLeft.x, pointLeft.y), sf::Color::Red),
	//	sf::Vertex(sf::Vector2f(pointRight.x, pointRight.y), sf::Color::Green),
	//	sf::Vertex(sf::Vector2f(pointTop.x, pointTop.y), sf::Color::Blue)
	//};

	//pTarget->draw(vertices, 3, sf::PrimitiveType::Triangles);
}
