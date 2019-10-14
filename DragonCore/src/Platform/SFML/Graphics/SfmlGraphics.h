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

	protected:
		sf::Vector2u getSize() const final override;

		void OnCameraChanged(Camera camera) final override;
	};

}