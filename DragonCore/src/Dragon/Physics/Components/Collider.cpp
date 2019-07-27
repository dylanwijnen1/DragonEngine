#include "Collider.h"

#include <Dragon/Game/Game.h>
#include <Dragon/Physics/Physics.h>

#include <Box2D/Box2D.h>

namespace dragon
{
	bool Collider::PostInitCollider()
	{
		m_pBody = (b2Body*)GetOwner()->GetComponent<RigidBody>();
		
		if (m_pBody)
			return true;

		return false;
	}

	bool Collider::PostInitCollider(Collider* pCollider)
	{
		bool result = PostInit();

		if (result)
		{
			b2Body* pOtherBody = pCollider->m_pBody;
			if (pOtherBody != nullptr)
			{
				b2Fixture* pOtherFixture = pOtherBody->GetFixtureList();
				b2Fixture* pThisFixture = m_pBody->GetFixtureList();

				// Copy Fixture data.
				if (pOtherFixture && pThisFixture)
				{
					pThisFixture->SetSensor(pOtherFixture->IsSensor());
					pThisFixture->SetDensity(pOtherFixture->GetDensity());
					pThisFixture->SetFriction(pOtherFixture->GetFriction());
					pThisFixture->SetRestitution(pOtherFixture->GetRestitution());
				}
			}

			return false;
		}

		return false;
	}

	void Collider::SetIsTrigger(bool trigger)
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->SetSensor(trigger);
		}
	}

	bool Collider::IsTrigger() const
	{
		if (b2Fixture * pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			return pFixture->IsSensor();
		}

		return false;
	}

	void Collider::SetDensity(float density)
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->SetDensity(density);
			m_pBody->ResetMassData();
		}
	}

	float Collider::GetDensity() const
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->GetDensity();
		}

		return 0.0f;
	}

	void Collider::SetFriction(float friction)
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->SetFriction(friction);
		}
	}

	float Collider::GetFriction() const
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->GetFriction();
		}

		return 0.0f;
	}

	void Collider::SetRestitution(float restitution)
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->SetRestitution(restitution);
		}
	}

	float Collider::GetRestitution() const
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			pFixture->GetRestitution();
		}

		return 0.0f;
	}

	RectF Collider::GetBounds() const
	{
		if (b2Fixture* pFixture = m_pBody->GetFixtureList(); pFixture != nullptr)
		{
			// TODO: Find out if this is accurate enough and if child index matters
			return b2::Convert(pFixture->GetAABB(0));
		}
		
		return RectF(0.0f, 0.0f, 0.0f, 0.0f);
	}
}
