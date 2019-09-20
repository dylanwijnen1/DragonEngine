#pragma once

#include <Dragon/Graphics/RenderTarget.h>
#include <Platform/SFML/SfmlHelpers.h>
#include <SFML/Graphics/RenderTarget.hpp>

namespace dragon
{
	// TODO: Instead of SFML drawing just use OpenGL drawing.
	class SfmlRenderTarget : public RenderTarget, sf::RenderTarget
	{
	public:
		// Inherited via RenderTarget
		virtual sf::Vector2u getSize() const override;

		//sf::RenderTarget& operator() { return this; }
	};

}