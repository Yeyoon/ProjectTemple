///////////////////////////////////////////////////////////////
// Filename:	Timer.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __TIMER_H_
#define __TIMER_H_

#include <Windows.h>

namespace Engine
{
	class Timer
	{
	private:
		INT64 m_frequency;
		double m_ticksPerMs;
		INT64 m_startTime;
		double m_frameTime;
	public:
		Timer(void);
		Timer(const Timer &other);
		virtual ~Timer(void);

		bool Initialize(void);
		double GetTime(void);
	};
};
#endif //__TIMER_H_