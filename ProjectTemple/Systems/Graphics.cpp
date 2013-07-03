///////////////////////////////////////////////////////////////
// Filename:	Graphics.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\Graphics.h>
#include <Systems\Overlord.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Graphics::Graphics(void)
{
	m_d3d = NULL;
	m_timer = NULL;
	m_currentScene = NULL;
#ifdef _DEBUG
	m_fpsCounter = NULL;
	m_fps = NULL;
	m_cpuCounter = NULL;
	m_cpu = NULL;
#endif //_DEBUG
}

Graphics::Graphics(const Graphics &other)
{
}

Graphics::~Graphics(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Graphics::Initialize(UINT screenWidth, UINT screenHeight, HWND hWnd)
{
	bool result;

	//Create d3d object
	m_d3d = new DX11System();
	if(!m_d3d)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize DX11System could not be created");
		return false;
	}

	//Initialize it
	result = m_d3d->Initialize(screenWidth, screenHeight, g_vSync, hWnd, g_fullScreen, g_zNear, g_zFar);
	if(!result)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize DX11 could not be initialized");
		return false;
	}

	m_d3d->TurnAlphaBlendingOn();

	m_timer = new Timer();
	if(!m_timer)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize Timer could not be created");
		return false;
	}

	result = m_timer->Initialize();
	if(!result)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize Timer could not be initialized");
		return false;
	}

#ifdef _DEBUG
	m_fpsCounter = new FPSCounter();
	if(!m_fpsCounter)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize FPSCounter could not be created");
		return false;
	}

	m_fpsCounter->Initialize();

	m_fps = new Text();
	if(!m_fps)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize FPS Text could not be created");
		return false;
	}

	result = m_fps->Initialize(L"FPS: xxx", 20.f, 20.f);
	if(!result)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize FPS Text could not be initialized");
		return false;
	}

	m_cpuCounter = new CPUCounter();
	if(!m_cpuCounter)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize CPUCounter could not be created");
		return false;
	}

	m_cpuCounter->Initialize();

	m_cpu = new Text();
	if(!m_cpu)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize CPU Text could not be created");
		return false;
	}

	result = m_cpu->Initialize(L"CPU: xxx", 20.f, 60.f);
	if(!result)
	{
		LogManager::GetInstance()->Error("Graphics::Initialize CPU Text could not be initialized");
		return false;
	}

#endif //_DEBUG

	return true;
}

void Graphics::Shutdown(void)
{
#ifdef _DEBUG
	if(m_cpu)
	{
		m_cpu->Shutdown();
		delete m_cpu;
		m_cpu = NULL;
	}

	if(m_cpuCounter)
	{
		m_cpuCounter->Shutdown();
		delete m_cpuCounter;
		m_cpuCounter = NULL;
	}

	if(m_fps)
	{
		m_fps->Shutdown();
		delete m_fps;
		m_fps = NULL;
	}

	if(m_fpsCounter)
	{
		delete m_fpsCounter;
		m_fpsCounter = NULL;
	}

#endif //_DEBUG

	//if(m_timer)
	//{
		//delete m_timer;
		//m_timer = NULL;
//	}

	if(m_d3d)
	{
		m_d3d->Shutdown();
		delete m_d3d;
		m_d3d = NULL;
	}
}

bool Graphics::Frame(void)
{
	bool result;

	m_currentScene->Update(m_timer->GetTime());

#ifdef _DEBUG
	m_fpsCounter->Frame();
	WCHAR temp[31];
	swprintf_s(temp, L"FPS: %d", m_fpsCounter->GetFPS());
	m_fps->SetText(temp);

	m_cpuCounter->Frame();
	swprintf_s(temp, L"CPU: %d%%", m_cpuCounter->GetCPUPercentage());
	m_cpu->SetText(temp);
#endif //_DEBUG

	result = Render();
	if(!result)
		return false;

	return true;
}

void Graphics::SetScene(Scene* scene)
{
	if(m_currentScene != NULL)
	{
		m_currentScene->Shutdown();
		delete m_currentScene;
		m_currentScene = NULL;
	}

	m_currentScene = scene;
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool Graphics::Render(void)
{
	m_d3d->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
	{
		m_d3d->TurnZBufferOn();
		{
			m_currentScene->Render3D();
		}

		m_d3d->TurnZBufferOff();
		{
#ifdef _DEBUG
			m_fps->Render();
			m_cpu->Render();
#endif //_DEBUG
			m_currentScene->Render2D();
		}

		m_d3d->TurnZBufferOn();
	}

	m_d3d->EndScene();

	return true;
}