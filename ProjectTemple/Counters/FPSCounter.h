///////////////////////////////////////////////////////////////
// Filename:	FPSCounter.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __FPSCOUNTER_H_
#define __FPSCOUNTER_H_

namespace Engine
{
	class FPSCounter
	{
	private:
		int m_fps, m_count;
		unsigned long m_startTime;
	public:
		FPSCounter(void);
		FPSCounter(const FPSCounter &other);
		virtual ~FPSCounter(void);

		void Initialize(void);
		void Frame(void);
		int GetFPS(void);
	};
};
#endif //__FPSCOUNTER_H_