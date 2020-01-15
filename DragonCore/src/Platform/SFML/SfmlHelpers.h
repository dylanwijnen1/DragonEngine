#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include <Dragon/Generic/Math.h>
#include <Dragon/Graphics/Color.h>

namespace sf
{
	// Vector2f
	inline dragon::Vector2f Convert(sf::Vector2f vec) { return dragon::Vector2f(vec.x, vec.y); }
	inline sf::Vector2f Convert(dragon::Vector2f vec) { return sf::Vector2f(vec.x, vec.y); }

	// Vector2
	inline dragon::Vector2 Convert(sf::Vector2i vec) { return dragon::Vector2(vec.x, vec.y); }
	inline sf::Vector2i Convert(dragon::Vector2 vec) { return sf::Vector2i(vec.x, vec.y); }

	// RectF
	inline dragon::RectF Convert(sf::FloatRect rect) { return { rect.left, rect.top, rect.width, rect.height }; }
	inline sf::FloatRect Convert(dragon::RectF rect) { return { rect.x, rect.y, rect.width, rect.height }; }

	// Color
	inline dragon::Color Convert(sf::Color color) 
	{ 
		return dragon::Color
		(
			dragon::math::Max(color.r / 255.0f, 1.0f),
			dragon::math::Max(color.g / 255.0f, 1.0f),
			dragon::math::Max(color.b / 255.0f, 1.0f),
			dragon::math::Max(color.a / 255.0f, 1.0f)
		); 
	}

	inline sf::Color Convert(dragon::Color color)
	{
		return sf::Color
		(
			(sf::Uint8)(color.r * 255u),
			(sf::Uint8)(color.g * 255u),
			(sf::Uint8)(color.b * 255u),
			(sf::Uint8)(color.a * 255u)
		);
	}

	// TODO: Transform / Matrix
}