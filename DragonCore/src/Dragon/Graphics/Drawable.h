#pragma once

#include <Dragon/Graphics/RenderState.h>

namespace dragon
{

	class Drawable
	{
	protected:
		friend class RenderTarget;
		virtual void Draw(RenderTarget& target, RenderState state) = 0;
	};

}