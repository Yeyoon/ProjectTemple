#ifndef __THREAD_H_
#define __THREAD_H_

#include <Windows.h>
#include <process.h>

namespace Engine
{
	class Thread
	{
		typedef void (*CallbackFunc)(void*);
	private:
		volatile bool m_isDone;
		CallbackFunc m_function;
		void* m_caller;
	public:
		Thread(CallbackFunc func, void* caller);
		~Thread(void);

		void Start(void);
		bool isDone(void) const;
	private:
		static unsigned int __stdcall ThreadFunctionCallback(void* h);
	};
}
#endif //__THREAD_H_