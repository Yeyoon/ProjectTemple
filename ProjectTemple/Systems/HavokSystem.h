///////////////////////////////////////////////////////////////
// Filename:	HavokSystem.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __HAVOKSYSTEM_H_
#define __HAVOKSYSTEM_H_

#include <Systems\Havok.h>
#include <Systems\LogManager.h>

#define KILOBYTE 1024
#define MEGABYTE 1024*1024

namespace Engine
{
	class HavokSystem
	{
		friend class Overlord;
	private:
		hkpWorld *m_world;
		hkMemoryRouter *m_memRouter;
		hkMallocAllocator m_baseMalloc;
		hkJobThreadPool* m_threadPool;
		hkJobQueue* m_jobQueue;
#ifdef _DEBUG
		hkVisualDebugger *m_visualDebugger;
		hkpPhysicsContext *m_physicsContext;
#endif //_DEBUG
	public:
		HavokSystem(void);
		HavokSystem(const HavokSystem &other);
		~HavokSystem(void);

		bool Initialize(void);
		void Shutdown(void);
		void Update(double dTime);
	private:
		static void HK_CALL havokErrorReport(const char* msg, void* userContext);
	};
};

#endif //__HAVOKSYSTEM_H_