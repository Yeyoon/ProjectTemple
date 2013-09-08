#include <Systems\Thread.h>
#include <Systems\LogManager.h>

using namespace Engine;

Thread::Thread(CallbackFunc func, void* caller)
{
	m_isDone = false;
	m_function = func;
	m_caller = caller;

	m_handle = (HANDLE)_beginthreadex(NULL, NULL, &Thread::ThreadFunctionCallback, this, CREATE_SUSPENDED, &m_threadID);
}

Thread::~Thread(void)
{
}

void Thread::Start(void)
{
	ResumeThread(m_handle);
}

void Thread::Pause(void)
{
	SuspendThread(m_handle);
}

bool Thread::isDone(void) const
{
	return m_isDone;
}

unsigned int __stdcall Thread::ThreadFunctionCallback(void* h)
{
	Thread* thread = static_cast<Thread*>(h);
	thread->m_function(thread->m_caller);

	thread->m_isDone = true;

	return NULL;
}