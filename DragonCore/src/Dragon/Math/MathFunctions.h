#pragma once

#include <limits>

namespace dragon
{
	namespace math
	{
		constexpr long double PI_ACCURATE = 3.141592653589793238L;
		constexpr double PI = 3.141592653589793;
		constexpr float PI_F = 3.1415927f;

		constexpr float Infinity = std::numeric_limits<float>::infinity();
		constexpr float NegativeInfinity = -std::numeric_limits<float>::infinity();


		// Precise method, which guarantees v = v1 when t = 1.
		template<class Type>
		Type Lerp(Type start, Type end, Type perc) {
			return ((Type)1.0 - perc) * start + perc * end;
		}

		// Clamp
		template<class Type>
		Type Clamp(Type value, Type min, Type max)
		{
			return std::clamp(value, min, max);
		}

		template<class Type>
		Type Max(Type left, Type right)
		{
			return std::max(left, right)
		}

		template<class Type>
		Type Min(Type left, Type right)
		{
			return std::Min(left, right)
		}
	}
}