#include "GameObject.h"

#include <Dragon/Game/Scene.h>
#include <Dragon/Game/DragonComponentFactory.h>
#include <Dragon/Generic/Serialization/InStream.h>
#include <Dragon/Generic/Serialization/OutStream.h>

namespace dragon
{
	GameObject::~GameObject()
	{
		// Delete all components.
		for (auto pair : m_components)
			delete pair.second;
	}

	void GameObject::Destroy()
	{
		m_pWorld->Remove(this->m_id);
	}

	GameObject* GameObject::Clone() const
	{
		if (m_pWorld)
		{
			return m_pWorld->Add(*this);
		}
		else
		{
			DWARN("[GameObject] Trying to clone a gameobject not associated with a world.");
			return nullptr;
		}
	}

	GameObject* GameObject::Clone(Scene* pWorld) const
	{
		if (pWorld)
		{
			return pWorld->Add(*this);
		}
		else
		{
			DWARN("[GameObject] Trying to clone a gameobject to an invalid world.");
			return nullptr;
		}
	}

	Component* GameObject::GetComponent(ComponentId id) const
	{
		if (auto result = m_components.find(id); result != m_components.end())
		{
			return (*result).second;
		}

		return nullptr;
	}

	Component* GameObject::AddComponent(ComponentId id)
	{
		if (auto result = m_components.find(id); result != m_components.end())
		{
			if (Component* pComponent = DragonComponentFactory::GetInstance().CreateComponent(id); pComponent != nullptr)
			{
				m_components.emplace(id, pComponent);
				return pComponent;
			}

			DWARN("[GameObject] Component id {%u} could not be created.", id);
			return nullptr;
		}
		else
		{
			DWARN("[GameObject] Trying to add an already existing component to the GameObject, ID: %u", m_id);
			return result->second;
		}

		return nullptr;
	}

	void GameObject::RemoveComponent(ComponentId id)
	{
		m_components.erase(id);
	}

	bool GameObject::HasComponent(ComponentId id) const
	{
		return m_components.find(id) != m_components.end();
	}

	//void GameObject::Synchronize(NetworkMessage& message)
	//{
	//	//message.Write(m_id)
	//	
	//	//message.Write(m_netDirty);
	//	//if (m_netDirty)
	//		//message.Write()

	//	//message.Write(m_components.count())
	//	for (auto pair : m_components)
	//	{
	//		//message.Write(pair.first)
	//		pair.second->Synchronize(message);
	//	}
	//}

	//void GameObject::Replicate(NetworkMessage& message)
	//{
	//	// Game Object

	//	// Components
	//	
	//	// count = message.Read<int>()
	//	// foreach component
	//		//identifier = message.Read<ComponentId>()
	//		//state = message.Read<std::byte>()

	//		//if state == new
	//			// pComponent = AddComponent(ComponentBuilder::FromIdentifier(identifier));
	//			// pComponent->Replicate(message);
	//		//else if state == update
	//			// pComponent->Replicate(message);
	//		//else if state == destroy
	//			// RemoveComponent(identifier);
	//}

	void GameObject::Serialize(OutStream& out)
	{
		out.Write(m_components.size());

		for (auto pair : m_components)
		{
			out.Write(pair.second->GetIdentifier());
			pair.second->Serialize(out);
		}
	}

	void GameObject::Deserialize(InStream& in)
	{
		ComponentId count = in.Read<ComponentId>();

		for (ComponentId index = 0; index < count; ++index)
		{
			ComponentId compId = in.Read<ComponentId>();
			Component* pComponent = DragonComponentFactory::GetInstance().CreateComponent(compId);
			m_components.emplace(compId, pComponent);
			pComponent->SetOwner(this);
			pComponent->Deserialize(in);
		}
		
	}

	GameObject GameObject::Create(GameObjectId id)
	{
		GameObject obj;
		obj.m_id = id;
		return obj;
	}

	GameObject::GameObject(const GameObject& other)
	{
		for (auto pair : other.m_components)
		{
			ComponentId id = pair.second->GetIdentifier();
			Component* pComponent = GetComponent(id);
			
			if (!pComponent)
			{
				auto result = m_components.emplace(id, pair.second->Clone());
				pComponent = (*result.first).second;
			}
			
			pComponent->SetOwner(this);
			pComponent->Init(pair.second);
		}

		for (auto pair : other.m_components)
		{
			pair.second->PostInit(pair.second);
		}
	}

	GameObject& GameObject::operator=(const GameObject& other)
	{
		for (auto pair : other.m_components)
		{
			ComponentId id = pair.second->GetIdentifier();
			Component* pComponent = GetComponent(id);

			if (!pComponent)
			{
				auto result = m_components.emplace(id, pair.second->Clone());
				pComponent = (*result.first).second;
			}

			pComponent->SetOwner(this);
			pComponent->Init(pair.second);
		}

		for (auto pair : other.m_components)
		{
			pair.second->PostInit(pair.second);
		}

		return *this;
	}

}
