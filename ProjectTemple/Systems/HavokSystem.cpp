///////////////////////////////////////////////////////////////
// Filename:	HavokSystem.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\HavokSystem.h>

using namespace Engine;

HavokSystem::HavokSystem(void)
{
	m_world = NULL;
	m_memRouter = NULL;
#ifdef _DEBUG
	m_visualDebugger = NULL;
	m_physicsContext = NULL;
#endif //_DEBUG
}

HavokSystem::~HavokSystem(void)
{
}

bool HavokSystem::Initialize(void)
{
	LogManager::GetInstance()->Trace("Initializing Havok...");

	//Init Memory
	m_memRouter = hkMemoryInitUtil::initDefault(&m_baseMalloc, hkMemorySystem::FrameInfo(6*MEGABYTE));
	hkBaseSystem::init(m_memRouter, havokErrorReport);

	//Init Physics
	hkpWorldCinfo info;
	info.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;
	info.setBroadPhaseWorldSize(1000.f);
	info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_8ITERS_HARD);
	info.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_FIX_ENTITY;

	//Multi-threading
	hkHardwareInfo hwInfo;
	hkGetHardwareInfo(hwInfo);
	
	hkCpuJobThreadPoolCinfo threadPoolCInfo;
	threadPoolCInfo.m_numThreads = hwInfo.m_numThreads - 1;
	threadPoolCInfo.m_timerBufferPerThreadAllocation = 200*KILOBYTE;
	m_threadPool = new hkCpuJobThreadPool(threadPoolCInfo);

	hkJobQueueCinfo jobQueueCInfo;
	jobQueueCInfo.m_jobQueueHwSetup.m_numCpuThreads = hwInfo.m_numThreads;
	m_jobQueue = new hkJobQueue(jobQueueCInfo);

	m_world = new hkpWorld(info);
	m_world->markForWrite();
	hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
	m_world->registerWithJobQueue(m_jobQueue);

	//Init Visual Debugger
#ifdef _DEBUG
	m_physicsContext = new hkpPhysicsContext();
	hkpPhysicsContext::registerAllPhysicsProcesses();
	m_physicsContext->addWorld(m_world);
	hkArray<hkProcessContext*> contexts;
	contexts.pushBack(m_physicsContext);

	m_visualDebugger = new hkVisualDebugger(contexts);
	m_visualDebugger->serve();
	LogManager::GetInstance()->Trace("Havok visual debugger active.");
#endif //_DEBUG

	m_world->unmarkForWrite();

	LogManager::GetInstance()->Trace("Havok Successfully Initialized.");

	return true;
}

void HavokSystem::Shutdown(void)
{
	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void HavokSystem::Update(double dTime)
{
	//Don't update the physics world too often, at small numbers the change is monumental.
	if(dTime < 8) //120 times per second
		m_world->stepMultithreaded(m_jobQueue, m_threadPool,8);
	else if(dTime < 16) //60 times per second
		m_world->stepMultithreaded(m_jobQueue, m_threadPool,16);
	else //Your computer probably sucks, so we'll update it every frame.
		m_world->stepMultithreaded(m_jobQueue, m_threadPool,dTime);
#ifdef _DEBUG
	m_visualDebugger->step();
#endif //_DEBUG
}

void HK_CALL HavokSystem::havokErrorReport(const char* msg, void* userContext)
{
	LogManager::GetInstance()->Trace("[HAVOK] %s", msg);
}

//
// Keycode
#include <Common/Base/keycode.cxx>

// Productfeatures
// We're using only physics - we undef products even if the keycode is present so
// that we don't get the usual initialization for these products.
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR

// Also we're not using any serialization/versioning so we don't need any of these.
#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
//#define HK_EXCLUDE_FEATURE_RegisterReflectedClasses
#define HK_EXCLUDE_FEATURE_MemoryTracker

// This include generates an initialization function based on the products
// and the excluded features.
#include <Common/Base/Config/hkProductFeatures.cxx>
//