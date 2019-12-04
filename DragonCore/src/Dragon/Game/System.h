#pragma once

#include <EASTL/type_traits.h>
#include <type_traits>

#include <Dragon/Game/EntityManager.h>

#include <type_traits>

namespace dragon
{
	class RenderTarget;

	// SystemInterface
	class ISystem
	{
	public:
		// Required Functionality
		virtual void Update(EntityManager& manager, float deltaTime) = 0;

		// Non Required Functionality
		virtual void FixedUpdate(EntityManager& manager, float deltaTime) = 0;

		// Render Functions Only Render. Update can take care of building 
		virtual void Render(EntityManager& manager, RenderTarget& target) = 0;
	};

	template<typename Impl, typename... Components>
	class System : public ISystem
	{
		static inline constexpr int m_kSize = sizeof...(Components);
		Impl m_impl;

	public:

		//using View = EntityView<Components...>;
		using View = int;

		void Update(EntityManager& manager, float deltaTime) final override 
		{
			auto entities = manager.GetEntities<Components...>();
			for (Entity entity : entities)
			{
				if constexpr (m_kSize > 0)
				{
					m_impl.Update(manager, entity, manager.GetEntityView<Components...>(entity), deltaTime);
				}
				else
				{
					m_impl.Update(manager, entity, deltaTime);
				}

			}
		}

		void FixedUpdate(EntityManager& manager, float deltaTime) final override
		{
			auto entities = manager.GetEntities<Components...>();
			for (Entity entity : entities)
			{
				if constexpr (m_kSize > 0)
				{
					m_impl.FixedUpdate(manager, entity, manager.GetEntityView<Components...>(entity), deltaTime);
				}
				else
				{
					m_impl.FixedUpdate(manager, entity, deltaTime);
				}
			}
		}

		void Render(EntityManager& manager, RenderTarget& target) final override 
		{
			auto entities = manager.GetEntities<Components...>();
			for (Entity entity : entities)
			{
				if constexpr (m_kSize > 0)
				{
					m_impl.Render(manager, entity, manager.GetEntityView<Components...>(entity), target);
				}
				else
				{
					m_impl.Render(manager, entity, target);
				}
			}
		}
	};

}

