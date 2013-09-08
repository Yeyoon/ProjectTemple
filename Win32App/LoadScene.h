#ifndef __LOADSCENE_H_
#define __LOADSCENE_H_

#include <Scene\Scene.h>
#include "TestScene.h"
#include <Systems\Thread.h>


class LoadScene : public Engine::Scene
{
private:
	bool _initialize(void);
public:
	LoadScene(void);
	virtual ~LoadScene(void);

	void Shutdown(void){}
	void Render2D(void);
	void Render3D(void){}
	void Update(double dTime){}

	static void LoadNextScene(void* caller);

	TestScene* m_nextScene;
	Engine::Thread *m_thread;
	//Engine::Text *m_loading;
};

#endif //__LOADSCENE_H_