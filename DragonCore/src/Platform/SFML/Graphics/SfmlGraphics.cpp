#include "SfmlGraphics.h"

#include <SFML/Graphics.hpp>

namespace sf
{
	sf::Vector2u SfmlGraphics::getSize() const
	{
		dragon::Vector2f size = GetSize();
		return sf::Vector2u((sf::Uint32)size.x, (sf::Uint32)size.y);
	}

	bool SfmlGraphics::Init(dragon::Vector2f size)
	{
		dragon::RenderTarget::Init(size);
		sf::RenderTarget::initialize();
		return true;
	}

	void SfmlGraphics::OnSizeChanged(dragon::Vector2f size)
	{
		// Reset View Bounds
		setView(getDefaultView());
	}

	void SfmlGraphics::OnCameraChanged(dragon::Camera camera)
	{
		sf::View view = getDefaultView();

		view.setCenter(sf::Convert(camera.m_position));
		view.setSize(sf::Convert(camera.m_size));
		view.setViewport(sf::Convert(camera.m_viewport));

		setView(view);
	}

}