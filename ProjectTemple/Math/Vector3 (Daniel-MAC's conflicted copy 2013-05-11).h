//#ifndef __VECTOR3_H_
//#define __VECTOR3_H_
//
//#include <Math\Math.h>
//
//namespace Engine
//{
//	class Vector2;
//
//	class Vector3
//	{
//	public:
//		float x, y, z;
//	public:
//		Vector3(void);
//		Vector3(const Vector2& vec2, const float fz);
//		Vector3(const float fx, const float fy, const float fz);
//		Vector3(const float coord[3]);
//		Vector3(const int coord[3]);
//		Vector3(float *const r);
//		Vector3(const float scalar);
//
//		void Swap(Vector3& other);
//
//
//		float* ptr(void);
//		const float* ptr(void) const;
//
//		float  operator[] (const size_t i) const;
//		float& operator[] (const size_t i);
//
//		bool operator== (const Vector3& other) const;
//		bool operator!= (const Vector3& other) const;
//
//		Vector3& operator= (const Vector3& other);
//		Vector3& operator= (const Vector2& vec2);
//		Vector3& operator= (const float scalar);
//		const Vector3& operator+ (void) const;
//		Vector3 operator- (void) const;
//
//		Vector3 operator+ (const Vector3& other) const;
//		Vector3 operator+ (const float scalar) const;
//		Vector3 operator- (const Vector3& other) const;
//		Vector3 operator- (const float scalar) const;
//		Vector3 operator* (const Vector3& other) const;
//		Vector3 operator* (const float scalar) const;
//		Vector3 operator/ (const Vector3& other) const;
//		Vector3 operator/ (const float scalar) const;
//
//		Vector3& operator+= (const Vector3& other);
//		Vector3& operator+= (const float scalar);
//		Vector3& operator-= (const Vector3& other);
//		Vector3& operator-= (const float scalar);
//		Vector3& operator*= (const Vector3& other);
//		Vector3& operator*= (const float scalar);
//		Vector3& operator/= (const Vector3& other);
//		Vector3& operator/= (const float scalar);
//	};
//}
//
//#endif //__VECTOR_H_