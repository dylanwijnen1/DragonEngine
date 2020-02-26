#pragma once

#include <Game/AI/Location.h>
#include <Game/AI/Kinematic.h>

class KinematicAgent
{
protected:
	Location m_location;
	Kinematic m_kinematic;

public:
	Vector2f GetPosition() const { return m_location.position; }
	void SetPosition(Vector2f pos) { m_location.position = pos; }

	float GetOrientation() const { return m_location.orientation; }
	void SetOrientation(float rot) { m_location.orientation = rot; }

	Kinematic& GetKinematic() { return m_kinematic; }
	const Kinematic& GetKinematic() const { return m_kinematic; }

	Location& GetLocation() { return m_location; }
	const Location GetLocation() const { return m_location; }

	virtual void Update(float dt)
	{
		m_kinematic.Integrate(m_location, dt);
	}
};