#pragma once

#include <Dragon/Config.h>
#include <Dragon/Generic/Handle.h>
#include <Dragon/Game/Components.h>

#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/priority_queue.h>


namespace dragon
{
	using ComponentId = EntitySize;

	class RenderTarget;

	/// <summary>
	/// ECS System and thought process
	/// 
	/// EntityManager : Responsible of managing systems, entities and components.
	///		Entities : Just an integer, the most upper bit is used for enabling/disabling of the entity.
	///		- Entity CreateEntity()
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
	///			- Init(EntityManager&, Entity) // BeforeAttach
	///			- PostInit(EntityManager&, Entity) // AfterAttach
	///			- Clone(EntityManager&, Entity) 
	/// 
	/// </Components>

	class ISystem;
	class IComponentSet;
	class EntityManager
	{
	public:

		using Entity = Handle<EntitySize>;
		using Entities = eastl::vector<Entity>;
		using Components = eastl::unordered_map<ComponentId, IComponentSet*>;
		using Systems = eastl::unordered_map<size_t, ISystem*>;

	private:

		Entities m_entities;
		Entities m_sparse;

		using EntityStatus = eastl::vector<bool>;
		EntityStatus m_entityStatus;

		Systems m_systems;
		Systems m_renderableSystems;

		Components m_components;

		using FreeList = eastl::priority_queue<Entity>;
		FreeList m_freeEntities;
		
	public:

		template<typename... Components>
		class EntityView
		{
			Entities::iterator m_begin;
			Entities::iterator m_end;
			EntityManager* m_pManager;

			// TODO: Create custom iterator that returns the components in a wrapper.
			//		 for(wrapper : EntityView)
			//			wrapper.GetComponent<Component>();

		public:

			EntityView(EntityManager* pManager, Entities::iterator begin, Entities::iterator end)
				: m_begin(begin)
				, m_end(end)
				, m_current(begin)
				, m_pManager(pManager)
			{}

			auto begin() { return m_begin; }
			auto end() { return m_end; }

			// TODO: Remove once component wrapped iterator is finished.
			template<typename Component>
			const Component& GetComponent()
			{
				return m_pManager->GetComponent<Component>();
			}

			template<typename Component>
			Component& GetComponent()
			{
				return m_pManager->GetComponent<Component>();
			}
		};

		EntityManager() = default;
		~EntityManager() = default;

		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;

		// Moving is ok, But generally discouraged. Use Move specifically.
		EntityManager(EntityManager&&) = delete;
		// Moving is ok, But generally discouraged. Use Move specifically.
		EntityManager& operator=(EntityManager&&) = delete;

		void Move(EntityManager&& other);

		void Update(float dt);
		void FixedUpdate(float dt);
		void Render(RenderTarget& target);

#pragma region Entities

		/// <summary>
		/// Creates an entity and enables it.
		/// </summary>
		Entity CreateEntity();

		// Create an entity from an entity definition, Basically includes a lpp::LuaVar and a resource id so that we can keep track of entities and their resources
		//Entity CreateEntity(const EntityResource& resource);

		template<typename... Components>
		Entity CreateEntity(Components&&... components)
		{
			Entity entity = CreateEntity();
			EmplaceComponentRecurse<Components>(entity, eastl::forward<Components>(components)...);
			return entity;
		}

		template<typename... Components>
		Entity CreateEntity()
		{
			Entity entity = CreateEntity();
			EmplaceComponentRecurse<Components>(entity, Components()...);
			return entity;
		}

		void RemoveEntity(Entity id);
		
		//
		// Utility Functions
		//

		void DisableEntity(Entity entity);
		void EnableEntity(Entity entity);

		// Creates a clone of an entity.
		Entity CloneEntity(Entity entity);

		// Check if entity exists in the world.
		bool ContainsEntity(Entity entity) const;

		template<typename... Components>
		EntityView<Components...> GetEntities()
		{
			if constexpr (sizeof(Components)... > 0)
			{
				// Determine smallest set of entities based on given components.
				IComponentSet* pSmallestSet = GetSmallestComponentSet<Components...>();

				// Construct EntityView from smallest set.
				return EntityView<Components...>(pSmallestSet->begin(), pSmallestSet->end());
			}
			else
			{
				return EntityView<Components...>(m_entities.begin(), m_entities.end());
			}
		}

#pragma endregion

#pragma region Components

		template<typename Component>
		void AddComponent(Entity entity)
		{
			AddComponent(entity, GetComponentIdentifier<Component>());
		}

		void AddComponent(Entity entity, ComponentId componentId);

		template<typename Component>
		void AddComponent(Entity entity, const Component& component)
		{
			size_t componentIndex = GetComponentIdentifier<Component>();
			IComponentSet* pIComponents = m_components[componentIndex];
			assert(pIComponents != nullptr);
			auto pSet = CastSet<Component>(pIComponents);
			pSet->Add(entity, component);
		}

		template<typename Component, typename... Args>
		void EmplaceComponent(Entity entity, Args... args)
		{
			size_t componentIndex = GetComponentIdentifier<Component>();
			IComponentSet* pIComponents = m_components[componentIndex];
			assert(pIComponents != nullptr);
			auto pSet = CastSet<Component>(pIComponents);
			pSet->Emplace(entity, eastl::forward<Args>(args)...);
		}

		template<typename Component>
		void RemoveComponent(Entity entity)
		{
			RemoveComponent(entity, GetComponentIdentifier<Component>());
		}

		void RemoveComponent(Entity entity, ComponentId componentId);

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

	private:

		template<typename Component>
		ComponentSet<Component>* CastSet(IComponentSet* pSet)
		{
			return static_cast<ComponentSet<Component>*>(pSet);
		}

		template<typename Component, typename... Components>
		void EmplaceComponentRecurse(Entity entity, Component&& component, Components&&... components)
		{
			EmplaceComponent<Component>(entity, eastl::forward<Component>(component));
			EmplaceComponentRecurse<Components...>(entity, eastl::forward<Components>(components)...);
		}

		template<typename... Component>
		IComponentSet* GetSmallestComponentSet()
		{
			IComponentSet* pLeast = eastl::min(GetComponentSet<Components>()..., [](IComponentSet* pLeft, IComponentSet* pRight) {
				return pLeft->Size() < pRight->Size();
			});

			return pLeast;
		}

		template<typename Component>
		IComponentSet* GetComponentSet()
		{
			return m_components[(size_t)GetComponentIdentifier<Component>()];
		}

	};

}