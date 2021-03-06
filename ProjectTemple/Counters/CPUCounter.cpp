///////////////////////////////////////////////////////////////
// Filename:	CPUCounter.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Counters\CPUCounter.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
CPUCounter::CPUCounter(void)
{
}

CPUCounter::CPUCounter(const CPUCounter &other)
{
}

CPUCounter::~CPUCounter(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
void CPUCounter::Initialize(void)
{
	PDH_STATUS status;

	m_canReadCpu = true;

	status = PdhOpenQuery(NULL, 0, &m_queryHandle);
	if(status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}

	status = PdhAddCounter(m_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_counterHandle);
	if(status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}

	m_lastSampleTime = GetTickCount();

	m_cpuUsage = 0;
}

void CPUCounter::Shutdown(void)
{
	if(m_canReadCpu)
		PdhCloseQuery(m_queryHandle);
}

void CPUCounter::Frame(void)
{
	PDH_FMT_COUNTERVALUE value;

	if(m_canReadCpu)
	{
		if((m_lastSampleTime + 1000) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount();

			PdhCollectQueryData(m_queryHandle);

			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);

			m_cpuUsage = value.longValue;
		}
	}
}

int CPUCounter::GetCPUPercentage(void)
{
	int usage;

	if(m_canReadCpu)
	{
		usage = (int)m_cpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}