///////////////////////////////////////////////////////////////
// Filename:	CPUCounter.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __CPUCOUNTER_H_
#define __CPUCOUNTER_H_

#include <Pdh.h>

namespace Engine
{
	class CPUCounter
	{
	private:
		bool m_canReadCpu;
		HQUERY m_queryHandle;
		HCOUNTER m_counterHandle;
		ULONG m_lastSampleTime;
		long m_cpuUsage;
	public:
		CPUCounter(void);
		CPUCounter(const CPUCounter &other);
		virtual ~CPUCounter(void);

		void Initialize(void);
		void Shutdown(void);
		void Frame(void);
		int GetCPUPercentage(void);
	};
};
#endif