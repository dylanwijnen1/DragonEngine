#pragma once

#include <Dragon/Graphics/RenderState.h>

namespace dragon
{

	class Drawable
	{
	protected:
		friend class RenderTarget;
		virtual void Draw(const RenderTarget& target, RenderState state) const = 0;
	};

}