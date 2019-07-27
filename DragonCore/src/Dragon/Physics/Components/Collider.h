#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Math/Math.h>

class b2Body;

namespace dragon
{
	// Abstract Component
	class Collider : public Component
	{
	protected:
		b2Body* m_pBody;

	public:
		bool PostInitCollider();
		bool PostInitCollider(Collider* pCollider);

		virtual void SetIsTrigger(bool trigger);
		virtual bool IsTrigger() const;

		//Weight
		virtual void SetDensity(float density);
		virtual float GetDensity() const;

		// Slipperyness
		virtual void SetFriction(float friction);
		virtual float GetFriction() const;
		
		// Bouncyness
		virtual void SetRestitution(float restitution);
		virtual float GetRestitution() const;

		RectF GetBounds() const;
	};
}