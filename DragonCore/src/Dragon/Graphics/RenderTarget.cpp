#include "RenderTarget.h"

#include <Dragon/Graphics/Drawable.h>
#include <Dragon/Graphics/Texture.h>

namespace dragon
{

	void RenderTarget::Draw(const Drawable& drawable) const
	{
		drawable.Draw(*this, m_renderState);
	}

}
