#pragma once

namespace dragon
{
	template<typename Type>
	class Range
	{
		Type m_min;
		Type m_max;

	public:

		constexpr Range(Type min, Type max)
			: m_min(min)
			, m_max(max)
		{}

		constexpr Type GetMin() const { return m_min; }

		constexpr Type GetMax() const { return m_max; }

		constexpr Type Normalized(Type in) const { return dragon::math::Normalize(in, m_min, m_max); }

	};
}