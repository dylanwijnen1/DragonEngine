#include "PathingAgent.h"

#include <Game/Config.h>
#include <Game/AI/Pathfinding/Path.h>
#include <SFML/Graphics.hpp>

#include <Dragon/Debug.h>

#include <Game/AI/Behaviors/WanderBehavior.h>

bool PathingAgent::Init(const Tilemap* pTilemap)
{
	m_pTilemap = pTilemap;

	// Setup tile information for this agent. (This is a ground agent)
	m_pathPlan.GetTilePathData(g_kWaterTile).m_isNavigable = false;
	m_pathPlan.GetTilePathData(g_kBushTile).m_weight = 2.0f;

	// Setup behaviors.
	m_pWanderBehavior = new WanderBehavior(this);
	//m_pFollowPathBehavior = new FollowPathBehavior(m_pWanderBehavior); // Transition into idle when finished.
	//m_pStruggleBehavior = new StruggleBehavior(m_pWanderBehavior); // Transition into idle when finished.

	// Setup event listener on what happens when path plan has finished processing.
	m_pathPlan.OnFinished([this](Path* pPath) 
	{
		// Make sure we found a path.
		if (pPath)
		{
			m_endTime = Clock::now();
			auto duration = Duration(m_endTime - m_startTime);
			DLOG("Path Found: %lf seconds.", duration.count());

			if (m_pPath)
			{
				delete m_pPath;
			}

			m_pPath = pPath;
			//TransitionToBehavior(m_pFollowPathBehavior);
		}
		else
		{
			//TransitionToBehavior(m_pStruggleBehavior);
		}
	});

	TransitionToBehavior(m_pWanderBehavior);

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
	Behavior* pTransitionBehavior = m_pBehavior->Update(dt);
	if (pTransitionBehavior != nullptr)
	{
		TransitionToBehavior(pTransitionBehavior);
	}
}

void PathingAgent::TransitionToBehavior(Behavior* pBehavior)
{
	if (!pBehavior)
	{
		DWARN_TRACE("pBehavior is nullptr.");
		return;
	}

	if (m_pBehavior)
		m_pBehavior->OnTransitionExit();

	m_pBehavior = pBehavior;
	m_pBehavior->OnTransitionEnter();
}

void PathingAgent::Draw(sf::RenderTarget* pTarget)
{
	m_pathPlan.Draw(pTarget);

	if (m_pPath)
		m_pPath->Draw(pTarget);

	// DYLAN: Ugly drawing code ahead, Can be optimized a lot.

	Vector2f tileCenter = Vector2f(g_kTileSize / 2.0f, g_kTileSize / 2.0f);
	Vector2f centroid = m_location.position + tileCenter;

	// Triangle
	Vector2f origin(0.0f, -0.25f);

	Vector2f pointRight = Vector2f(0.5f, .25f) * g_kTileSize;
	pointRight.RotateAroundOrigin(m_location.orientation, origin);
	pointRight += centroid;

	Vector2f pointLeft = Vector2f(-0.5f, .25f) * g_kTileSize;
	pointLeft.RotateAroundOrigin(m_location.orientation, origin);
	pointLeft += centroid;

	Vector2f pointTop = Vector2f(0.0f, -1.f) * g_kTileSize;
	pointTop.RotateAroundOrigin(m_location.orientation, origin);
	pointTop += centroid;

	sf::Vertex vertices[]
	{
		sf::Vertex(sf::Vector2f(pointLeft.x, pointLeft.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(pointRight.x, pointRight.y), sf::Color::Green),
		sf::Vertex(sf::Vector2f(pointTop.x, pointTop.y), sf::Color::Blue)
	};

	pTarget->draw(vertices, 3, sf::PrimitiveType::Triangles);
}
