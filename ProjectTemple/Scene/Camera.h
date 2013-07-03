///////////////////////////////////////////////////////////////
// Filename:	Camera.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <Systems\LogManager.h>
#include <Scene\Frustum.h>
#include <D3DX10math.h>

namespace Engine
{
	class Camera
	{
		friend class Player;
	private:
		float m_positionX, m_positionY, m_positionZ;
		float m_lookAtX, m_lookAtY, m_lookAtZ;
		float m_upX, m_upY, m_upZ;
		D3DXMATRIX m_viewMatrix;
		Frustum* m_frustum;
	public:
		Camera(void);
		Camera(const Camera &other);
		virtual ~Camera(void);

		void SetPosition(float x, float y, float z);
		void SetLookAt(float x, float y, float z);
		void SetUp(float x, float y, float z);

		D3DXVECTOR3 GetPosition(void);

		void Render(void);
		void GetViewMatrix(D3DXMATRIX &view);
		Frustum* GetFrustum(void);
	};
};

#endif