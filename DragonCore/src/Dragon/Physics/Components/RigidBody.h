#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Generic/Math.h>

class b2Body;

namespace dragon
{
	class RigidBody : public Component
	{
	public:
		enum struct BodyType
		{
			Static = 0,
			Kinematic,
			Dynamic
		};

	private:
		b2Body* m_pBody;

	public:
		COMPONENT_ID(RigidBody)

		RigidBody()
			: m_pBody(nullptr)
		{}

		~RigidBody();

		RigidBody(const RigidBody&) = default;
		RigidBody(RigidBody&&) = default;
		RigidBody& operator=(const RigidBody&) = default;
		RigidBody& operator=(RigidBody&&) = default;

		virtual bool Init() override;
		virtual bool Init(Component* pComponent) override;

		operator b2Body* () { return m_pBody; }
		b2Body* GetPhysicsBody() const { return m_pBody; }
		b2Body* GetPhysicsBody() { return m_pBody; }

#pragma region Body Functions

		void SetBodyType(BodyType type);
		BodyType GetBodyType() const;

		void SetLinearDamping(float damping);
		float GetLinearDamping() const;

		void SetLinearVelocity(Vector2f vel);
		Vector2f GetLinearVelocity() const;

		void SetAngularDamping(float damping);
		float GetAngularDamping() const;

		void SetAngularVelocity(float vel);
		float GetAngularVelocity() const;
		
		void SetGravityScale(float scale);
		float GetGravityScale() const;

		void SetBullet(bool isBullet);
		bool IsBullet() const;

		void SetCanSleep(bool allowance);
		bool CanSleep() const;

		Vector2f GetPosition() const;
		float GetAngle() const;
		float GetMass() const;

		void ApplyForce(Vector2f force, Vector2f pos, bool wake = true);
		void ApplyForceToCenter(Vector2f force, bool wake = true);
		void ApplyTorque(float torque, bool wake = true);

		void ApplyLinearImpulse(Vector2f impulse, Vector2f point, bool wake = true);
		void ApplyLinearImpulseToCenter(Vector2f impulse, bool wake = true);
		void ApplyAngularImpulse(float impulse, bool wake = true);

#pragma endregion

#pragma region Serialization

		virtual void Serialize(OutStream& out) override;
		virtual void Deserialize(InStream& in) override;

#pragma endregion

	};

}