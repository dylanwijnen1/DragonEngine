#pragma once

#include <chrono>

namespace dragon
{
	/// <summary>
	/// Holds the amount of time elapsed since last frame.
	/// </summary>
	struct TimeStep
	{	
	public:
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = Clock::time_point;
		using Duration = std::chrono::duration<double>; // Seconds Duration

	private:
		Duration m_duration;

	public:

		TimeStep(TimePoint start, TimePoint end)
			: m_duration(end - start)
		{}

		TimeStep(Duration duration)
			: m_duration(duration)
		{}

		TimeStep& operator=(Duration duration)
		{
			m_duration = duration;
			return *this;
		}

		/// <summary>
		/// Get Delta Time in Milliseconds
		/// </summary>
		/// <returns></returns>
		long long Milliseconds() const;

		/// <summary>
		/// Better Precision
		/// </summary>
		/// <returns></returns>
		double Seconds() const;

		/// <summary>
		/// Precision issues might occur when using a float value.
		/// </summary>
		/// <returns></returns>
		float SecondsAsFloat() const;

		static auto now() { return Clock::now(); }

		// Operators
		float operator*(float val) const { return (float)(val * Seconds()); }
		double operator*(double val) const { return val * Seconds(); }

		float operator +=(float val) const { return SecondsAsFloat(); }
		double operator +=(double val) const { return Seconds(); }
	};
}