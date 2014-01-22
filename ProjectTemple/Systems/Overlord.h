///////////////////////////////////////////////////////////////
// Filename:	Overlord.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __OVERLORD_H_
#define __OVERLORD_H_

#include <Systems\Destroyer.h>
#include <Windows.h>

struct ID3D11DeviceContext;
struct ID3D11Device;

namespace Engine
{
	class Camera;
	class System;
	class Scene;
	class DX11System;
	class Input;
	class ShaderManager;

	class Overlord
	{
		friend class Destroyer<Overlord>;
	private:
		static Overlord* m_instance;
		static Destroyer<Overlord> m_destroyer;

		System* m_system;
		Camera* m_currentCamera;
		//ULONG m_DeltaTime;

		Overlord(void);
		virtual ~Overlord(void){}
	public:
		static Overlord* GetInstance(void);
		static void SetSystem(System* sys);

		void SetCamera(Camera* cam);
		void SetScene(Scene* scene);
		System* GetSystem(void);
		ID3D11DeviceContext* GetDeviceContext(void);
		ID3D11Device* GetDevice(void);
		HWND GetHwnd(void);
		DX11System* GetDX11System(void);
		Camera* GetCamera(void);
		Input* GetInput(void);
		ShaderManager* GetShaders(void);
	};
}

#endif //__OVERLORD_H_