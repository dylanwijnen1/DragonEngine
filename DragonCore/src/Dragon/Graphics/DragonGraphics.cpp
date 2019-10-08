#include "DragonGraphics.h"

#include <Dragon/Application/Window/DragonWindow.h>

bool dragon::DragonGraphics::Init(DragonWindow* pWindow)
{
	if (!pWindow)
		return false;

	m_pWindow = pWindow;

	Vector2 size = pWindow->GetSize();
	return RenderTarget::Init({ (float)size.x, (float)size.y });
}

void dragon::DragonGraphics::Display()
{
	m_pWindow->SwapBuffers();
}
