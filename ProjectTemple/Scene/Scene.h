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

		virtual bool _initialize(void);
		virtual void _kill(void);
	private:
		static void _updateThread(void* caller);
	public:
		Scene(void);
		virtual ~Scene(void);

		virtual void Render3D(void) = 0;
		virtual void Render2D(void) = 0;
		virtual void Shutdown(void) = 0;
		virtual void Update(double dTime);

		virtual void Kill(void);
		bool Initialize(void);
		bool IsInitialized(void);
	};
};

#endif //__SCENE_H_