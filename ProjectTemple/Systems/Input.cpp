///////////////////////////////////////////////////////////////
// Filename:	Input.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\Input.h>
#include <Systems\LogManager.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Input::Input(void)
{
	m_DIObject = NULL;
	m_DIKeyboard = NULL;
	m_DIMouse = NULL;
	m_currInput = INPUT_DI;
	for(int i = 0; i < 256; i ++)
		m_keys[i]=false;
	for(int i = 0; i < 256; i ++)
		m_lastKeys[i]=false;
	m_lastLeft = false;
	m_lastRight = false;
	m_lastMiddle = false;
	ZeroMemory(&m_mouseState, sizeof(MOUSESTATE));
}

Input::Input(const Input &other)
{
}

Input::~Input(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
bool Input::Initialize(TYPE type)
{
	HRESULT result;
	m_currInput = type;

	if(m_currInput == INPUT_DI)
	{
		result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
									IID_IDirectInput8, (void**)&m_DIObject, NULL);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to be created");
			return false;
		}

		//Keyboard

		result = m_DIObject->CreateDevice(GUID_SysKeyboard, &m_DIKeyboard, NULL);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to create the keyboard device");
			return false;
		}

		result = m_DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to set the keyboard data format");
			return false;
		}

		result = m_DIKeyboard->SetCooperativeLevel(NULL, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to set the keyboards cooperative level");
			return false;
		}

		result = m_DIKeyboard->Acquire();
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to acquire the keyboard");
			return false;
		}

		//Mouse

		result = m_DIObject->CreateDevice(GUID_SysMouse, &m_DIMouse, NULL);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to create the mouse device");
			return false;
		}

		result = m_DIMouse->SetDataFormat(&c_dfDIMouse);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to set the mouse's data format");
			return false;
		}

		result = m_DIMouse->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to set the mouse's cooperative level");
			return false;
		}

		result = m_DIMouse->Acquire();
		if(FAILED(result))
		{
			LogManager::GetInstance()->Error("Input::Initialize DirectInput failed to acquire the mouse");
			return false;
		}

		return true;
	}
	else
	{
		RAWINPUTDEVICE rid[2];

		rid[0].usUsagePage = 0x01;
		rid[0].usUsage = 0x02; //mouse
		rid[0].dwFlags = 0;
		rid[0].hwndTarget = 0;

		rid[1].usUsagePage = 0x01;
		rid[1].usUsage = 0x06; //mouse
		rid[1].dwFlags = RIDEV_NOLEGACY;
		rid[1].hwndTarget = 0;

		if(RegisterRawInputDevices(rid, 2, sizeof(rid[0])) == FALSE)
		{
			LogManager::GetInstance()->Error("Input::Initialize Raw Input could not be initialized (%u)", GetLastError());
			return false;
		}

		return true;
	}

	LogManager::GetInstance()->Warning("Input::Initialize Unexpected end of function!");
	return true;
}

