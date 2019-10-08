#pragma once

#include <Dragon/Graphics/RenderTarget.h>

namespace dragon
{
	class DragonGraphics : public RenderTarget
	{
	private:
		class DragonWindow* m_pWindow;

	public:

		DragonGraphics() = default;
		DragonGraphics(DragonWindow* pWindow, Vector2f size) 
			: m_pWindow(pWindow)
		{}

		virtual ~DragonGraphics() = default;

		DragonGraphics(const DragonGraphics&) = default;
		DragonGraphics(DragonGraphics&&) = default;
		DragonGraphics& operator=(const DragonGraphics&) = default;
		DragonGraphics& operator=(DragonGraphics&&) = default;

		bool Init(DragonWindow* pWindow);

		// Swap buffers from window.
		void Display();
	};
}