#include <Systems\Thread.h>

#include <Windows.h>
#include <process.h>

using namespace Engine;

Thread::Thread(CallbackFunc func, void* caller)
{
	m_isDone = false;
	m_function = func;
	m_caller = caller;
}

Thread::~Thread(void)
{
}

void Thread::Start(void)
{
	_beginthreadex(NULL, NULL, &Thread::ThreadFunctionCallback, this, NULL, NULL);
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