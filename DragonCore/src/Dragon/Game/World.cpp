#include "World.h"

//#include <Dragon/Game/System.h>
//#include <Dragon/Game/Component.h>

namespace dragon
{
	void World::Update(float dt)
	{
		for (auto [id, system] : m_systems)
		{
			//system->Update(*this, dt); // Internally calls World->Each<Components...>(dt, entity, comps);
		}
	}

	void World::Render(RenderTarget& target)
	{
		for (auto [id, system] : m_systems)
		{
			//system->Render(*this, target); // Internally calls World->Each<Components...>(target, entity, comps);
		}
	}
}
