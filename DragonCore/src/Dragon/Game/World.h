#pragma once

#include <Dragon/Config.h>

#include <Dragon/Graphics/RenderTarget.h>

#include <EASTL/vector.h>

namespace dragon
{

	/// <summary>
	/// ECS System and thought process
	/// 
	/// World : Responsible of managing systems, entities and components.
	///		Entities : Just an integer, the most upper bit is used for enabling/disabling of the entity.
	///		- Entity CreateEntity()
	///		- Entity CreateEntity<Archetype>(...)
	///		- Entity CreateEntity<Components...>(...)
	///		- RemoveEntity(Entity id)
	///		- DisableEntity(Entity id), Disables the entity (sets flag in the entity id)
	///		- EnableEntity(Entity id), Enables the entity (sets flag in the entity id)
	/// 
	///		Components : These are generally POD structs, they must be default constructible in order to be registered.
	///		- RegisterComponent<Component>(), Registers the component with the world.
	///		- AddComponent<Component>(Entity id);
	///		- AddComponent<Component>(Entity id, Args...);
	///		- AddComponent(ComponentHash hash), Only if the component has been registered.
	///		- RemoveComponent<Component>(Entity id);
	///		- RemoveComponent(ComponentHash hash);
	/// 
	///		Systems : 
	/// 
	///			Should systems get system events???
	///			
	///		- AddSystem<System>();
	///		- AddSystem<System>(...);
	///		- AddSystem(System*);
	///		- RemoveSystem<System>();
	/// </summary>
	/// 
	/// <Components>
	///		
	///		Even though components in ECS are traditionally just data we
	///		might want to add some functionality for components such as serialization, cloning, etc.
	///		These functions are not required to be implemented on each component and if they do not exist they will not be called. 
	///		Example of functionality we would want to support :
	///			- Load(InStream&), Save(OutStream&)
	///			- Init(World&, Entity) // BeforeAttach
	///			- PostInit(World&, Entity) // AfterAttach
	///			- Clone(World&, Entity) 
	/// 
	/// </Components>

	class System;
	class RenderableSystem;
	class ComponentSet;
	class World
	{
		const Entity m_kInvalidEntity = 0;

		using Entities = eastl::vector<Entity>;
		Entities m_entities;

		using SystemID = size_t;
		using ComponentHash = uint64_t;

		eastl::hash_map<SystemID, System*> m_systems;
		eastl::hash_map<SystemID, RenderableSystem*> m_renderableSystems;

		eastl::hash_map<ComponentHash, ComponentSet*> m_components;
		
	public:

		World() = default;
		~World() = default;

		/// Copying is not ok, This is a slow operation, Moving is fair game.
		World(const World&) = delete;
		World(World&&) = default;
		World& operator=(const World&) = delete;
		World& operator=(World&&) = default;

		void Update(float dt);
		void Render(RenderTarget& target);

#pragma region Entities

		Entity CreateEntity();

		// Create an entity from an entity definition, Basically includes a lpp::LuaVar and a resource id so that we can keep track of entities and their resources
		//Entity CreateEntity(EntityResource definition);

		//template<typename ArcheType>
		//Entity CreateEntity(typename ArcheType::Args... args)
		//{
		//	
		//}

		template<typename... Components>
		Entity CreateEntity(Components&&... comps);

		void RemoveEntity(Entity id);
		
		//
		// Utility Functions
		//

		void DisableEntity(Entity id);
		void EnableEntity(Entity id);

		Entity CloneEntity(Entity id);

		bool IsValidEntity(Entity id) { return id != m_kInvalidEntity; }

		// Check if entity exists in the world.
		bool EntityExists(Entity id);

		template<typename... Components>
		Entities GetEntityView() const
		{
			// TODO: Do actual implementation.
			return m_entities;
		}

#pragma endregion

#pragma region Components

		template<typename Component>
		void RegisterComponent()
		{
			// TODO: Register to a global m_componentFactory.
			auto result = m_registeredComponents.find(Component::Identifier);
			if (result == m_registeredComponents.end())
			{
				// Create a function for the construction of this component.
				s_registeredComponent[Component::Identifier] = []() -> Component 
				{
					return Component();
				}
			}
		}

		template<typename Component>
		Component& AddComponent(Entity id)
		{
			return m_components[Component::Identifier].Add(id);
		}

		template<typename Component, typename... Args>
		Component& AddComponent(Entity id, Args... args)
		{
			return m_components[Component::Identifier].Add(id, eastl::forward<Args>(args)...);
		}

		void AddComponent(Entity id, ComponentHash hash)
		{
			//m_components[hash].Add(id, s_registeredComponent[hash]());
		}

		template<typename Component>
		void RemoveComponent(Entity id);

		void RemoveComponent(Entity id, ComponentHash hash);

		template<typename Component>
		bool HasComponent(Entity id) const
		{
			HasComponent(id, Component::Identifier);
		}

		bool HasComponent(Entity id, ComponentHash) const;

#pragma endregion

#pragma region System

		//template<typename System>
		//void AddSystem();

		//template<typename System, typename... Args>
		//void AddSystem<System>(Args&&... args);

		//void AddSystem(System*);

		//template<typename System>
		//void RemoveSystem();

		//void RemoveSystem(SystemID id);

		//System* GetSystem(SystemID id) const;

		//template<typename System>
		//System* GetSystem() const;

#pragma endregion

#pragma region Serialization

		/// <summary>
		/// The world will serialize each component and its current data to a stream
		/// If the component has not overridden the IO methods it will parse its raw binary data.
		/// NOTE: This will also copy pointers, And can cause errors it is recommended to invalidate pointers upon load.
		/// </summary>

#pragma endregion


	};

}