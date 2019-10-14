#include "Graphics.h"

#include <Dragon/Application/Window/Window.h>

namespace dragon
{

	bool Graphics::Init(Window* pWindow, Vector2f size)
	{
		if (!pWindow)
			return false;

		m_pWindow = pWindow;

		return Init(size);
	}

	void Graphics::Display()
	{
		// Swap buffer from backbuffer to window buffer.
		m_pWindow->SwapBuffers();
	}

	bool Graphics::Init(Vector2f size)
	{
		return RenderTarget::Init(size);
	}

}