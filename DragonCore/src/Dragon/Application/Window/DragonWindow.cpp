#include "DragonWindow.h"

#include <Dragon/Config.h>

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML
	#include <Platform/SFML/Graphics/SfmlGraphics.h>
	using GraphicsImpl = sf::SfmlGraphics;
#endif

namespace dragon
{
	DragonGraphics* DragonWindow::CreateGraphics()
	{
#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		return new GraphicsImpl();
#else
		return nullptr;
#endif
	}
}
