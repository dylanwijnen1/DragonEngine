#include "Kinematic.h"

#include <Game/AI/Location.h>

#include <Dragon/Generic/Math/MathFunctions.h>

void Kinematic::Integrate(Location& location, float dt)
{
	location.position += m_velocity * dt;
	location.orientation += m_angularVelocity * dt;

	// Clamp the angles to range -2*PI, 2*PI
	location.orientation = std::fmodf(location.orientation, 2.0f * dragon::math::kPi);

	// Do not allow kinematic to go faster than max speed.
	if (m_velocity.LengthSqrd() > m_maxSpeed * m_maxSpeed)
	{
		m_velocity.Normalize();
		m_velocity *= m_maxSpeed;
	}

	if (m_angularVelocity > m_maxAngularVelocity * m_maxAngularVelocity)
	{
		m_angularVelocity *= m_maxAngularVelocity;
	}
}

void Kinematic::Accelerate(Vector2f acceleration, float dt)
{
	m_velocity += acceleration * dt;
}

void Kinematic::AccelerateRotation(float angularAcceleration, float dt)
{
	m_angularVelocity += angularAcceleration * dt;
}

void Kinematic::Stop()
{
	m_velocity = Vector2f(0.f, 0.f);
	m_angularVelocity = 0.f;
}
