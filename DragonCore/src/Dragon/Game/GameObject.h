#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Application/Debugging/Debug.h>

#include <Generic/ISerializable.h>

#include <EASTL/unordered_map.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>

namespace dragon
{
	using GameObjectId = unsigned long long;

	class GameObject final : public ISerializable
	{
		// What world does this GameObject belong too.
		class Scene* m_pWorld; 

		// The id of this game object in the world.
		GameObjectId m_id;

		// ResourceId m_resourceId; // If not 0 this game object was spawned from a resource definition.

		using Components = eastl::unordered_map<ComponentId, Component*>;
		Components m_components;

		//Transform m_transform;
		//GameObject* m_pParent;

		eastl::string m_tag; // Could use Compile time tags but that could become weird with adding new tags mismatched version of enum ?

		bool m_active;

	public:
		GameObject(GameObject&&) noexcept = default;
		GameObject& operator=(GameObject&&) noexcept = default;

		GameObject(const GameObject& other);
		GameObject& operator=(const GameObject& other);

		~GameObject();

		// World: Get/Set
		Scene* GetScene() { return m_pWorld; }
		Scene* GetScene() const { return m_pWorld; }
		void SetWorld(Scene* pWorld) { m_pWorld = pWorld; }

		// GameObject::m_active, Get/Set
		bool IsActive() const { return m_active; }
		void SetActive(bool active) { m_active = active; }

		// Marks this game object for destruction
		void Destroy();

		GameObject* Clone() const;
		GameObject* Clone(Scene* pWorld) const;

		GameObjectId GetId() const { return m_id; }

#pragma region Component

		// Get

		template<typename ComponentType>
		ComponentType* GetComponent() const;

		Component* GetComponent(ComponentId id) const;

		// Add Component
		template<typename ComponentType, typename... Args> 
		ComponentType* AddComponent(Args&&... comp);

		template<typename ComponentType>
		ComponentType* AddComponent(const ComponentType& comp);

		Component* AddComponent(ComponentId id);

		// Remove

		void RemoveComponent(ComponentId id);

		// Has

		template<typename ComponentType>
		bool HasComponent() const;

		bool HasComponent(ComponentId id) const;

#pragma endregion

#pragma region Coroutines

	private:
		//eastl::unordered_map<CoroutineId, Coroutine*> m_coroutines;
	public:
		//CoroutineId StartCoroutine(Coroutine* pCoroutine);
		//void StopCoroutine(CoroutineId id);

#pragma endregion


#pragma region Networking

	private:
		bool m_isSynced; // Wether this object is synced on the network.

		bool m_netDirty; // Set to false when anything about the game object changes such as : Destroy, Add/Remove Component, Activeness, Parenting etc.
		unsigned int m_netOwnerId; // The owner id of this gameobject see : {DragonNet::ClientID}

		unsigned int m_priorityWeight; // Default is 1, Higher weight = more updates.

	public:

		//virtual void Synchronize(NetworkMessage& message);
		//virtual void Replicate(NetworkMessage& message);

		//bool IsNetOwner() const; // Detects wether the current GameObject is owned by the current client.
		//void SetNetOwner(int id) const; // The server is the only one who is allowed to set this value.


#pragma endregion

#pragma region Serialization

		// Inherited via ISerializable
		virtual void Serialize(OutStream& out) override;

		virtual void Deserialize(InStream& in) override;

#pragma endregion

		// Creates a game object with a specific id.
		static GameObject Create(GameObjectId id);

	private:
		GameObject()
			: m_active(true)
			, m_id(0)
		{}
	};

#pragma region Component

	// Get

	template<typename ComponentType>
	inline ComponentType* GameObject::GetComponent() const
	{
		if (auto result = m_components.find(ComponentType::Identifier); result != m_components.end())
		{
			return static_cast<ComponentType*>((*result).second);
		}

		return nullptr;
	}

	// Add

	template<typename ComponentType, typename ...Args>
	inline ComponentType* GameObject::AddComponent(Args&&... args)
	{
		if (auto result = m_components.find(ComponentType::Identifier); result != m_components.end())
		{
			auto it = m_components.emplace(ComponentType::Identifier, ComponentType { args... });
			return static_cast<ComponentType*>(((*it.first).second));
		}
		else
		{
			WARN("[GameObject] Trying to add an already existing component to the GameObject, ID: %u", m_id);
			return static_cast<ComponentType*>(result->second);
		}
	}

	template<typename ComponentType>
	inline ComponentType* GameObject::AddComponent(const ComponentType& comp)
	{
		if (auto result = m_components.find(ComponentType::Identifier); result != m_components.end())
		{
			auto it = m_components.emplace(ComponentType::Identifier, comp);
			return static_cast<ComponentType*>(((*it.first).second));
		}
		else
		{
			WARN("[GameObject] Trying to add an already existing component to the GameObject, ID: %u", m_id);
			return static_cast<ComponentType*>(result->second);
		}
	}

	// Has

	template<typename ComponentType>
	inline bool GameObject::HasComponent() const
	{
		return m_components.find(ComponentType::Identifier) != m_component.end();
	}

#pragma endregion

};