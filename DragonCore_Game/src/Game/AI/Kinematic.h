#pragma once

#include <Game/Vector2.h>

class Kinematic
{
	Vector2f m_velocity;
	float m_angularVelocity;

	float m_maxSpeed;
	float m_maxAcceleration;
	float m_maxAngularVelocity;
	float m_maxAngularAcceleration;

public:

	void SetMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
	float GetMaxSpeed() const { return m_maxSpeed; }

	void SetMaxAcceleration(float maxAccel) { m_maxAcceleration = maxAccel; }
	float GetMaxAcceleration() const { return m_maxAcceleration; }

	void SetMaxAngularVelocity(float maxAngularVel) { m_maxAngularVelocity = maxAngularVel; }
	float GetMaxAngularVelocity() const { return m_maxAngularVelocity; }

	void SetMaxAngularAcceleration(float maxAngularAccel) { m_maxAngularAcceleration = maxAngularAccel; }
	float GetMaxAngularAcceleration() const { return m_maxAngularAcceleration; }

	void Integrate(struct Location& location, float dt);

	void Accelerate(Vector2f velocity, float dt);
	void AccelerateRotation(float angularVelocity, float dt);

	void Stop();
};