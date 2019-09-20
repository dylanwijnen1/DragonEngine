#pragma once

#include <Dragon/Graphics/RenderState.h>

namespace dragon
{

	class Renderable
	{
	protected:
		friend class RenderTarget;
		virtual void Render(RenderTarget& target, RenderState state = RenderState::Default) const = 0;
	};

}