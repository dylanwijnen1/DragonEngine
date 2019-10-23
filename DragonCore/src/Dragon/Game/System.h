#pragma once

#include <EASTL/type_traits.h>
#include <type_traits>

#include <Dragon/Game/World.h>

#include <type_traits>

namespace dragon
{
	class RenderTarget;

	template<typename T, typename... Args>
	struct HasUpdateFunction
	{
		template<typename U, void(U::*)(World&, Entity, float, Args...)> struct SFINAE {};
		template<typename U> static char Test(SFINAE<U, &U::Update>*);
		template<typename U> static int Test(...);
		constexpr bool value = sizeof(Test<T>(0)) == sizeof(char);
	};

	template<typename T, typename... Args>
	struct HasFixedUpdateFunction
	{
		template<typename U, void(U::*)(World&, Entity, float, Args...)> struct SFINAE {};
		template<typename U> static char Test(SFINAE<U, &U::FixedUpdate>*);
		template<typename U> static int Test(...);
		constexpr bool value = sizeof(Test<T>(0)) == sizeof(char);
	};

	template<typename T, typename... Args>
	struct HasRenderFunction
	{
		template<typename U, void(U::*)(World&, Entity, RenderTarget&, Args...)> struct SFINAE {};
		template<typename U> static char Test(SFINAE<U, &U::Render>*);
		template<typename U> static int Test(...);
		constexpr bool value = sizeof(Test<T>(0)) == sizeof(char);
	};


	// SystemInterface
	class ISystem
	{
		// Required Functionality
		virtual void Update(World& world, float deltaTime) = 0;

		// Non Required Functionality
		virtual void FixedUpdate(World& world, float deltaTime) = 0;

		// Render Functions Only Render. Update can take care of building 
		virtual void Render(const World& world, RenderTarget& target) const = 0;
	};

	template<typename Impl, typename... Components>
	class System : public ISystem
	{
		//static constexpr int m_kSize = sizeof...(Components);
		Impl m_impl;

	public:

		void Update(World& world, float deltaTime) final override 
		{
			if constexpr (HasUpdateFunction<Impl, Components...>::value)
			{
				auto entities = world.GetEntityView<Components...>();
				for (Entity entity : entities)
				{
					m_impl.Update(world, entity, deltaTime, world.GetComponent<Components>(entity)...);
				}
			}
		}

		void FixedUpdate(World& world, float deltaTime) final override
		{
			if constexpr (HasFixedUpdateFunction<Impl, Components...>::value)
			{
				auto entities = world.GetEntities<Components...>();
				for (Entity entity : entities)
				{
					m_impl.FixedUpdate(world, entity, deltaTime, world.GetComponent<Components>(entity)...);
				}
			}
		}

		void Render(const World& world, RenderTarget& target) const final override 
		{
			if constexpr (HasRenderFunction<Impl, Components...>::value)
			{
				auto entities = world.GetEntities<Components...>();
				for (Entity entity : entities)
				{
					m_impl.Render(world, entity, target, world.GetComponent<Components>(entity)...);
				}
			}
		}
	};

	class FooSystem : public System<FooSystem, int>
	{
	public:
		void Update(World& world, Entity entity, float t, int i) 
		{}

		void FixedUpdate(World& world, Entity entity, float dt, int i)
		{}

		void Render(const World& world, Entity entity, RenderTarget& target, int i)
		{}
	};

}

