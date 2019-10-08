#pragma once

#include <cstdint>
#include <type_traits>
#include <time.h>
#include <limits>

namespace dragon
{

	class XorShift
	{
	public:
		struct XorState
		{
			uint64_t high;
			uint64_t low;

			XorState() : low(0), high(0) {}
			XorState(uint64_t seed) : XorState(seed, seed) {}
			XorState(uint64_t low, uint64_t high) : low(low), high(high) {}
		};
		using SeedType = XorState;

		XorShift() = default;
		~XorShift() = default;

		XorShift(const XorShift&) = default;
		XorShift(XorShift&&) = default;
		XorShift& operator=(const XorShift&) = default;
		XorShift& operator=(XorShift&&) = default;

		void Seed(XorState seed) { m_state = seed; }
		void Seed(unsigned int seed) { m_state = { seed, seed }; }

		/// Generate a random number.
		template<typename Type, typename Decayed = std::decay_t<Type>>
		Decayed Random()
		{
			if constexpr (std::is_integral_v<Decayed>)
			{
				return (Decayed)(Next() % (uint64_t)std::numeric_limits<Decayed>::max());
			}
			else if constexpr (std::is_floating_point_v<Decayed>)
			{
				return ToDouble(Next());
			}
			else
			{
				static_assert(false, "Unsupported type given for XorShift::Random");
			}
		}

		/// Gets the current seed.
		XorState GetSeed() const
		{
			return m_state;
		}

	private:

		/// Current state
		XorState m_state;

		/// Shift bits around, Part of XorShift Randomization.
		constexpr inline uint64_t RotateLeft(const uint64_t x, int k)
		{
			return (x << k) | (x >> (64 - k));
		}

		/// Conversion to floating point from integer: http://prng.di.unimi.it/
		inline double ToDouble(uint64_t x)
		{
			union { uint64_t i; double d; } u;
			u.i = UINT64_C(0x3FF) << 52 | x >> 12;
			return u.d - 1.0;
		}

		/// Conversion to floating point from integer based on : http://prng.di.unimi.it/
		inline float ToFloat(uint32_t x)
		{
			union { uint32_t i; float f; } u;
			u.i = 0x3F800000U | (x >> 9);
			return u.f - 1.0f;
		}

		/// Generate a value between 0 and uint64_t::max
		uint64_t Next()
		{
			const uint64_t s0 = m_state.low;
			uint64_t s1 = m_state.high;
			const uint64_t result = s0 + s1;

			s1 ^= s0;
			m_state.low = RotateLeft(s0, 24) ^ s1 ^ (s1 << 16); // a, b
			m_state.high = RotateLeft(s1, 37); // c

			return result;
		}
	};

}