#pragma once

#include <stdint.h>
#include <cstddef>


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

#define FORWARD_DECLARE_RENDERSKIN_TYPE(Type, Prefix) \
    template<typename Impl> class _##Type; \
    using Type = _##Type<class Prefix##Type>

namespace dragon
{
	using Entity = uint32_t;
	using Byte = std::byte;

	// TODO: Possibly forward declare the RENDERSKIN specific Rendering classes with aliases.
	//		 This could confuse users with intellisense giving more options. A factory method on the class would mitigage this problem.
	//		 RenderTexture::Create(...); Texture::Create(...); Sprite::Create(...);
};