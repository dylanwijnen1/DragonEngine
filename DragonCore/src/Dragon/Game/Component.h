#pragma once

#include <Dragon/Generic/StringHash.h>
#include <Dragon/Generic/Serialization/ISerializable.h>


/// <summary>
/// Generates an Identifier for the component and creates the GetIdentifier function.
/// </summary>
#if defined(_MSC_VER)
#define COMPONENT_ID(COMPONENT) \
	__pragma(warning(push)) \
	__pragma(warning(disable : 4307)) \
	static constexpr ComponentId Identifier = #COMPONENT##_hash64; \
	virtual ComponentId GetIdentifier() const override { return Identifier; } \
	virtual Component* Clone() const override { return new COMPONENT(*this); } \
	__pragma (warning(pop))
#else
#define COMPONENT_ID(COMPONENT) \
	static constexpr ComponentId Identifier = #COMPONENT##_hash64; \
	virtual ComponentId GetIdentifier() const override { return Identifier; } \
	virtual Component* Clone() const override { return new COMPONENT(*this); }
#endif

namespace dragon
{
	using ComponentId = uint64_t;

	class Component : public ISerializable
	{
		class GameObject* m_pOwner;

		bool m_isActive;

	public:

		Component()
			: m_pOwner(nullptr)
			, m_isActive(true)
		{}

		virtual ~Component() = default;

		Component(const Component&) = default;
		Component(Component&&) = default;
		Component& operator=(const Component&) = default;
		Component& operator=(Component&&) = default;

		virtual ComponentId GetIdentifier() const = 0;

		// GameObject Owner
		GameObject* GetOwner() { return m_pOwner; }
		GameObject* GetOwner() const { return m_pOwner; }
		void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }

		// Active
		bool IsActive() const { return m_isActive; }
		virtual void SetActive(bool active) { m_isActive = active; }

		virtual bool Init() { return true; }
		virtual bool PostInit() { return true; }

		// Called during cloning, The component given is the component it is cloning from
		virtual bool Init(Component* pComponent) { return Init(); }

		// Called during cloning, The component given is the component it is cloning from
		virtual bool PostInit(Component* pComponent) { return PostInit(); }

		// Creates a blank version of the component
		virtual Component* Clone() const = 0;

#pragma region Networking

		//virtual void Synchronize(NetworkMessage& message) {}
		//virtual void Replicate(NetworkMessage& message) {}

#pragma endregion

#pragma region Serialization

		virtual void Serialize(OutStream& out) override {}
		virtual void Deserialize(InStream& in) override {}

#pragma endregion

	};

};