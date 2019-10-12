#pragma once

#include <Dragon/Graphics/RenderTarget.h>
#include <Dragon/Graphics/Texture.h>

namespace dragon
{

	template<typename Impl>
	class _RenderTexture : public RenderTarget
	{
		Impl m_impl;

		Texture* m_pTexture;

	public:

		_RenderTexture() 
			: m_pTexture(new Texture())
		{}
		~_RenderTexture()
		{
			delete m_pTexture;
		}

		virtual bool Init(Vector2f size) final override { return m_impl.Init(size); }

		void Display() { m_impl.Display(); }

		virtual Vector2f GetSize() const final override { return m_impl.GetSize(); }
		virtual void SetSize(Vector2f size) final override { m_impl.SetSize(size); }

		virtual void Clear(Color color) final override { m_impl.Clear(); }

		virtual void SetCamera(Camera camera) final override { m_impl.SetCamera(camera); }
		virtual Camera GetCamera() const final override { return m_impl.GetCamera(); }

		virtual void* GetNativeTarget() final override { return m_impl.GetNativeTarget(); }

		void* GetNativeTexture() { return m_impl.GetNativeTexture(); }
	};

};


#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML

#include <Platform/SFML/Graphics/SfmlRenderTexture.h>

#endif