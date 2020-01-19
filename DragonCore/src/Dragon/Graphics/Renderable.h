#pragma once

#include <Dragon/Config.h>
#include <Dragon/Graphics/RenderStates.h>

namespace dragon
{

	class Renderable
	{
		friend class RenderTarget;

	protected:
		virtual void Render(RenderTarget& target, RenderStates states) = 0;
	};

}