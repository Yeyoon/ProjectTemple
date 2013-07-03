#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <Scene\Camera.h>
//#include <Systems\Havok.h>

namespace Engine
{
	class Player
	{
	private:
		Camera* m_camera;
		float m_xRot, m_yRot;
		float m_xMouseSens, m_yMouseSens;
		//Havok Character Controller
		//hkpCharacterRigidBody* m_player;
		//hkpRigidBody* m_playerBody;
		//hkpCharacterContext* m_playerContext;
	public:
		Player(void);
		virtual ~Player(void);

		void Initialize(void);
		void Update(double dt);
		void Shutdown(void);
	};
}
#endif //__PLAYER_H_