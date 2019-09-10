#pragma once

// CONFLICT: Python defines a ssize_t typedef and so does EASTL, however they're not of the same type in x86.

#include <Dragon/Application/Debugging/Debug.h>

#include <stdint.h>

#define DRAGON_RENDERSKIN_NONE 0
#define DRAGON_RENDERSKIN_SFML 1

// TODO: 
#define DRAGON_RENDERSKIN DRAGON_RENDERSKIN_SFML

#ifndef DRAGON_RENDERSKIN
	#define DRAGON_RENDERSKIN DRAGON_RENDERSKIN_NONE
#endif

#define APP_NAME "DragonApplication"

// TODO: These are default settings, this should only be used if the "gameapp.settings" have not specified the width/height of the window
#define DRAGON_WINDOW_WIDTH 1280
#define DRAGON_WINDOW_HEIGHT 768

/// 
/// EASTL Configuration
/// 
