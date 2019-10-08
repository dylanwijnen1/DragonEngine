#pragma once

#include <Dragon/Graphics/RenderTarget.h>

namespace dragon
{

	class DragonGraphics : public RenderTarget
	{
	public:
		DragonGraphics() = default;
		~DragonGraphics() = default;

		DragonGraphics(const DragonGraphics&) = default;
		DragonGraphics(DragonGraphics&&) = default;
		DragonGraphics& operator=(const DragonGraphics&) = default;
		DragonGraphics& operator=(DragonGraphics&&) = default;

	protected:
		// Inherited via RenderTarget
		virtual void OnResize(Vector2f size) override;

	};

}