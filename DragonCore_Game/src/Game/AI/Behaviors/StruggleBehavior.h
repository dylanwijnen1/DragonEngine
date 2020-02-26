#pragma once

#include <Game/AI/Behaviors/Behavior.h>

#include <Dragon/Generic/Random.h>

class StruggleBehavior : public Behavior
{
	
	float m_struggleTime;
	float m_timeLeft;

	Behavior* m_pExitState;
	dragon::Random m_random;

public:

	StruggleBehavior()
		: StruggleBehavior(nullptr, nullptr)
	{}

	StruggleBehavior(KinematicAgent* pAgent, Behavior* pExitState)
		: StruggleBehavior(pAgent, pExitState, 3.0f)
	{}

	StruggleBehavior(KinematicAgent* pAgent, Behavior* pExitState, float struggleTime)
		: Behavior(pAgent)
		, m_pExitState(pExitState)
		, m_struggleTime(struggleTime)
		, m_random((unsigned int)time(nullptr))
		, m_timeLeft(m_struggleTime)
	{}

	virtual Behavior* Update(float dt) override;

	virtual void OnTransitionEnter() override { m_timeLeft = m_struggleTime; }
};