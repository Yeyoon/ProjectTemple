#ifndef __MATRIX4_H_
#define __MATRIX4_H_

namespace Engine
{
	class Matrix4
	{
	protected:
		union {
			float m[4][4];
			float _m[16];
		};
	public:
		Matrix4(void);
	};
}

#endif //__MATRIX4_H_