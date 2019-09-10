#include "RenderComponent.h"

#include <Dragon/Game/Scene.h>
#include <Dragon/Game/SceneRenderer.h>
#include <Dragon/Game/GameObject.h>

namespace dragon
{

	bool RenderComponent::Init()
	{
		if(GameObject* pOwner = GetOwner())
		{
			if (Scene* pScene = pOwner->GetScene())
			{
				pScene->GetSceneRenderer().AddRenderable(this);
			}
		}

		return true;
	}

}