///////////////////////////////////////////////////////////////
// Filename:	Graphics.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <Windows.h>

namespace Engine
{
	class DX11System;
	class Scene;
	class Timer;
	class FPSCounter;
	class CPUCounter;

	const bool	g_fullScreen = false;
	const bool  g_vSync = false;
	const float g_zFar = 10000.0f;
	const float g_zNear = 0.1f;

	class Graphics
	{
		friend class Overlord;
	private:
		DX11System* m_d3d;
		Scene*		m_currentScene;
		Timer*		m_timer;

#ifdef _DEBUG
		FPSCounter* m_fpsCounter;
		CPUCounter* m_cpuCounter;
		//Text*		m_fps;
		//Text*		m_cpu;
#endif //_DEBUG
	public:
		Graphics(void);
		Graphics(const Graphics &other);
		virtual ~Graphics(void);

		bool Initialize(unsigned int screenWidth, unsigned int screenHeight, HWND hWnd);
		void Shutdown(void);
		bool Frame(void);

		void SetScene(Scene* scene);
	private:
		bool Render(void);
	};
};

#endif //__GRAPHICS_H_