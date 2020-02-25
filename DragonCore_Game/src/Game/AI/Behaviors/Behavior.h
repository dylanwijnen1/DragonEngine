#pragma once

#include <Game/AI/KinematicAgent.h>

class Behavior
{
	KinematicAgent* m_pAgent;

public:

	Behavior()
		: m_pAgent(nullptr)
	{}

	Behavior(KinematicAgent* pAgent)
		: m_pAgent(pAgent)
	{}


	// Return the behavior to transition into.
	virtual Behavior* Update(float dt) = 0;

	virtual void OnTransitionEnter() {}
	virtual void OnTransitionExit() {}

	KinematicAgent* GetAgent() { return m_pAgent; }
	const KinematicAgent* GetAgent() const { return m_pAgent; }
	void SetAgent(KinematicAgent* pAgent) { m_pAgent = pAgent; }
};