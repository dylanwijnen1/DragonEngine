#pragma once

#include <Dragon/Graphics/RenderTarget.h>

namespace dragon
{
	class Window;

	class Graphics : public RenderTarget
	{
		Window* m_pWindow;

	public:

		Graphics() : m_pWindow(nullptr) {}
		Graphics(Window* pWindow) : m_pWindow(pWindow) {}
		virtual ~Graphics() {}

		virtual bool Init(Window* pWindow, Vector2f size);

		void Display();

		// Abstract RenderTarget Functions.
		virtual void Clear(Color color) override = 0;
		virtual void* GetNativeTarget() override = 0;

		// Override Init() from RenderTarget and mark it final.
		bool Init(Vector2f size) final override;
	};

}