#include "Window.h"

#include <Dragon/Config.h>
#include <Dragon/Graphics/Graphics.h>

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML
	#include <Platform/SFML/Graphics/SfmlGraphics.h>
	namespace dragon
	{
		using GraphicsImpl = SfmlGraphics;
	}
#endif

namespace dragon
{
	Graphics* Window::CreateGraphics()
	{
#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		return new GraphicsImpl();
#else
		return nullptr;
#endif
	}
}
