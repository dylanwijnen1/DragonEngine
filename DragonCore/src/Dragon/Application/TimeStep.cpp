#include "TimeStep.h"

namespace dragon
{

	long long TimeStep::Milliseconds() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_duration).count();
	}

	double TimeStep::Seconds() const
	{
		return m_duration.count();
	}

	float TimeStep::SecondsAsFloat() const
	{
		return std::chrono::duration<float>(m_duration).count();
	}

}