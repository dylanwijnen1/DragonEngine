#pragma once

#include <Dragon/Graphics/DragonGraphics.h>

#include <Platform/SFML/SfmlHelpers.h>

#include <SFML/Graphics/RenderTarget.hpp>

namespace sf
{

	class SfmlGraphics final : public dragon::DragonGraphics, public sf::RenderTarget
	{

	public:

		SfmlGraphics() = default;
		~SfmlGraphics() = default;

		SfmlGraphics(const SfmlGraphics&) = delete;
		SfmlGraphics(SfmlGraphics&&) = delete;
		SfmlGraphics& operator=(const SfmlGraphics&) = delete;
		SfmlGraphics& operator=(SfmlGraphics&&) = delete;

		bool Init(dragon::Vector2f size) override final;

		void Clear(dragon::Color color) override { clear(sf::Convert(color)); }

		Vector2u getSize() const final override;

	protected:


		void OnSizeChanged(dragon::Vector2f size) override final;

		void OnCameraChanged(dragon::Camera camera) override final;
	};

}