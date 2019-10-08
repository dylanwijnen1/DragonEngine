#pragma once

#include <Dragon/Physics/Components/Collider.h>
#include <Dragon/Generic/Math.h>

class b2Fixture;

namespace dragon
{
	class CircleCollider : public Collider
	{
		b2Fixture* m_pFixture;

	public:
		COMPONENT_ID(CircleCollider)

		CircleCollider() = default;
		~CircleCollider() = default;

		CircleCollider(const CircleCollider&) = default;
		CircleCollider(CircleCollider&&) = default;
		CircleCollider& operator=(const CircleCollider&) = default;
		CircleCollider& operator=(CircleCollider&&) = default;

		virtual bool PostInit() final override;
		virtual bool PostInit(Component* pComponent) final override;

#pragma region CircleCollider functions

		void SetRadius(float radius);
		float GetRadius() const;

		void SetOffset(Vector2f offset);
		Vector2f GetOffset() const;

#pragma endregion

	};

}