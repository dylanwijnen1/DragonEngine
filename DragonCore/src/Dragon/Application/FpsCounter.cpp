#include "FpsCounter.h"

using namespace std::chrono_literals;

namespace dragon
{

	void FpsCounter::Tick()
	{
		++m_currentCount;
		if (TimePoint now = Clock::now(); now > m_nextSecond)
		{
			m_nextSecond = now + 1s;
			m_count = m_currentCount;
			m_currentCount = 0;
		}
	}

}
