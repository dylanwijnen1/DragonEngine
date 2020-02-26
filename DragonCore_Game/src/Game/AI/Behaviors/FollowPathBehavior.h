#pragma once

#include <Game/AI/Behaviors/Behavior.h>

class FollowPathBehavior : public Behavior
{
	Behavior* m_pExitState;

	size_t m_pathIndex;
	Vector2f m_target;

	float m_arriveRadius;
	float m_slowRadius;

public:

	FollowPathBehavior()
		: FollowPathBehavior(nullptr, nullptr)
	{}

	FollowPathBehavior(KinematicAgent* pAgent, Behavior* pExitStateBehavior)
		: FollowPathBehavior(pAgent, pExitStateBehavior, 3.0f, 8.0f)
	{}

	FollowPathBehavior(KinematicAgent* pAgent, Behavior* pExitStateBehavior, float arriveRadius, float slowRadius)
		: Behavior(pAgent)
		, m_pExitState(pExitStateBehavior)
		, m_pathIndex(0)
		, m_target()
		, m_arriveRadius(arriveRadius)
		, m_slowRadius(slowRadius)
	{}

	virtual Behavior* Update(float dt) override;

	virtual void OnTransitionEnter() override;
	virtual void OnTransitionExit() override;

private:
	bool Next();
	bool GoToWaypoint(size_t index);
};