#include <Counters\Timer.h>
#include <Systems\LogManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Timer::Timer(void)
{
}

Timer::Timer(const Timer &other)
{
}

Timer::~Timer(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Timer::Initialize(void)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		LogManager::GetInstance()->Warning("Timer::Initialize This system does not support high performance timers");
		return false;
	}

	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

double Timer::GetTime(void)
{
	INT64 currentTime;
	double timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (double)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return m_frameTime;
}