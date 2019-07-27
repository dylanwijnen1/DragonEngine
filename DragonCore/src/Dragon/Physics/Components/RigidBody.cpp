#include "RigidBody.h"

#include <Dragon/Game/Game.h>
#include <Dragon/Game/GameObject.h>
#include <Box2D/Box2D.h>

#include <Dragon/Physics/Physics.h>

namespace dragon
{
	RigidBody::~RigidBody()
	{
		b2World* pWorld = (b2World*)(GetOwner()->GetWorld());
		pWorld->DestroyBody(m_pBody);
	}

	bool RigidBody::Init()
	{
		// If a body is already existant (from cloning) then skip this step.
		if (!m_pBody)
		{
			b2BodyDef def;
			def.userData = GetOwner();
			def.active = IsActive();
			def.bullet = false;

			//Vector2f pos = GetOwner()->GetPosition();
			Vector2f pos;
			def.position = b2Vec2(pos.x, pos.y);

			//float angle = GetOwner()->GetRotation();
			float angle = 0.0f;
			def.angle = angle;

			b2World* pWorld = (b2World*)GetOwner()->GetWorld();
			m_pBody = pWorld->CreateBody(&def);
		}

		return true;
	}

	bool RigidBody::Init(Component* pComponent)
	{
		RigidBody* pOther = dynamic_cast<RigidBody*>(pComponent);
		if(pComponent)
		{
			b2World* pWorld = (b2World*)(GetOwner()->GetWorld());
			b2BodyDef def;
			m_pBody = pWorld->CreateBody(&def);

			// Actual cloning
			SetBodyType(pOther->GetBodyType());
			SetLinearDamping(pOther->GetLinearDamping());
			SetLinearVelocity(pOther->GetLinearVelocity());
			SetAngularDamping(pOther->GetAngularDamping());
			SetAngularVelocity(pOther->GetAngularVelocity());
			SetBullet(pOther->IsBullet());
			SetCanSleep(pOther->CanSleep());

			return true; // Successfully created rigidbody copy.
		}

		return false;
	}

#pragma region Body Functions

	void RigidBody::SetBodyType(BodyType type)
	{
		m_pBody->SetType((b2BodyType)type);
	}

	RigidBody::BodyType RigidBody::GetBodyType() const
	{
		return (BodyType)m_pBody->GetType();
	}

	void RigidBody::SetLinearDamping(float damping)
	{
		m_pBody->SetLinearDamping(damping);
	}

	float RigidBody::GetLinearDamping() const
	{
		return m_pBody->GetLinearDamping();
	}

	void RigidBody::SetLinearVelocity(Vector2f vel)
	{
		return m_pBody->SetLinearVelocity(b2::Convert(vel));
	}

	Vector2f RigidBody::GetLinearVelocity() const
	{
		return b2::Convert(m_pBody->GetLinearVelocity());
	}

	void RigidBody::SetAngularDamping(float damping)
	{
		m_pBody->SetAngularDamping(damping);
	}

	float RigidBody::GetAngularDamping() const
	{
		return m_pBody->GetAngularDamping();
	}

	void RigidBody::SetAngularVelocity(float vel)
	{
		m_pBody->SetAngularVelocity(vel);
	}

	float RigidBody::GetAngularVelocity() const
	{
		return m_pBody->GetAngularVelocity();
	}

	void RigidBody::SetGravityScale(float scale)
	{
		m_pBody->SetGravityScale(scale);
	}

	float RigidBody::GetGravityScale() const
	{
		return m_pBody->GetGravityScale();
	}

	void RigidBody::SetBullet(bool isBullet)
	{
		m_pBody->SetBullet(isBullet);
	}

	bool RigidBody::IsBullet() const
	{
		return m_pBody->IsBullet();
	}

	void RigidBody::SetCanSleep(bool allowance)
	{
		m_pBody->SetSleepingAllowed(allowance);
	}

	bool RigidBody::CanSleep() const
	{
		return m_pBody->IsSleepingAllowed();
	}

	Vector2f RigidBody::GetPosition() const
	{
		return b2::Convert(m_pBody->GetPosition());
	}

	float RigidBody::GetAngle() const
	{
		return m_pBody->GetAngle();
	}

	float RigidBody::GetMass() const
	{
		return m_pBody->GetMass();
	}

	void RigidBody::ApplyForce(Vector2f force, Vector2f pos, bool wake)
	{
		m_pBody->ApplyForce(b2::Convert(force), b2::Convert(pos), wake);
	}

	void RigidBody::ApplyForceToCenter(Vector2f force, bool wake)
	{
		m_pBody->ApplyForceToCenter(b2::Convert(force), wake);
	}

	void RigidBody::ApplyTorque(float torque, bool wake)
	{
		m_pBody->ApplyTorque(torque, wake);
	}

	void RigidBody::ApplyLinearImpulse(Vector2f impulse, Vector2f point, bool wake)
	{
		m_pBody->ApplyLinearImpulse(b2::Convert(impulse), b2::Convert(point), wake);
	}

	void RigidBody::ApplyLinearImpulseToCenter(Vector2f impulse, bool wake)
	{
		m_pBody->ApplyLinearImpulseToCenter(b2::Convert(impulse), wake);
	}

	void RigidBody::ApplyAngularImpulse(float impulse, bool wake)
	{
		m_pBody->ApplyAngularImpulse(impulse, wake);
	}

	void RigidBody::Serialize(OutStream& out)
	{
		// Total Cost: 8 bytes
		out.Write((char)GetBodyType());
		out.Write(GetLinearDamping());
		out.Write(GetLinearVelocity());
		out.Write(GetAngularDamping());
		out.Write(GetAngularVelocity());
		out.Write(IsBullet());
		out.Write(CanSleep());
	}

	void RigidBody::Deserialize(InStream& in)
	{
		SetBodyType((BodyType)in.Read<char>());
		SetLinearDamping(in.Read<float>());
		SetLinearVelocity(in.Read<Vector2f>());
		SetAngularDamping(in.Read<float>());
		SetAngularVelocity(in.Read<float>());
		SetBullet(in.Read<bool>());
		SetCanSleep(in.Read<bool>());
	}

#pragma endregion

}
