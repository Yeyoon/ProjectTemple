#include <Systems\LogManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Static variables
///////////////////////////////////////////////////////////////
Destroyer<LogManager> LogManager::m_destroyer;
LogManager *LogManager::m_instance = NULL;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
LogManager::LogManager(void)
{
	m_logFile = NULL;
	fopen_s(&m_logFile, "GameLog.log", "a");
	if(m_logFile)
	{
		fprintf_s(m_logFile, " ------START------ \n\n");
		fclose(m_logFile);
	}
}

LogManager::~LogManager(void)
{
	fopen_s(&m_logFile, "GameLog.log", "a");
	if(m_logFile)
	{
		fprintf(m_logFile, "\n -------END------- \n\n");
		fclose(m_logFile);
	}
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
LogManager* LogManager::GetInstance(void)
{
	if(m_instance == NULL)
	{
		m_instance = new LogManager();
		m_destroyer.setSingleton(m_instance);
	}
	return m_instance;
}

char* LogManager::GetTime(void)
{
	time_t rawtime;
	struct tm *timeinfo;
	timeinfo = new tm();
	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	asctime_s(m_cTime, timeinfo);
	int i = strlen(m_cTime);
	m_cTime[i-1] = '\0';

	return m_cTime;
}

void LogManager::Trace(char* output, ...)
{
	fopen_s(&m_logFile, "GameLog.log", "a");

	if(m_logFile)
	{
		GetTime();

		char final[2048];

		va_list arglist;
		va_start(arglist, output);
		vsprintf_s(final, output, arglist);
		va_end(arglist);

		fprintf(m_logFile, "[%s] : %s\n", m_cTime, final);

		fclose(m_logFile);
	}
}

void LogManager::Error(char* output, ...)
{
	fopen_s(&m_logFile, "GameLog.log", "a");

	if(m_logFile)
	{
		GetTime();

		char final[2048];

		va_list arglist;
		va_start(arglist, output);
		vsprintf_s(final, output, arglist);
		va_end(arglist);

		fprintf(m_logFile, "[%s] : [ERROR] %s\n", m_cTime, final);

		fclose(m_logFile);
	}
}

void LogManager::Warning(char* output, ...)
{
	fopen_s(&m_logFile, "GameLog.log", "a");

	if(m_logFile)
	{
		GetTime();

		char final[2048];

		va_list arglist;
		va_start(arglist, output);
		vsprintf_s(final, output, arglist);
		va_end(arglist);

		fprintf(m_logFile, "[%s] : [WARNING] %s\n", m_cTime, final);

		fclose(m_logFile);
	}
}