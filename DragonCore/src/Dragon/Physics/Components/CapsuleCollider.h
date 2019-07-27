#pragma once

#include <Dragon/Physics/Components/Collider.h>
#include <EASTL/array.h>

class b2Fixture;

namespace dragon
{

	/// <summary>
	/// A capsule collider consists of two circles and one box collider.
	/// To create the illusion of a Capsule.
	/// </summary>
	class CapsuleCollider : public Collider
	{
		//bool m_isHorizontal; // TODO: Maybe implement the feature of allowing a horizontal capsule, See unity documentation.
		Vector2f m_size;
		Vector2f m_offset;

		eastl::array<b2Fixture*, 3> m_fixtures; // 0 = TopCircle, 1 = Box, 2 = BottomCircle

	public:
		COMPONENT_ID(CapsuleCollider)

		CapsuleCollider() 
			: m_size(1.0f, 1.0f)
			, m_offset(0.0f, 0.0f)
		{}

		~CapsuleCollider() = default;

		CapsuleCollider(const CapsuleCollider&) = default;
		CapsuleCollider(CapsuleCollider&&) = default;
		CapsuleCollider& operator=(const CapsuleCollider&) = default;
		CapsuleCollider& operator=(CapsuleCollider&&) = default;

		virtual bool PostInit() final override;
		virtual bool PostInit(Component* pComponent) final override;

#pragma region CapsuleCollider functions

		void SetOffset(Vector2f offset);
		Vector2f GetOffset() const;

		void SetSize(Vector2f size);
		Vector2f GetSize() const;

#pragma endregion

#pragma region Collider Overrides

		virtual void SetIsTrigger(bool trigger) override;
		virtual bool IsTrigger() const override;

		//Weight
		virtual void SetDensity(float density) override;
		virtual float GetDensity() const override;

		// Slipperyness
		virtual void SetFriction(float friction) override;
		virtual float GetFriction() const override;

		// Bouncyness
		virtual void SetRestitution(float restitution) override;
		virtual float GetRestitution() const override;

#pragma endregion

	private:

		bool CreateFixtures();

	};

}