#pragma once

#include <chrono>

namespace dragon
{
	class FpsCounter
	{
		size_t m_currentCount;
		size_t m_count;

		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = Clock::time_point;

		TimePoint m_nextSecond;

	public:

		FpsCounter() : m_currentCount(0), m_count(0), m_nextSecond(Clock::now()) {}
		~FpsCounter() = default;

		FpsCounter(const FpsCounter&) = default;
		FpsCounter(FpsCounter&&) = default;
		FpsCounter& operator=(const FpsCounter&) = default;
		FpsCounter& operator=(FpsCounter&&) = default;

		void Tick();

		size_t GetCount() const { return m_count; }
	};
}