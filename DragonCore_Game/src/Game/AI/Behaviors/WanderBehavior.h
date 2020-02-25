#pragma once

#include <Game/AI/Behaviors/Behavior.h>

class WanderBehavior : public Behavior
{
	
	// Random tile in x radius.
	Vector2 m_targetTile;

	// Speed at which the agent should move around.
	float m_speed;

public:

	WanderBehavior()
		: WanderBehavior(nullptr, 5.0f)
	{}

	WanderBehavior(KinematicAgent* pAgent)
		: WanderBehavior(pAgent, 5.0f)
	{}

	WanderBehavior(KinematicAgent* pAgent, float speed)
		: Behavior(pAgent)
		, m_targetTile()
		, m_speed(speed)
	{}

	virtual void OnTransitionEnter() override;

	virtual Behavior* Update(float dt) override;
	
};