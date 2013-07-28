///////////////////////////////////////////////////////////////
// Filename:	Camera.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\Overlord.h>
#include <Scene\Camera.h>

using namespace Engine;

///////////////////////////////////////////////////////////////
// Constructors and Destructors
///////////////////////////////////////////////////////////////
Camera::Camera(void)
{
	m_positionX = m_positionY = m_positionZ = 0.0f;
	m_lookAtX = m_lookAtY = 0.0f;
	m_lookAtZ = 1.0f;
	m_upX = 0.0f;
	m_upY = 1.0f;
	m_upZ = 0.0f;

	m_frustum = new Frustum();
	if(!m_frustum)
	{
		//LogManager::GetInstance()->Warning("Camera::Frustum not properly allocated");
	}
}

Camera::Camera(const Camera &other)
{
}

Camera::~Camera(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
void Camera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}

void Camera::SetLookAt(float x, float y, float z)
{
	m_lookAtX = x;
	m_lookAtY = y;
	m_lookAtZ = z;
}

void Camera::SetUp(float x, float y, float z)
{
	m_upX = x;
	m_upY = y;
	m_upZ = z;
}

D3DXVECTOR3 Camera::GetPosition(void)
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}

Frustum* Camera::GetFrustum(void)
{
	return m_frustum;
}

void Camera::Render(void)
{
	D3DXMatrixLookAtLH(&m_viewMatrix, 
		&D3DXVECTOR3(m_positionX, m_positionY, m_positionZ), 
		&D3DXVECTOR3(m_lookAtX, m_lookAtY, m_lookAtZ), 
		&D3DXVECTOR3(m_upX, m_upY, m_upZ));

	//Construct the Frustum
	D3DXMATRIX proj;

	Overlord::GetInstance()->GetDX11System()->GetProjectionMatrix(proj);
	m_frustum->Construct(g_zFar, proj, m_viewMatrix);
}

void Camera::GetViewMatrix(D3DXMATRIX &view)
{
	view = m_viewMatrix;
}