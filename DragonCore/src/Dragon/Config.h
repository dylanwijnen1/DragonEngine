#pragma once

#include <Dragon/Application/Debugging/Debug.h>
#include <Dragon/Generic/Math.h>

#include <stdint.h>

#define DRAGON_RENDERSKIN_NONE 0
#define DRAGON_RENDERSKIN_SFML 1

// TODO: Should be defined by premake
#define DRAGON_RENDERSKIN DRAGON_RENDERSKIN_SFML
#ifndef DRAGON_RENDERSKIN
	#define DRAGON_RENDERSKIN DRAGON_RENDERSKIN_NONE
#endif

#define DRAGON_APP_NAME "DragonApplication"

// TODO: These are default settings, this should only be used if the "gameapp.settings" have not specified the width/height of the window
#define DRAGON_WINDOW_WIDTH 1280
#define DRAGON_WINDOW_HEIGHT 768

namespace dragon
{
	using Entity = uint32_t;
	using Byte = std::byte;
}