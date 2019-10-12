#include "Window.h"

#include <Dragon/Config.h>
#include <Dragon/Graphics/Graphics.h>

namespace dragon
{
	Graphics* Window::CreateGraphics()
	{
#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		return new Graphics();
#else
		return nullptr;
#endif
	}
}
