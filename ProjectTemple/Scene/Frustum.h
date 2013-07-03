///////////////////////////////////////////////////////////////
// Filename:	Frustum.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __FRUSTUM_H_
#define __FRUSTUM_H_

#include <D3DX10math.h>

namespace Engine
{
	class Frustum
	{
	private:
		D3DXPLANE m_planes[6];
	public:
		Frustum(void);
		Frustum(const Frustum &other);
		virtual ~Frustum(void);

		void Construct(float screenDepth, D3DXMATRIX proj, D3DXMATRIX view);

		bool CheckPoint(float x, float y, float z);
		bool CheckCube(float xCenter, float yCenter, float zCenter, float radius);
		bool CheckSphere(float xCenter, float yCenter, float zCenter, float radius);
		bool CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize);
	};
};

#endif //__FRUSTUM_H_