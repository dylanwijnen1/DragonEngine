#include "WanderBehavior.h"

#include <Game/Config.h>
#include <Game/Tilemap.h>
#include <Game/AI/Pathfinding/PathingAgent.h>

#include <Dragon/Generic/Math/MathFunctions.h>

#include <SFML/Graphics.hpp>

void WanderBehavior::OnTransitionEnter()
{
    FindNewTarget();
}

void WanderBehavior::FindNewTarget()
{   
    Vector2 agentPos = m_pTilemap->WorldToTilePosition(GetAgent()->GetPosition());
    Vector2 targetTile;

    do
    {
        float angle = m_random.RandomRange(-dragon::math::kPi, dragon::math::kPi);
        Vector2 dir;
        dir.x = (int)dragon::math::RoundToNearest(dragon::math::Cos(angle) * (float)m_distance);
        dir.y = (int)dragon::math::RoundToNearest(dragon::math::Sin(angle) * (float)m_distance);
        targetTile = agentPos + dir;
    } while (!m_pTilemap->WithinBounds(targetTile));

    m_targetTile = targetTile;
}

Behavior* WanderBehavior::Update(float dt)
{
    KinematicAgent* pAgent = GetAgent();
    PathingAgent* pPathingAgent = dynamic_cast<PathingAgent*>(pAgent);

    if (pPathingAgent)
    {
        // Transitions into path finding behavior.
        pPathingAgent->PathFindTo(m_targetTile);
        return m_pIdleBehavior;
    }

    return nullptr;
}

void WanderBehavior::Draw(sf::RenderTarget* pTarget)
{
	Vector2f agentPos = GetAgent()->GetPosition();
    Vector2f targetPos = m_pTilemap->TileToWorldPosition(m_targetTile);
    targetPos += Vector2f(g_kTileSize / 2.0f, g_kTileSize / 2.0f);

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(agentPos.x, agentPos.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(targetPos.x, targetPos.y), sf::Color::Red)
	};

	pTarget->draw(line, 2, sf::PrimitiveType::Lines);
}
