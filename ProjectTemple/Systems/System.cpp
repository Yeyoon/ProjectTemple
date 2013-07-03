///////////////////////////////////////////////////////////////
// Filename:	System.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\System.h>

using namespace Engine;

Input* System::m_input = NULL;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
System::System(void)
{
	m_input = NULL;
	m_graphics = NULL;
	m_soundSystem = NULL;
	m_shaderManager = NULL;
	//m_havokSystem = NULL;
}

System::System(const System &other)
{

}

System::~System(void)
{

}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool System::Initialize(void)
{
	LogManager::GetInstance()->Trace("System initializing...");
	UINT sWidth, sHeight;
	bool result;
	sWidth = sHeight = 0;
	m_input = NULL;
	m_graphics = NULL;
	m_soundSystem = NULL;

	InitializeWindows(sWidth, sHeight);

	m_input = new Input();
	if(!m_input)
	{
		LogManager::GetInstance()->Error("System::Initialize Input could not be created");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	result = m_input->Initialize(Input::INPUT_RAW);
	if(!result)
	{
		LogManager::GetInstance()->Error("System::Initialize Input could not be initialized");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	m_graphics = new Graphics();
	if(!m_graphics)
	{
		LogManager::GetInstance()->Error("System::Initialize Graphics could not be created");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	result = m_graphics->Initialize(sWidth, sHeight, m_hWnd);
	if(!result)
	{
		LogManager::GetInstance()->Error("System::Initialize Graphics could not be initialized");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	m_soundSystem = new SoundSystem();
	if(!m_soundSystem)
	{
		LogManager::GetInstance()->Error("System::Initialize SoundSystem could not be created");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	result = m_soundSystem->Initialize();
	if(!result)
	{
		LogManager::GetInstance()->Error("System::Initialize SoundSystem could not be initialized");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	m_shaderManager = new ShaderManager();
	if(!m_shaderManager)
	{
		LogManager::GetInstance()->Error("System::Initialize ShaderManager could not be created");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	/*m_havokSystem = new HavokSystem();
	if(!m_havokSystem)
	{
		LogManager::GetInstance()->Error("System::Initialize HavokSystem could not be created");
		ShowCursor(true);
		MessageBox(m_hWnd, "Check GameLog.log for errors.", "ERROR!", MB_OK | MB_ICONERROR);
		return false;
	}

	result = m_havokSystem->Initialize();*/

	m_timer = new Timer();

	m_timer->Initialize();

	//Sound* temp;
	//m_soundSystem->CreateStream("title.mp3", &temp);
	//temp->setMode(FMOD_LOOP_NORMAL);
	//m_soundSystem->PlaySound(temp);

	LogManager::GetInstance()->Trace("System initialization successful");
	return true;
}

void System::Shutdown(void)
{
	if(m_timer)
	{
		delete m_timer;
		m_timer = NULL;
	}

	/*if(m_havokSystem)
	{
		m_havokSystem->Shutdown();
		delete m_havokSystem;
		m_havokSystem = NULL;
	}*/

	if(m_shaderManager)
	{
		delete m_shaderManager;
		m_shaderManager = NULL;
	}

	if(m_soundSystem)
	{
		m_soundSystem->Shutdown();
		delete m_soundSystem;
		m_soundSystem = NULL;
	}

	if(m_graphics)
	{
		m_graphics->Shutdown();
		delete m_graphics;
		m_graphics = NULL;
	}

	if(m_input)
	{
		m_input->Shutdown();
		delete m_input;
		m_input = NULL;
	}

	ShutdownWindows();
}

void System::Run(void)
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));
	done = false;

	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			double dTime = m_timer->GetTime();
			//m_havokSystem->Update(dTime);
			result = Frame();
			if(!result)
				done = true;
		}
	}
}

//LRESULT CALLBACK System::MessageHandler(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	switch(msg)
//	{
//		case WM_INPUT:
//		{
//			m_input->Update(lparam);
//			return 0;
//		}
//		default:
//		{
//			return DefWindowProc(hWnd, msg, wparam, lparam);
//		}
//	}
//}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
bool System::Frame(void)
{
	bool result;

	m_soundSystem->Update();

	result = m_graphics->Frame();
	if(!result)
		return false;

	return true;
}

void System::InitializeWindows(UINT &screenWidth, UINT &screenHeight)
{
	LogManager::GetInstance()->Trace("Window initializing...");
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	//g_appHandle = this;

	m_hInstance = GetModuleHandle(NULL);

	m_applicationName = "Project Temple";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	RECT currentRes;
	GetWindowRect(GetDesktopWindow(), &currentRes);
	screenWidth = currentRes.right;
	screenHeight = currentRes.bottom;

	if(g_fullScreen)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (ULONG)screenWidth;
		dmScreenSettings.dmPelsHeight = (ULONG)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;

		posX = (currentRes.right - screenWidth) / 2;
		posY = (currentRes.bottom - screenHeight) / 2;
	}

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	//ShowCursor(false);
	LogManager::GetInstance()->Trace("Window successfully initialized");
}

void System::ShutdownWindows(void)
{
	//ShowCursor(true);

	if(g_fullScreen)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
}

///////////////////////////////////////////////////////////////
// Static Functions
///////////////////////////////////////////////////////////////
LRESULT CALLBACK System::WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_INPUT:
		{
			if(m_input)
				m_input->Update(lparam);
			return 0;
		}
		default:
		{
			return DefWindowProc(hWnd, msg, wparam, lparam);
		}
	}
}