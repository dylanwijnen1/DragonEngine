#pragma once

#include <Game/AI/Behaviors/Behavior.h>
#include <Dragon/Generic/Random.h>

#include <Game/AI/Pathfinding/PathPlan.h>
#include <Game/AI/Behaviors/IdleBehavior.h>

class Tilemap;

class WanderBehavior : public Behavior
{
	// Random pos in x radius.
	Vector2 m_targetTile;

	// Distance at which the generated new tile should be made.
	int m_distance;

	// Tilemap to find a new position.
	const Tilemap* m_pTilemap;

	dragon::Random m_random;

	IdleBehavior* m_pIdleBehavior;

public:

	WanderBehavior()
		: WanderBehavior(nullptr, nullptr, 5)
	{}

	WanderBehavior(KinematicAgent* pAgent, const Tilemap* pTilemap)
		: WanderBehavior(pAgent, pTilemap, 5)
	{}

	WanderBehavior(KinematicAgent* pAgent, const Tilemap* pTilemap, int distance)
		: Behavior(pAgent)
		, m_pTilemap(pTilemap)
		, m_targetTile()
		, m_distance(distance)
		, m_random((unsigned int)time(nullptr))
		, m_pIdleBehavior(new IdleBehavior())
	{}

	~WanderBehavior()
	{
		delete m_pIdleBehavior;
	}

	virtual Behavior* Update(float dt) override;
	virtual void Draw(sf::RenderTarget* pTarget) override;

	virtual void OnTransitionEnter() override;

private:

	void FindNewTarget();
	
};