#pragma once

#include <Dragon/Graphics/RenderTarget.h>
#include <Dragon/Graphics/Texture.h>

namespace dragon
{

	template<typename RenderTextureImpl>
	class RenderTexture final : public RenderTarget
	{
		RenderTextureImpl m_impl;

	public:

		RenderTexture();
		virtual ~RenderTexture() 

		/// <summary>
		/// Update texture with current buffer.
		/// </summary>
		virtual void Display() override { m_impl.Display(); }
		
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