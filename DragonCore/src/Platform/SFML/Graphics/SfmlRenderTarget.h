#pragma once

#include <Dragon/Generic/Math.h>
#include <Dragon/Graphics/DragonGraphics.h>

#include <Platform/SFML/SfmlHelpers.h>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf
{
	class SfmlGraphics final : public sf::RenderTarget, public dragon::DragonGraphics
	{
	public:

		SfmlGraphics() = default;
		~SfmlGraphics() = default;

		// Render Target must be able to be initialized with initial value
		SfmlGraphics(const SfmlGraphics&) = delete;
		SfmlGraphics(SfmlGraphics&&) = delete;
		SfmlGraphics& operator=(const SfmlGraphics&) = delete;
		SfmlGraphics& operator=(SfmlGraphics&&) = delete;

		virtual sf::Vector2u getSize() const override;

		// Inherited via RenderTarget

		bool Init(dragon::Vector2f size) final override;
		void Clear(dragon::Color color) final override { clear(sf::Convert(color)); }

	protected:
		void OnCameraChanged(dragon::Camera camera) final override;
		void OnSizeChanged(dragon::Vector2f size) final override;
	};

};