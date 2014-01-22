///////////////////////////////////////////////////////////////
// Filename:	Overlord.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\Overlord.h>
#include <Systems\LogManager.h>
#include <Systems\System.h>
#include <Systems\DX11System.h>
#include <Systems\Input.h>
#include <Systems\Graphics.h>
#include <Scene\Camera.h>
#include <Scene\Scene.h>
#include <Shader\ShaderManager.h>

using namespace Engine;

Overlord* Overlord::m_instance = 0;
Destroyer<Overlord> Overlord::m_destroyer;

Overlord* Overlord::GetInstance(void)
{
	if(m_instance == NULL)
	{
		LogManager::GetInstance()->Warning("Overlord::GetInstance - System not set!");
		m_instance = new Overlord();
		m_destroyer.setSingleton(m_instance);
	}
	return m_instance;
}

void Overlord::SetSystem(System* sys)
{
	if(m_instance == NULL)
	{
		m_instance = new Overlord();
		m_destroyer.setSingleton(m_instance);
	}
	m_instance->m_system = sys;
}

Overlord::Overlord(void)
{
	m_system = NULL;
	m_currentCamera = NULL;
}

void Overlord::SetCamera(Camera* cam)
{
	m_currentCamera = cam;
}

void Overlord::SetScene(Scene* scene)
{
	m_system->m_graphics->SetScene(scene);
}

System* Overlord::GetSystem(void)
{
	return m_system;
}

ID3D11DeviceContext* Overlord::GetDeviceContext(void)
{
	return m_system->m_graphics->m_d3d->m_deviceContext;
}

ID3D11Device* Overlord::GetDevice(void)
{
	return m_system->m_graphics->m_d3d->m_device;
}

HWND Overlord::GetHwnd(void)
{
	return m_system->m_hWnd;
}

DX11System* Overlord::GetDX11System(void)
{
	return m_system->m_graphics->m_d3d;
}

Camera* Overlord::GetCamera(void)
{
	return m_currentCamera;
}

Input* Overlord::GetInput(void)
{
	return m_system->m_input;
}

ShaderManager* Overlord::GetShaders(void)
{
	return m_system->m_shaderManager;
}