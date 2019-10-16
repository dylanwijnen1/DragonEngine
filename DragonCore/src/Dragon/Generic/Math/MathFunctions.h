#pragma once

#include <EASTL/numeric_limits.h>

namespace dragon
{
	namespace math
	{
		constexpr long double PI_ACCURATE = 3.141592653589793238L;
		constexpr double PI = 3.141592653589793;
		constexpr float PI_F = 3.1415927f;

		// TODO: EASTL does not have a constexpr numeric_limits as of yet. Replace when available.
		constexpr float Infinity = std::numeric_limits<float>::infinity();
		constexpr float NegativeInfinity = -std::numeric_limits<float>::infinity();


		// Precise method, which guarantees v = v1 when t = 1.
		template<class Type>
		constexpr inline Type Lerp(Type start, Type end, Type perc) 
		{
			return ((Type)1.0 - perc) * start + perc * end;
		}

		// Normalize a value.
		template<class Type>
		Type Normalize(Type in, Type min, Type max)
		{
			return (in - min) / (max - min);
		}

		// Clamp
		template<class Type>
		constexpr inline Type Clamp(Type value, Type min, Type max)
		{
			return eastl::clamp(value, min, max);
		}

		template<class Type>
		constexpr inline Type Max(Type left, Type right)
		{
			return eastl::max(left, right);
		}

		template<class Type>
		constexpr inline Type Min(Type left, Type right)
		{
			return eastl::min(left, right);
		}

		// TODO: Unable to find an eastl round function although a "round_to_nearest" enum exists.
		inline float RoundToNearest(float in)
		{
			return std::roundf(in);
		}

		// TODO: Unable to find an eastl round function although a "round_to_nearest" enum exists.
		inline float Ceil(float in)
		{
			return std::ceilf(in);
		}
	}
}