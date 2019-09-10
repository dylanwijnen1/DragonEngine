#pragma once

#include <Dragon/Graphics/RenderState.h>

namespace dragon
{

	class Renderable
	{
	protected:
		friend class RenderTarget;
		virtual void Render(const RenderTarget& target, const RenderState& state) const = 0;
	};

}