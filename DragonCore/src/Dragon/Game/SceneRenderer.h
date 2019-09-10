#pragma once

#include <Dragon/Game/Component.h>

#include <EASTL/vector.h>

namespace dragon
{

	class RenderComponent;

	class SceneRenderer
	{

		using RenderComponents = eastl::vector<RenderComponent*>;
		RenderComponents m_renderables;

	public:
		SceneRenderer() = default;
		~SceneRenderer() = default;

		SceneRenderer(const SceneRenderer&) = default;
		SceneRenderer(SceneRenderer&&) = default;
		SceneRenderer& operator=(const SceneRenderer&) = default;
		SceneRenderer& operator=(SceneRenderer&&) = default;

		virtual void Render(class RenderTarget& target);

		void AddRenderable(RenderComponent* pRenderComponent);
	};

}