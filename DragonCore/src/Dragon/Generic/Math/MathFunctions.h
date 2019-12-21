#pragma once

#include <EASTL/numeric_limits.h>

namespace dragon
{
	namespace math
	{
		static constexpr long double kPiAccurate = 3.141592653589793238L;
		static constexpr double kPi = 3.141592653589793;
		static constexpr float kPi = 3.1415927f;

		// TODO: EASTL does not have a constexpr numeric_limits as of yet. Replace when available.
		static constexpr float kInfinity = std::numeric_limits<float>::infinity();
		static constexpr float kNegativeInfinity = -std::numeric_limits<float>::infinity();

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

		inline float Floor(float in)
		{
			return std::floorf(in);
		}

		inline constexpr float DegToRad(float deg)
		{
			return deg * (kPi / 180.f);
		}

		inline constexpr float RadToDeg(float rad)
		{
			return rad * (180.f / kPi);
		}

		inline float Sin(float in)
		{
			return std::sinf(in);
		}

		inline float Cos(float in)
		{
			return std::cosf(in);
		}

		/// <summary>
		/// Apply a smoother step on the value.
		/// </summary>
		/// <param name="x">The value to apply the smoother step to.</param>
		/// <returns>Smoothened value.</returns>
		constexpr inline float SmootherStep(float x)
		{
			return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
		}
	}
}