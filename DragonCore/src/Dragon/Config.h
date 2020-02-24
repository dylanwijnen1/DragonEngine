#pragma once

#include <stdint.h>
#include <cstddef>

// Render Skin Definitions
#define DRAGON_RENDERSKIN_NONE 0
#define DRAGON_RENDERSKIN_SFML 1

#ifndef DRAGON_RENDERSKIN
#define DRAGON_RENDERSKIN DRAGON_RENDERSKIN_NONE
#endif

#define DRAGON_APP_NAME "DragonApplication"

// TODO: These are default settings, this should only be used if the application settings have not been specified.
#define DRAGON_WINDOW_WIDTH 1280
#define DRAGON_WINDOW_HEIGHT 768

// Forward Declaring RenderSkin Types.

#define FORWARD_DECLARE_RENDERSKIN_TYPE(Type, Prefix) \
    template<typename Impl> class _##Type; \
    using Type = _##Type<class Prefix##Type>

// Determine renderskin prefix.
#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML
#define FORWARD_RENDERSKIN_TYPE(Type) FORWARD_DECLARE_RENDERSKIN_TYPE(Type, Sfml)
#else
#define FORWARD_RENDERSKIN_TYPE(Type) using Type = nullptr;
#endif

// Aliases
namespace dragon
{
	using Entity = uint32_t;
	using Byte = std::byte;
};