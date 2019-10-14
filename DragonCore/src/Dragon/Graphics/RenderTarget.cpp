#include "RenderTarget.h"

#include <Dragon/Graphics/Renderable.h>

bool dragon::RenderTarget::Init(Vector2f size)
{
	m_size = size;
	m_camera.m_size = size;
	m_camera.m_position = { size.x / 2.0f, size.y / 2.0f };
	m_camera.m_viewport = { 0.f, 0.f, 1.0f, 1.0f };
	return true;
}

void dragon::RenderTarget::Draw(Renderable& renderable)
{
	renderable.Render(*this);
}
