#include "CapsuleCollider.h"

#include <Dragon/Physics/Physics.h>

#include <Box2D/Box2D.h>

namespace dragon
{
	bool CapsuleCollider::PostInit()
	{
		Collider::PostInitCollider();
		return CreateFixtures();
	}

	bool CapsuleCollider::PostInit(Component* pComponent)
	{
		CapsuleCollider* pOther = dynamic_cast<CapsuleCollider*>(pComponent);
		if (pOther)
		{
			m_size = pOther->m_size;
			m_offset = pOther->m_offset;

			Collider::PostInitCollider();

			SetDensity(pOther->GetDensity());
			SetFriction(pOther->GetFriction());
			SetRestitution(pOther->GetRestitution());
		}

		return false;
	}

	void CapsuleCollider::SetOffset(Vector2f offset)
	{
		m_offset = offset;

		// Change fixture positions
	}

	Vector2f CapsuleCollider::GetOffset() const
	{
		return m_offset;
	}

	void CapsuleCollider::SetSize(Vector2f size)
	{
		m_size = size;
	}

	Vector2f CapsuleCollider::GetSize() const
	{
		return m_size;
	}

#pragma region Collider Overrides

	void CapsuleCollider::SetIsTrigger(bool trigger)
	{
		for (b2Fixture* pFixture : m_fixtures)
		{
			if (pFixture)
			{
				pFixture->SetSensor(trigger);
			}
		}
	}

	bool CapsuleCollider::IsTrigger() const
	{
		if (m_fixtures[0])
		{
			return m_fixtures[0]->IsSensor();
		}

		return false;
	}

	void CapsuleCollider::SetDensity(float density)
	{
		for (b2Fixture* pFixture : m_fixtures)
		{
			if (pFixture)
			{
				pFixture->SetDensity(density / 3.0f);
			}
		}

		if (m_pBody)
		{
			m_pBody->ResetMassData();
		}
	}

	float CapsuleCollider::GetDensity() const
	{
		if (m_fixtures[0])
		{
			return m_fixtures[0]->GetDensity() * 3.0f;
		}

		return 0.0f;
	}

	void CapsuleCollider::SetFriction(float friction)
	{
		for (b2Fixture* pFixture : m_fixtures)
		{
			if (pFixture)
			{
				pFixture->SetFriction(friction);
			}
		}
	}

	float CapsuleCollider::GetFriction() const
	{
		if (m_fixtures[0])
		{
			return m_fixtures[0]->GetFriction();
		}

		return 0.0f;
	}

	void CapsuleCollider::SetRestitution(float restitution)
	{
		for (b2Fixture* pFixture : m_fixtures)
		{
			if (pFixture)
			{
				pFixture->SetRestitution(restitution);
			}
		}
	}

	float CapsuleCollider::GetRestitution() const
	{
		if (m_fixtures[0])
		{
			return m_fixtures[0]->GetRestitution();
		}

		return 0.0f;
	}

	bool CapsuleCollider::CreateFixtures()
	{
		// TODO: Just create the fixtures and call, SetSize and SetOffset
		if (m_pBody)
		{
			// Circles
			b2CircleShape circleShape;
			circleShape.m_radius = m_size.x;
			circleShape.m_p.Set(0.f + m_offset.x, .5f + m_offset.y);

			m_fixtures[0] = m_pBody->CreateFixture(&circleShape, 1.0f);
			circleShape.m_p.Set(0.f + m_offset.x, -.5f + m_offset.y);
			m_fixtures[2] = m_pBody->CreateFixture(&circleShape, 1.0f);

			// Box
			b2PolygonShape boxShape;
			boxShape.SetAsBox(m_size.x / 2.0f, m_size.y / 2.0f);
			boxShape.m_centroid = b2::Convert(m_offset);
			m_fixtures[1] = m_pBody->CreateFixture(&boxShape, 1.0f);

			return true;
		}
		
		return false;
	}

#pragma endregion

}
