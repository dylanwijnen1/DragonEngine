#include "RenderTarget.h"

#include <Dragon/Graphics/Renderable.h>

bool dragon::RenderTarget::Init(Vector2f size)
{
	m_size = size;
	return true;
}

void dragon::RenderTarget::Draw(Renderable& renderable)
{
	renderable.Render(*this, m_states);
}
