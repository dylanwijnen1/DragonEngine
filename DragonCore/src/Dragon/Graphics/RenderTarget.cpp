#include "RenderTarget.h"

#include <Dragon/Graphics/Renderable.h>
#include <Dragon/Graphics/Texture.h>

namespace dragon
{

	void RenderTarget::Draw(const Renderable& renderable, const RenderState& state)
	{
		renderable.Render(*this, state);
	}

}
