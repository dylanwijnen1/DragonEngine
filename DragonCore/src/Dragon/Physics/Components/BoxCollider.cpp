#include "BoxCollider.h"

#include <Dragon/Game/Game.h>
#include <Dragon/Physics/Physics.h>

#include <Box2D/Box2D.h>

namespace dragon
{
	bool BoxCollider::PostInit()
	{
		b2Body* pBody = (b2Body*)GetOwner()->GetComponent<RigidBody>();

		if (pBody)
		{
			b2PolygonShape shape;
			shape.SetAsBox(.5f, .5f);
			b2Fixture* pFixture = pBody->CreateFixture(&shape, 1.0f);
			return Collider::PostInitCollider();
		}

		return false;
	}

	bool BoxCollider::PostInit(Component* pComponent)
	{
		BoxCollider* pOther = dynamic_cast<BoxCollider*>(pComponent);
		if (pOther)
		{
			b2Body* pBody = (b2Body*)GetOwner()->GetComponent<RigidBody>();
			
			if (pBody)
			{
				b2PolygonShape shape;
				Vector2f size = pOther->GetSize();
				shape.SetAsBox(size.x / 2.f, size.y / 2.f);
				shape.m_centroid = b2::Convert(pOther->GetOffset());

				b2Fixture* pFixture = pBody->CreateFixture(&shape, pOther->GetDensity());
				return Collider::PostInitCollider(pOther);
			}
		}

		return false;
	}

	void BoxCollider::SetWidth(float width)
	{
		m_size.x = width;
		SetBoxData();
	}

	void BoxCollider::SetHeight(float height)
	{
		m_size.y = height;
		SetBoxData();
	}

	void BoxCollider::SetSize(Vector2f size)
	{
		m_size = size;
		SetBoxData();
	}

	void BoxCollider::SetAngle(float angle)
	{
		m_angle = angle;
		SetBoxData();
	}

	void BoxCollider::SetOffset(Vector2f offset)
	{
		b2Fixture* pFixture = m_pBody->GetFixtureList();
		if (pFixture)
		{
			if (pFixture->GetShape()->GetType() != b2Shape::e_polygon)
			{
				WARN("[BoxCollider] Tried to edit BoxCollider but fixture is not of type polygon.");
				return;
			}

			b2PolygonShape* pShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());
			if (pShape)
			{
				pShape->m_centroid.Set(offset.x, offset.y);
			}
			else
			{
				WARN("[BoxCollider] Tried to edit BoxCollider but fixture is not of type polygon.");
			}
		}

	}

	Vector2f BoxCollider::GetOffset() const
	{
		b2Fixture* pFixture = m_pBody->GetFixtureList();
		if (pFixture)
		{
			if (pFixture->GetShape()->GetType() == b2Shape::e_polygon)
			{
				b2PolygonShape* pShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());
				if (pShape)
				{
					return b2::Convert(pShape->m_centroid);
				}
			}
		}

		WARN("[BoxCollider] Tried to access polygon shape data but it was not a polygon shape.");
		return Vector2f(0.f, 0.f);
	}

	void BoxCollider::SetBoxData()
	{
		b2Fixture* pFixture = m_pBody->GetFixtureList();
		if (pFixture)
		{
			if (pFixture->GetShape()->GetType() == b2Shape::e_polygon)
			{
				b2PolygonShape* pShape = dynamic_cast<b2PolygonShape*>(pFixture->GetShape());
				if (pShape)
				{
					pShape->SetAsBox(m_size.x / 2.0f, m_size.y / 2.0f, pShape->m_centroid, m_angle);
				}
			}
		}

		WARN("[BoxCollider] Tried to edit BoxCollider but fixture is not of type polygon.");
		return;
	}

}

