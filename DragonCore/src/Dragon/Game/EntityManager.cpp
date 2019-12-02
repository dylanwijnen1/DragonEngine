#include "EntityManager.h"

#include <Dragon/Game/System.h>
//#include <Dragon/Game/Component.h>

namespace dragon
{
	using Entity = EntityManager::Entity;

	void EntityManager::Move(EntityManager&& other)
	{
		// Explicit moving.
	}

	void EntityManager::Update(float dt)
	{
		for (auto [id, system] : m_systems)
		{
			system->Update(*this, dt);
		}
	}

	void EntityManager::FixedUpdate(float dt)
	{
		for (auto [id, system] : m_systems)
		{
			system->FixedUpdate(*this, dt);
		}
	}

	void EntityManager::Render(RenderTarget& target)
	{
		for (auto [id, system] : m_systems)
		{
			system->Render(*this, target);
		}
	}

	Entity EntityManager::CreateEntity()
	{
		if (m_freeEntities.size() > 0)
		{
			Entity entity = m_freeEntities.top();
			m_freeEntities.pop();
			return entity;
		}
		else
		{
			size_t entityIndex = m_entities.size();
			Entity entity = entityIndex;
			m_entities.emplace_back(entity);

			// Enable the entity.
			m_entityStatus[entityIndex] = true;
		}
	}

	void EntityManager::RemoveEntity(Entity entity)
	{
		entity.Increment();
		m_freeEntities.emplace(entity);
		m_entities[(size_t)entity.GetId()].Invalidate();
	}

	void EntityManager::DisableEntity(Entity entity)
	{
		if (ContainsEntity(entity))
			m_entityStatus[entity.GetId()] = false;
	}

	void EntityManager::EnableEntity(Entity entity)
	{
		if (ContainsEntity(entity))
			m_entityStatus[entity.GetId()] = true;
	}

	EntityManager::Entity EntityManager::CloneEntity(Entity entity)
	{
		Entity clone = CreateEntity();

		for (auto [id, components] : m_components)
		{
			if(components->Contains(entity))
				components->Clone(entity, clone);
		}

		return clone;
	}

	bool EntityManager::ContainsEntity(Entity entity) const
	{
		return m_sparse[(size_t)entity.GetId()].IsValid();
	}

	// TODO: Assert if entity is valid ?
	void EntityManager::AddComponent(Entity entity, ComponentId componentId)
	{
		size_t componentIndex = componentId;
		assert(m_components[componentIndex] != nullptr);
		m_components[componentIndex]->Add(entity);
	}

	// TODO: Assert if entity is valid ?
	void EntityManager::RemoveComponent(Entity entity, ComponentId componentId)
	{
		size_t componentIndex = componentId;
		assert(m_components[componentIndex] != nullptr);
		m_components[componentIndex]->Remove(entity);
	}

}
