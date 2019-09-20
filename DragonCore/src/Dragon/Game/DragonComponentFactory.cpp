#include "DragonComponentFactory.h"
#include <Generic/StringHash.h>

#include <Dragon/Application/Debugging/Debug.h>

#pragma region Engine Components

#pragma endregion

#define CASE_COMPONENT(CLASS) case #CLASS##_hash: return new CLASS

namespace dragon
{
	Component* DragonComponentFactory::CreateComponent(ComponentId id)
	{
		Component* pComponent = nullptr;

		// Engine level components
		switch (id)
		{
#if defined(ENGINE_COMPONENTS)
		ENGINE_COMPONENTS
#endif
		default:
			pComponent = nullptr;
		}

		// Game level components
		pComponent = m_pGameFactory->CreateComponent();
		
		// TODO: Scriptable Components.
		// Script level components
		// pComponent = m_createScriptComponent(); // LuaVar::Call();

		if (!pComponent)
		{
			WARN("[DragonComponentFactory] Could not create component with the id of %u", id);
		}


		return nullptr;
	}

}
