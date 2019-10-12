#include "SfmlGraphics.h"

#include <Dragon/Application/Window/Window.h>
#include <SFML/Graphics.hpp>

namespace dragon
{
	sf::Vector2u SfmlGraphics::getSize() const
	{
		return sf::Vector2u((sf::Uint32)m_size.x, (sf::Uint32)m_size.y);
	}

	void SfmlGraphics::SetCamera(Camera camera)
	{
		sf::View view = getDefaultView();

		view.setCenter(sf::Convert(camera.m_position));
		view.setSize(sf::Convert(camera.m_size));
		view.setViewport(sf::Convert(camera.m_viewport));

		setView(view);
	}

	Camera SfmlGraphics::GetCamera() const
	{
		const sf::View& view = getView();

		Camera camera;
		camera.m_position = sf::Convert(view.getCenter());
		camera.m_size = sf::Convert(view.getSize());
		camera.m_viewport = sf::Convert(view.getViewport());

		return camera;
	}

	void SfmlGraphics::Display()
	{
		m_pWindow->SwapBuffers();
	}

	bool SfmlGraphics::Init(Vector2f size)
	{
		sf::RenderTarget::initialize();
		return true;
	}

}