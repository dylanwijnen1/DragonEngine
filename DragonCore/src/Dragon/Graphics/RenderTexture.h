#pragma once

#include <Dragon/Graphics/RenderTarget.h>
#include <Dragon/Graphics/Texture.h>

namespace dragon
{

	class RenderTexture : public RenderTarget
	{
	public:

		RenderTexture();
		virtual ~RenderTexture();

		/// <summary>
		/// Display the currently drawn buffer to the texture.
		/// </summary>
		virtual void Display() = 0;
		
		// RenderTarget Abstract Functions.
		virtual void Clear(Color color) override = 0;
		virtual void* GetNativeTarget() override = 0;

		/// <summary>
		/// Return a pointer to the texture of this RenderTarget
		/// </summary>
		/// <returns></returns>
		virtual const void* GetNativeTexture() const = 0;
	};

};


#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML

#include <Platform/SFML/Graphics/SfmlRenderTexture.h>

#endif