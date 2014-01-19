///////////////////////////////////////////////////////////////
// Filename:	System.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Systems\Input.h>
#include <Systems\Graphics.h>
#include <Systems\LogManager.h>
#include <Systems\SoundSystem.h>
#include <Shader\ShaderManager.h>
#include <Counters\Timer.h>
#include <Math\Vector2.h>

namespace Engine
{
	class System
	{
		friend class Overlord;
	private:
		LPCSTR			m_applicationName;
		HINSTANCE		m_hInstance;
		HWND			m_hWnd;
		static Input*	m_input;
		Graphics*		m_graphics;
		SoundSystem*	m_soundSystem;
		ShaderManager*	m_shaderManager;
		Vector2			m_windowSize;
		//Timer*			m_timer;
	public:
		System(void);
		System(const System &other);
		virtual ~System(void);

		bool Initialize(int winHeight, int winWidth);
		void Shutdown(void);
		void Run(void);
		Vector2 GetWindowSize(void);


		//LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

		bool Frame(void);
		void InitializeWindows(UINT screenWidth, UINT screenHeight);
		void ShutdownWindows(void);
	};
};

#endif //__SYSTEM_H_