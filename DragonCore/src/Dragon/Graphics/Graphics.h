#pragma once

#include <Dragon/Graphics/RenderTarget.h>
#include <Dragon/Application/Window/Window.h>

namespace dragon
{

	template<typename Impl>
	class _Graphics : public RenderTarget
	{
		Impl m_impl;

	public:

		_Graphics() = default;
		_Graphics(Window* pWindow)
			: m_impl(pWindow)
		{}

		~_Graphics() = default;

		bool Init(Window* pWindow, Vector2f size)
		{
			if (!pWindow)
				return false;

			SetWindow(pWindow);

			return Init(size);
		}

		void Display() { m_impl.Display(); }

		virtual Vector2f GetSize() const final override	{ return m_impl.GetSize(); }

		virtual void SetSize(Vector2f size) final override { m_impl.SetSize(size); }

		virtual void Clear(Color color) final override { m_impl.Clear(color); }

		virtual void SetCamera(Camera camera) final override { m_impl.SetCamera(camera); }

		virtual Camera GetCamera() const final override { return m_impl.GetCamera(); }

		virtual void* GetNativeTarget() final override { return m_impl.GetNativeTarget(); }

	private:

		// Hide Inherited Member Init() from RenderTarget
		virtual bool Init(Vector2f size) final override { return m_impl.Init(size); }

		void SetWindow(Window* pWindow) { m_impl.SetWindow(pWindow); }
	};

}

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML
	
#include <Platform/SFML/Graphics/SfmlGraphics.h>
//namespace dragon
//{
//	using Graphics = _Graphics<SfmlGraphics>;
//}

#endif