bool Input::Update(LPARAM lParam)
{
	if(m_currInput == INPUT_DI)
	{
		char temp[256];
		if(FAILED(m_DIKeyboard->GetDeviceState(sizeof(temp), (LPVOID)&temp)))
		{
			LogManager::GetInstance()->Error("Input::Update DirectInput could not acquire the keyboard state");
			return false;
		}

		for(USHORT i = 0; i < 256; i++)
		{
			if(temp[i] & 0x80)
				m_keys[i] = true;
			else
				m_keys[i] = false;
		}

		DIMOUSESTATE mouseTemp;

		if(DIERR_INPUTLOST == m_DIMouse->GetDeviceState(sizeof(mouseTemp), (LPVOID)&mouseTemp))
			m_DIMouse->Acquire();

		if((mouseTemp.rgbButtons[0] & 0x80) && m_lastLeft)
			m_mouseState.left = false;
		else if((mouseTemp.rgbButtons[0] & 0x80) && !m_lastLeft)
		{
			m_lastLeft = true;
			m_mouseState.left = true;
		}
		else
		{
			m_lastLeft = false;
			m_mouseState.left = false;
		}

		if((mouseTemp.rgbButtons[1] & 0x80) && m_lastRight)
			m_mouseState.right = false;
		else if((mouseTemp.rgbButtons[1] & 0x80) && !m_lastRight)
		{
			m_lastRight = true;
			m_mouseState.right = true;
		}
		else
		{
			m_lastRight = false;
			m_mouseState.right = false;
		}

		if((mouseTemp.rgbButtons[2] & 0x80) && m_lastMiddle)
			m_mouseState.middle = false;
		else if((mouseTemp.rgbButtons[2] & 0x80) && !m_lastMiddle)
		{
			m_lastMiddle = true;
			m_mouseState.middle = true;
		}
		else
		{
			m_lastMiddle = false;
			m_mouseState.middle = false;
		}

		m_mouseState.x += mouseTemp.lX;
		m_mouseState.y += mouseTemp.lY;

		return true;
	}
	else if(m_currInput == INPUT_RAW)
	{
		if(lParam == NULL) return false;

		UINT dwSize;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if(lpb == NULL)
			return false;

		if(GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			LogManager::GetInstance()->Warning("Input::Update GetRawInputData did not return the correct size");

		RAWINPUT* raw = (RAWINPUT*)lpb;

		if(raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			if(raw->data.keyboard.Message == WM_KEYDOWN)
				m_keys[raw->data.keyboard.VKey] = true;
			else
				m_keys[raw->data.keyboard.VKey] = false;
		}
		else if(raw->header.dwType == RIM_TYPEMOUSE)
		{
			m_mouseState.x += raw->data.mouse.lLastX;
			m_mouseState.y += raw->data.mouse.lLastY;

			if(raw->data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_DOWN)
				m_mouseState.left = true;

			if(raw->data.mouse.ulButtons & RI_MOUSE_RIGHT_BUTTON_DOWN)
				m_mouseState.right = true;

			if(raw->data.mouse.ulButtons & RI_MOUSE_MIDDLE_BUTTON_DOWN)
				m_mouseState.middle = true;
		}
		else
		{
			LogManager::GetInstance()->Warning("Input::Update RAWINPUT data type doesn't match");
		}

		delete[] lpb;

		return true;
	}
	else
	{
		LogManager::GetInstance()->Warning("Input::Update current input mode not recognized");
		return false;
	}
	LogManager::GetInstance()->Warning("Input::Update unexpected end of function");
	return true;
}

bool Input::IsKeyDown(USHORT key)
{
	USHORT temp = KeyConverter(key);
	if(m_lastKeys[temp] && m_keys[temp])
		return false;
	else if(!(m_lastKeys[temp]) && m_keys[temp])
	{
		m_lastKeys[temp] = true;
		return true;
	}
	else
	{
		m_lastKeys[temp] = false;
		return false;
	}
}

bool Input::IsKeyHeld(USHORT key)
{
	USHORT temp = KeyConverter(key);
	return m_keys[temp];
}

void Input::Reset(void)
{
	if(m_currInput == INPUT_RAW)
	{
		m_mouseState.middle = false;
		m_mouseState.left = false;
		m_mouseState.right = false;
	}
	m_mouseState.x = 0;
	m_mouseState.y = 0;
}

Input::MOUSESTATE Input::GetMouseState(void)
{
	return m_mouseState;
}

void Input::Shutdown(void)
{
	if(m_DIMouse != NULL)
	{
		m_DIMouse->Unacquire();
		m_DIMouse->Release();
		m_DIMouse = NULL;
	}

	if(m_DIKeyboard != NULL)
	{
		m_DIKeyboard->Unacquire();
		m_DIKeyboard->Release();
		m_DIKeyboard = NULL;
	}

	if(m_DIObject != NULL)
	{
		m_DIObject->Release();
		m_DIObject = NULL;
	}
}

///////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////
USHORT Input::KeyConverter(USHORT key)
{
	if(m_currInput == INPUT_RAW)
	{
		USHORT rawKey=0;
		switch(key)
		{
			case KEY_A:
				rawKey='A';
				break;
			case KEY_B:
				rawKey='B';
				break;
			case KEY_C:
				rawKey='C';
				break;
			case KEY_D:
				rawKey='D';
				break;
			case KEY_E:
				rawKey='E';
				break;
			case KEY_F:
				rawKey='F';
				break;
			case KEY_G:
				rawKey='G';
				break;
			case KEY_H:
				rawKey='H';
				break;
			case KEY_I:
				rawKey='I';
				break;
			case KEY_J:
				rawKey='J';
				break;
			case KEY_K:
				rawKey='K';
				break;
			case KEY_L:
				rawKey='L';
				break;
			case KEY_M:
				rawKey='M';
				break;
			case KEY_N:
				rawKey='N';
				break;
			case KEY_O:
				rawKey='O';
				break;
			case KEY_P:
				rawKey='P';
				break;
			case KEY_Q:
				rawKey='Q';
				break;
			case KEY_R:
				rawKey='R';
				break;
			case KEY_S:
				rawKey='S';
				break;
			case KEY_T:
				rawKey='T';
				break;
			case KEY_U:
				rawKey='U';
				break;
			case KEY_V:
				rawKey='V';
				break;
			case KEY_W:
				rawKey='W';
				break;
			case KEY_X:
				rawKey='X';
				break;
			case KEY_Y:
				rawKey='Y';
				break;
			case KEY_Z:
				rawKey='Z';
				break;
			case KEY_1:
				rawKey='1';
				break;
			case KEY_2:
				rawKey='2';
				break;
			case KEY_3:
				rawKey='3';
				break;
			case KEY_4:
				rawKey='4';
				break;
			case KEY_5:
				rawKey='5';
				break;
			case KEY_6:
				rawKey='6';
				break;
			case KEY_7:
				rawKey='7';
				break;
			case KEY_8:
				rawKey='8';
				break;
			case KEY_9:
				rawKey='9';
				break;
			case KEY_0:
				rawKey='0';
				break;
			case KEY_F1:
				rawKey=VK_F1;
				break;
			case KEY_F2:
				rawKey=VK_F2;
				break;
			case KEY_F3:
				rawKey=VK_F3;
				break;
			case KEY_F4:
				rawKey=VK_F4;
				break;
			case KEY_F5:
				rawKey=VK_F5;
				break;
			case KEY_F6:
				rawKey=VK_F6;
				break;
			case KEY_F7:
				rawKey=VK_F7;
				break;
			case KEY_F8:
				rawKey=VK_F8;
				break;
			case KEY_F9:
				rawKey=VK_F9;
				break;
			case KEY_F10:
				rawKey=VK_F10;
				break;
			case KEY_F11:
				rawKey=VK_F11;
				break;
			case KEY_F12:
				rawKey=VK_F12;
				break;
			case KEY_SPACE:
				rawKey=VK_SPACE;
				break;
			case KEY_ENTER:
				rawKey=VK_RETURN;
				break;
			case KEY_ESC:
				rawKey=VK_ESCAPE;
				break;
			case KEY_UP:
				rawKey=VK_UP;
				break;
			case KEY_DOWN:
				rawKey=VK_DOWN;
				break;
			case KEY_LEFT:
				rawKey=VK_LEFT;
				break;
			case KEY_RIGHT:
				rawKey=VK_RIGHT;
				break;
			default:
				rawKey=0;
		}
		return rawKey;
	}
	else if(m_currInput == INPUT_DI)
	{
		USHORT DIKey=0;
		switch(key)
		{
			case KEY_A:
				DIKey=DIK_A;
				break;
			case KEY_B:
				DIKey=DIK_B;
				break;
			case KEY_C:
				DIKey=DIK_C;
				break;
			case KEY_D:
				DIKey=DIK_D;
				break;
			case KEY_E:
				DIKey=DIK_E;
				break;
			case KEY_F:
				DIKey=DIK_F;
				break;
			case KEY_G:
				DIKey=DIK_G;
				break;
			case KEY_H:
				DIKey=DIK_H;
				break;
			case KEY_I:
				DIKey=DIK_I;
				break;
			case KEY_J:
				DIKey=DIK_J;
				break;
			case KEY_K:
				DIKey=DIK_K;
				break;
			case KEY_L:
				DIKey=DIK_L;
				break;
			case KEY_M:
				DIKey=DIK_M;
				break;
			case KEY_N:
				DIKey=DIK_N;
				break;
			case KEY_O:
				DIKey=DIK_O;
				break;
			case KEY_P:
				DIKey=DIK_P;
				break;
			case KEY_Q:
				DIKey=DIK_Q;
				break;
			case KEY_R:
				DIKey=DIK_R;
				break;
			case KEY_S:
				DIKey=DIK_S;
				break;
			case KEY_T:
				DIKey=DIK_T;
				break;
			case KEY_U:
				DIKey=DIK_U;
				break;
			case KEY_V:
				DIKey=DIK_V;
				break;
			case KEY_W:
				DIKey=DIK_W;
				break;
			case KEY_X:
				DIKey=DIK_X;
				break;
			case KEY_Y:
				DIKey=DIK_Y;
				break;
			case KEY_Z:
				DIKey=DIK_Z;
				break;
			case KEY_1:
				DIKey=DIK_1;
				break;
			case KEY_2:
				DIKey=DIK_2;
				break;
			case KEY_3:
				DIKey=DIK_3;
				break;
			case KEY_4:
				DIKey=DIK_4;
				break;
			case KEY_5:
				DIKey=DIK_5;
				break;
			case KEY_6:
				DIKey=DIK_6;
				break;
			case KEY_7:
				DIKey=DIK_7;
				break;
			case KEY_8:
				DIKey=DIK_8;
				break;
			case KEY_9:
				DIKey=DIK_9;
				break;
			case KEY_0:
				DIKey=DIK_0;
				break;
			case KEY_F1:
				DIKey=DIK_F1;
				break;
			case KEY_F2:
				DIKey=DIK_F2;
				break;
			case KEY_F3:
				DIKey=DIK_F3;
				break;
			case KEY_F4:
				DIKey=DIK_F4;
				break;
			case KEY_F5:
				DIKey=DIK_F5;
				break;
			case KEY_F6:
				DIKey=DIK_F6;
				break;
			case KEY_F7:
				DIKey=DIK_F7;
				break;
			case KEY_F8:
				DIKey=DIK_F8;
				break;
			case KEY_F9:
				DIKey=DIK_F9;
				break;
			case KEY_F10:
				DIKey=DIK_F10;
				break;
			case KEY_F11:
				DIKey=DIK_F11;
				break;
			case KEY_F12:
				DIKey=DIK_F12;
				break;
			case KEY_SPACE:
				DIKey=DIK_SPACE;
				break;
			case KEY_ENTER:
				DIKey=DIK_RETURN;
				break;
			case KEY_ESC:
				DIKey=DIK_ESCAPE;
				break;
			case KEY_UP:
				DIKey=DIK_UP;
				break;
			case KEY_DOWN:
				DIKey=DIK_DOWN;
				break;
			case KEY_LEFT:
				DIKey=DIK_LEFT;
				break;
			case KEY_RIGHT:
				DIKey=DIK_RIGHT;
				break;
			default:
				DIKey=0;
		}
		return DIKey;
	}
	return 257;
}