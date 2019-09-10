#include "SceneRenderer.h"

#include <Dragon/Graphics/Components/RenderComponent.h>
#include <Dragon/Game/GameObject.h>
#include <Dragon/Application/Debugging/Debug.h>

#include <EASTL/sort.h>

namespace dragon
{

	void SceneRenderer::Render(RenderTarget& target)
	{
		// TODO: Add sorting layer. Add any axis ordering. Use Y-Axis by default.
		/*eastl::sort(m_renderables.begin(), m_renderables.end(), [](RenderComponent* left, RenderComponent* right) {
			if (left->GetOwner()->GetPosition().y < right->GetOwner()->GetPosition().y)
				return left;
		});*/

		for (auto it = m_renderables.begin(); it != m_renderables.end();)
		{
			RenderComponent* pRenderable = (*it);

			if (pRenderable)
			{
				pRenderable->Render(target);
				++it;
			}
			else
			{
				it = m_renderables.erase(it);
			}
		}
	}

	void SceneRenderer::AddRenderable(RenderComponent* pRenderComponent)
	{
#if DRAGON_DEBUG
		// Check for duplicates.
		auto result = eastl::find(m_renderables.begin(), m_renderables.end(), pRenderComponent);
		if (result != m_renderables.end())
		{
			WARN("Renderable already added to the Renderer.");
		}
#endif

		m_renderables.push_back(pRenderComponent);
	}

}

