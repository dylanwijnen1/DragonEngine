#pragma once

#include <Dragon/Game/Component.h>

namespace dragon
{
	class IComponentFactory
	{
	public:
		virtual Component* CreateComponent() = 0;
	};

	class DragonComponentFactory
	{
	private:
		IComponentFactory* m_pGameFactory;

		DragonComponentFactory() 
			: m_pGameFactory(nullptr)
		{}

		~DragonComponentFactory() = default;

	public:
		static auto& GetInstance()
		{
			static DragonComponentFactory instance;
			return instance;
		}

		DragonComponentFactory(const DragonComponentFactory&) = delete;
		DragonComponentFactory(DragonComponentFactory&&) = delete;
		DragonComponentFactory& operator=(const DragonComponentFactory&) = delete;
		DragonComponentFactory& operator=(DragonComponentFactory&&) = delete;

		Component* CreateComponent(ComponentId id);

		void SetComponentFactory(IComponentFactory* pFactory) { m_pGameFactory = pFactory; }
	};

}