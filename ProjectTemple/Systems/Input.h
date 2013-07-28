///////////////////////////////////////////////////////////////
// Filename:	Input.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __INPUT_H_
#define __INPUT_H_

#include <dinput.h>
#include "Thread.h"

namespace Engine
{
	enum KEYS
	{
		KEY_A=1,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_SPACE,
		KEY_ENTER,
		KEY_ESC,
		KEY_TILDE,
		KEY_MINUS,
		KEY_PLUS,
		KEY_CURLYLEFT,
		KEY_CURLYRIGHT,
		KEY_BACKSLASH,
		KEY_COLON,
		KEY_QUOTE,
		KEY_COMMA,
		KEY_PERIOD,
		KEY_FORWARDSLASH,
		KEY_TAB,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_RIGHTCONTROL,
		KEY_LEFTCONTROL,
		KEY_RIGHTALT,
		KEY_LEFTALT,
		KEY_RIGHTSHIFT,
		KEY_LEFTSHIFT
	};

	class Input
	{
	public:
		enum TYPE
		{
			INPUT_DI = 0,
			INPUT_RAW
		};
	private:
		struct MOUSESTATE
		{
			long x,y;
			bool left,middle,right;
			bool b1,b2,b3,b4,b5;
			bool wheel;
		};
		LPDIRECTINPUT8 m_DIObject;
		LPDIRECTINPUTDEVICE8 m_DIKeyboard;
		LPDIRECTINPUTDEVICE8 m_DIMouse;
		TYPE m_currInput;
		bool m_keys[256];
		bool m_lastKeys[256];
		bool m_lastLeft, m_lastRight, m_lastMiddle;
		MOUSESTATE m_mouseState;
	public:
		Input(void);
		Input(const Input &other);
		virtual ~Input(void);

		bool Initialize(TYPE type);
		void Shutdown(void);
		bool Update(LPARAM lParam=NULL);
		void UpdateThreaded(LPARAM lParam=NULL);
		void Reset(void);

		bool IsKeyDown(USHORT key);
		bool IsKeyHeld(USHORT key);
		MOUSESTATE GetMouseState(void);
	private:
		Engine::Thread *m_thread;
		USHORT KeyConverter(USHORT key);
		static void _threadUpdateFunc(void* caller);
	};
};
#endif