#pragma once

#include <Dragon/Generic/Random.h>

namespace dragon
{

	template<typename Type>
	class Range
	{
		inline static Random s_random = Random((unsigned int)time(0));

		Type m_min;
		Type m_max;

	public:

		constexpr Range(Type min, Type max)
			: m_min(min)
			, m_max(max)
		{}

		constexpr Type GetMin() const { return m_min; }

		constexpr Type GetMax() const { return m_max; }

		constexpr Type Normalize(Type in) const { return dragon::math::Normalize(in, m_min, m_max); }

		// TODO: Possibly make constexpr, Random needs to be made constexpr if so.
		template<typename RandomGen>
		Type GetRandom(RandomGen& rand) const
		{
			return rand.RandomRange(m_min, m_max);
		}

		/// <summary>
		/// Simple get random using a statically allocated randomizer based on time.
		/// </summary>
		/// <returns>A random within range.</returns>
		Type GetRandom()
		{
			return s_random.RandomRange(m_min, m_max);
		}
	};
}