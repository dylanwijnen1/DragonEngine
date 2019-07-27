#include "CircleCollider.h"

#include <Dragon/Game/Game.h>
#include <Dragon/Physics/Physics.h>

#include <Box2D/Box2D.h>

namespace dragon
{
	bool CircleCollider::PostInit()
	{
		b2Body* pBody = (b2Body*)GetOwner()->GetComponent<RigidBody>();
		if (pBody)
		{
			b2CircleShape shape;
			shape.m_radius = 1.0f;
			shape.m_p.SetZero();
			m_pFixture = pBody->CreateFixture(&shape, 1.0f);

			return Collider::PostInit();
		}
		else
		{
			WARN("[CircleCollider] Could not add collider there is no rigidbody attached to the game object.");
			return false;
		}

	}

	bool CircleCollider::PostInit(Component* pComponent)
	{
		CircleCollider* pOther = dynamic_cast<CircleCollider*>(pComponent);
		if (pOther)
		{
			b2Body* pBody = (b2Body*)GetOwner()->GetComponent<RigidBody>();
			if (pBody)
			{

				b2CircleShape shape;
				shape.m_radius = pOther->GetRadius();
				//shape.m_p = GetOwner()->GetPosition();
				shape.m_p.SetZero(); // TODO: Set position of the new game object.
				m_pFixture = pBody->CreateFixture(&shape, pOther->GetDensity());

				return Collider::PostInit(pOther);
			}
		}

		return false;
	}

	void CircleCollider::SetRadius(float radius)
	{
		b2Shape* pShape = m_pFixture->GetShape();
		if (pShape; pShape->GetType() != b2Shape::e_circle)
		{
			WARN("[CircleCollider] Tried to edit BoxCollider but fixture is not of type circle.");
			return;
		}

		b2CircleShape* pCircleShape = dynamic_cast<b2CircleShape*>(pShape);
		if (pCircleShape)
		{
			pCircleShape->m_radius = radius;
		}
		else
		{
			WARN("[CircleCollider] Tried to edit BoxCollider but fixture is not of type circle.");
		}
	}

	float CircleCollider::GetRadius() const
	{
		b2Shape* pShape = m_pFixture->GetShape();
		if (pShape; pShape->GetType() == b2Shape::e_circle)
		{
			b2CircleShape* pCircleShape = dynamic_cast<b2CircleShape*>(pShape);
			if (pCircleShape)
			{
				return pCircleShape->m_radius;
			}
		}

		WARN("[CircleCollider] Tried to access data on CircleCollider but fixture is not of type circle.");
		return 0.0f;
	}

	void CircleCollider::SetOffset(Vector2f offset)
	{
		b2Shape* pShape = m_pFixture->GetShape();
		if (pShape; pShape->GetType() == b2Shape::e_circle)
		{
			b2CircleShape* pCircleShape = dynamic_cast<b2CircleShape*>(pShape);
			if (pCircleShape)
			{
				pCircleShape->m_p.Set(offset.x, offset.y);
			}
		}

		WARN("[CircleCollider] Tried to edit Circle but fixture is not of type circle.");
	}

	Vector2f CircleCollider::GetOffset() const
	{
		b2Shape* pShape = m_pFixture->GetShape();
		if (pShape; pShape->GetType() == b2Shape::e_circle)
		{
			b2CircleShape* pCircleShape = dynamic_cast<b2CircleShape*>(pShape);
			if (pCircleShape)
			{
				return b2::Convert(pCircleShape->m_p);
			}
		}

		WARN("[CircleCollider] Tried to access circle data but fixture is not of type circle.");

		return Vector2f();
	}
}
