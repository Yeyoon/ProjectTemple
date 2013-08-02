///////////////////////////////////////////////////////////////
// Filename:	Graphics.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <Systems\DX11System.h>
#include <Systems\LogManager.h>
#include <Counters\FPSCounter.h>
#include <Counters\CPUCounter.h>
#include <Counters\Timer.h>
#include <Shader\LightShader.h>
#include <Shader\TextureShader.h>
#include <Scene\Camera.h>
#include <Scene\Model.h>
#include <Scene\Light.h>
#include <Scene\Bitmap.h>
#include <Scene\Frustum.h>
#include <Scene\Scene.h>
#include <Text\Text.h>

#include <Windows.h>

namespace Engine
{
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

		bool Initialize(UINT screenWidth, UINT screenHeight, HWND hWnd);
		void Shutdown(void);
		bool Frame(void);

		void SetScene(Scene* scene);
	private:
		bool Render(void);
	};
};

#endif //__GRAPHICS_H_