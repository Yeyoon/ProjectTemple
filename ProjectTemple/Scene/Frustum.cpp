///////////////////////////////////////////////////////////////
// Filename:	Frustum.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Scene\Frustum.h>

using namespace Engine;

Frustum::Frustum(void)
{
}

Frustum::Frustum(const Frustum &other)
{
}

Frustum::~Frustum(void)
{
}

///////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////
void Frustum::Construct(float screenDepth, D3DXMATRIX proj, D3DXMATRIX view)
{
	float zMin, r;
	D3DXMATRIX fMat;

	zMin = -proj._43 / proj._33;
	r = screenDepth / (screenDepth - zMin);
	proj._33 = r;
	proj._43 = -r * zMin;

	D3DXMatrixMultiply(&fMat, &view, &proj);

	//close
	m_planes[0].a = fMat._14 + fMat._13;
	m_planes[0].b = fMat._24 + fMat._23;
	m_planes[0].c = fMat._34 + fMat._33;
	m_planes[0].d = fMat._44 + fMat._43;
	D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

	//far
	m_planes[1].a = fMat._14 - fMat._13; 
	m_planes[1].b = fMat._24 - fMat._23;
	m_planes[1].c = fMat._34 - fMat._33;
	m_planes[1].d = fMat._44 - fMat._43;
	D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

	//left
	m_planes[2].a = fMat._14 + fMat._11; 
	m_planes[2].b = fMat._24 + fMat._21;
	m_planes[2].c = fMat._34 + fMat._31;
	m_planes[2].d = fMat._44 + fMat._41;
	D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

	//right
	m_planes[3].a = fMat._14 - fMat._11; 
	m_planes[3].b = fMat._24 - fMat._21;
	m_planes[3].c = fMat._34 - fMat._31;
	m_planes[3].d = fMat._44 - fMat._41;
	D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

	//top
	m_planes[4].a = fMat._14 - fMat._12; 
	m_planes[4].b = fMat._24 - fMat._22;
	m_planes[4].c = fMat._34 - fMat._32;
	m_planes[4].d = fMat._44 - fMat._42;
	D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

	//bottom
	m_planes[5].a = fMat._14 + fMat._12;
	m_planes[5].b = fMat._24 + fMat._22;
	m_planes[5].c = fMat._34 + fMat._32;
	m_planes[5].d = fMat._44 + fMat._42;
	D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);
}

bool Frustum::CheckPoint(float x, float y, float z)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(x, y, z)) < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}
		
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}
		
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool Frustum::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(xCenter, yCenter, zCenter)) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;

	for(i=0; i<6; i++)
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}