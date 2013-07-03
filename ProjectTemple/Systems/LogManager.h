#ifndef __LOGMANAGER_H_
#define __LOGMANAGER_H_

#include <cstdarg>
#include <stdio.h>
#include <string>
#include <time.h>
#include <Systems\Destroyer.h>

namespace Engine
{
	class LogManager
	{
		friend class Destroyer<LogManager>;
	private:
		FILE *m_logFile;
		static Destroyer<LogManager> m_destroyer;
		static LogManager *m_instance;
		char m_cTime[64];

		LogManager(void);
		virtual ~LogManager(void);
	public:
		static LogManager* GetInstance(void);
		char* GetTime(void);
		void Error(char* output, ...);
		void Warning(char* output, ...);
		void Trace(char* output, ...);
	};
};
#endif