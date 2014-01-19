///////////////////////////////////////////////////////////////
// Filename:	main.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////

#include <Systems\System.h>
#include <Systems\Overlord.h>
#include "LoadScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	//using namespace Engine;

	Engine::System* pSys = NULL;
	bool result;

	pSys = new Engine::System();
	if(!pSys)
	{
		return 1;
	}

	Engine::Overlord::SetSystem(pSys);

	result = pSys->Initialize(640, 480);
	if(result)
	{
		LoadScene* test = new LoadScene();
		result = test->Initialize();
		if(result)
		{
			Engine::Overlord::GetInstance()->SetScene(test);
			pSys->Run();
		}
	}

	pSys->Shutdown();
	delete pSys;
	pSys = NULL;

	return 0;
}