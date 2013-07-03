///////////////////////////////////////////////////////////////
// Filename:	Overlord.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __OVERLORD_H_
#define __OVERLORD_H_

#include <Systems\System.h>

namespace Engine
{
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
		static inline Overlord* GetInstance(void)
		{
			if(m_instance == NULL)
			{
				LogManager::GetInstance()->Warning("Overlord::GetInstance - System not set!");
				m_instance = new Overlord();
				m_destroyer.setSingleton(m_instance);
			}
			return m_instance;
		}

		static inline void SetSystem(System* sys)
		{
			if(m_instance == NULL)
			{
				m_instance = new Overlord();
				m_destroyer.setSingleton(m_instance);
			}
			m_instance->m_system = sys;
		}

		void SetCamera(Camera* cam){m_currentCamera = cam;}
		void SetScene(Scene* scene){m_system->m_graphics->SetScene(scene);}
		System* GetSystem(void){return m_system;}
		ID3D11DeviceContext* GetDeviceContext(void){return m_system->m_graphics->m_d3d->m_deviceContext;}
		ID3D11Device* GetDevice(void){return m_system->m_graphics->m_d3d->m_device;}
		HWND GetHwnd(void){return m_system->m_hWnd;}
		DX11System* GetDX11System(void){return m_system->m_graphics->m_d3d;}
		Camera* GetCamera(void){return m_currentCamera;}
		Input* GetInput(void){return m_system->m_input;}
		ShaderManager* GetShaders(void){return m_system->m_shaderManager;}
		//hkpWorld* GetHavokWorld(void){return m_system->m_havokSystem->m_world;}
		//ULONG GetDeltaTime(void){return m_DeltaTime;}
	};
}

#endif //__OVERLORD_H_