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

	void SfmlGraphics::DrawRect(RectF rect, Color color)
	{
		sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
		shape.setPosition(rect.x, rect.y);
		shape.setFillColor(sf::Convert(color));
		draw(shape);
	}

	void SfmlGraphics::DrawFillRect(RectF rect, Color color, Color outlineColor, float outlineSize)
	{
		sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
		shape.setPosition(rect.x, rect.y);

		shape.setFillColor(sf::Convert(color));

		shape.setOutlineColor(sf::Convert(outlineColor));
		shape.setOutlineThickness(outlineSize);

		draw(shape);
	}

	void SfmlGraphics::DrawCircle(Vector2f pos, float radius, Color color)
	{
		sf::CircleShape shape(radius);
		shape.setPosition(sf::Convert(pos));
		shape.setFillColor(sf::Convert(color));
		draw(shape);
	}

	void SfmlGraphics::DrawFillCircle(Vector2f pos, float radius, Color color, Color outlineColor, float outlineSize)
	{
		sf::CircleShape shape(radius);
		shape.setPosition(sf::Convert(pos));
		shape.setFillColor(sf::Convert(color));

		shape.setOutlineColor(sf::Convert(outlineColor));
		shape.setOutlineThickness(outlineSize);

		draw(shape);
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