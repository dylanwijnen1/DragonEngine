#include "SfmlGraphics.h"

#include <Dragon/Application/Window/Window.h>
#include <SFML/Graphics.hpp>

namespace dragon
{
	bool SfmlGraphics::Init(Window* pWindow, Vector2f size)
	{
		bool result = Graphics::Init(pWindow, size);
		sf::RenderTarget::initialize();
		return result;
	}

	sf::Vector2u SfmlGraphics::getSize() const
	{
		Vector2f size = GetSize();
		return sf::Vector2u((sf::Uint32)size.x, (sf::Uint32)size.y);
	}

	void SfmlGraphics::OnCameraChanged(Camera camera)
	{
		sf::View view = getDefaultView();

		view.setCenter(sf::Convert(camera.m_position));
		view.setSize(sf::Convert(camera.m_size));
		view.setViewport(sf::Convert(camera.m_viewport));

		setView(view);
	}

}