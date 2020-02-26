#include "StruggleBehavior.h"

Behavior* StruggleBehavior::Update(float dt)
{
	KinematicAgent* pAgent = GetAgent();

	m_timeLeft -= dt;

	if (pAgent)
	{

		if (m_timeLeft < 0.0f)
			return m_pExitState;

		Kinematic& kinematic = pAgent->GetKinematic();
		float dir = m_random.RandomRange(-dragon::math::kPi, dragon::math::kPi) * 100.f;
		kinematic.AccelerateRotation(dir, dt);
	}

	return nullptr;
}
