#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Graphics/Renderable.h>

namespace dragon
{

	class RenderComponent : public Component, public Renderable
	{
		virtual bool Init() override;

	protected:
		// Renderable
		virtual void Render(RenderTarget& target, RenderState state) const override = 0;
	};

}