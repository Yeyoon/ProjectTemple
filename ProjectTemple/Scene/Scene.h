///////////////////////////////////////////////////////////////
// Filename:	Scene.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __SCENE_H_
#define __SCENE_H_

//#include <list>
//#include "Model.h"
#include "Systems\Thread.h"
#include "Counters\Timer.h"

namespace Engine
{
	class Scene
	{
		//typedef std::list<Model*> VectorType;
	protected:
		Thread* m_updateLoop;
		bool m_bUpdating;
		bool m_bInitialized;
		Timer* m_updateTimer;
		bool m_bTimerInit;

		virtual bool _initialize(void) = 0;
	private:
		static void _updateThread(void* caller)
		{
			Scene *pCaller = (Scene*)caller;

			while(pCaller->m_bUpdating)
			{
				if(pCaller->m_bInitialized)
				{
					if(pCaller->m_bTimerInit)
					{
						pCaller->Update(pCaller->m_updateTimer->GetTime());
					}
					else
					{
						pCaller->m_updateTimer->Initialize();
						pCaller->m_bTimerInit = true;
						pCaller->Update(pCaller->m_updateTimer->GetTime());
					}
				}
			}
		}
	public:
		Scene(void)
		{
			m_bInitialized = false;
			m_bUpdating = true;
			m_bTimerInit = false;
			m_updateTimer = new Timer();
			m_updateLoop = new Thread(Scene::_updateThread, this);
			m_updateLoop->Start();
		}
		virtual ~Scene(void)
		{
			//This is bad, figure out how to cleanly kill the thread instead of pausing it.
			m_updateLoop->Pause();
			m_bUpdating = m_bInitialized = false;
		}

		virtual void Render3D(void) = 0;
		virtual void Render2D(void) = 0;
		virtual void Shutdown(void) = 0;
		virtual void Update(double dTime) = 0;

		bool Initialize(void)
		{
			m_bInitialized = _initialize();
			return m_bInitialized;
		}
		bool IsInitialized(void){return m_bInitialized;};
	};
};

#endif //__SCENE_H_