#ifndef __QUATERNION_H_
#define __QUATERNION_H_

#include "Math\Math.h"
namespace Engine
{
	class Quaternion
	{
	public:
		float w, x, y, z;
	public:
		Quaternion(void) : w(1), x(0), y(0), z(0) {}
		Quaternion(float fw, float fx, float fy, float fz)
			: w(fw), x(fx), y(fy), z(fz) {}
		//Quaternion(const Matrix3& rot);

	};
}
#endif //__QUATERNION_H_