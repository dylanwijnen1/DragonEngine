#pragma once

#include <Dragon/Graphics/Graphics.h>

#include <Platform/SFML/SfmlHelpers.h>

#include <SFML/Graphics/RenderTarget.hpp>

namespace dragon
{
	class SfmlGraphics final : public sf::RenderTarget, public Graphics
	{
	public:

		SfmlGraphics() = default;
		~SfmlGraphics() = default;

		SfmlGraphics(const SfmlGraphics&) = delete;
		SfmlGraphics(SfmlGraphics&&) = delete;
		SfmlGraphics& operator=(const SfmlGraphics&) = delete;
		SfmlGraphics& operator=(SfmlGraphics&&) = delete;

		void Clear(Color color) { clear(sf::Convert(color)); }
		bool Init(Window* pWindow, Vector2f size) final override;

		void* GetNativeTarget() final override { return this; }

		// Convenience Methods, Mainly used for debugging
		virtual void DrawRect(RectF rect, Color color);
		virtual void DrawFillRect(RectF rect, Color color, Color outlineColor, float outlineSize);

		virtual void DrawCircle(Vector2f pos, float radius, Color color);
		virtual void DrawFillCircle(Vector2f pos, float radius, Color color, Color outlineColor, float outlineSize);

	protected:
		sf::Vector2u getSize() const final override;

		void OnCameraChanged(Camera camera) final override;
	};

}