///////////////////////////////////////////////////////////////
// Filename:	System.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Math\Vector2.h>

namespace Engine
{
	class Graphics;
	class SoundSystem;
	class ShaderManager;
	class Input;

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

		bool Initialize(unsigned int winHeight, unsigned int winWidth);
		void Shutdown(void);
		void Run(void);
		Vector2 GetWindowSize(void);

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

		bool Frame(void);
		void InitializeWindows(unsigned int screenWidth, unsigned int screenHeight);
		void ShutdownWindows(void);
	};
};

#endif //__SYSTEM_H_