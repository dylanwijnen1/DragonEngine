#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include <Dragon/Generic/Math.h>
#include <Dragon/Graphics/Color.h>
#include <Dragon/Application/Input/Key.h>
#include <Dragon/Application/Input/MouseButton.h>
#include <Dragon/Graphics/PrimitiveType.h>

namespace sf
{
	// Vector2f
	inline dragon::Vector2f Convert(Vector2f vec) { return dragon::Vector2f(vec.x, vec.y); }
	inline Vector2f Convert(dragon::Vector2f vec) { return Vector2f(vec.x, vec.y); }

	// Vector2
	inline dragon::Vector2 Convert(Vector2i vec) { return dragon::Vector2(vec.x, vec.y); }
	inline Vector2i Convert(dragon::Vector2 vec) { return Vector2i(vec.x, vec.y); }

	// RectF
	inline dragon::RectF Convert(FloatRect rect) { return { rect.left, rect.top, rect.width, rect.height }; }
	inline FloatRect Convert(dragon::RectF rect) { return { rect.x, rect.y, rect.width, rect.height }; }

	// Color
	inline dragon::Color Convert(Color color) 
	{ 
		return dragon::Color
		(
			dragon::math::Max(color.r / 255.0f, 1.0f),
			dragon::math::Max(color.g / 255.0f, 1.0f),
			dragon::math::Max(color.b / 255.0f, 1.0f),
			dragon::math::Max(color.a / 255.0f, 1.0f)
		); 
	}

	inline Color Convert(dragon::Color color)
	{
		return Color
		(
			(Uint8)(color.r * 255u),
			(Uint8)(color.g * 255u),
			(Uint8)(color.b * 255u),
			(Uint8)(color.a * 255u)
		);
	}

	dragon::Key ConvertKey(Keyboard::Key key);

	dragon::MouseButton ConvertButton(Mouse::Button button);

	PrimitiveType ConvertPrimitiveType(dragon::PrimitiveType primitiveType);
};