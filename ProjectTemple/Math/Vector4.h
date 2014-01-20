#ifndef __VECTOR4_H_
#define __VECTOR4_H_

namespace Engine
{
	class Vector3;

	class Vector4
	{
	public:
		float x, y, z, w;
	public:
		Vector4(void);
		Vector4(const float fx, const float fy, const float fz, const float fw);
		Vector4(const float coord[4]);
		Vector4(const int coord[4]);
		Vector4(float* const r);
		Vector4(const float scalar);
		Vector4(const Vector3& rhs, const float fw = 1.0f);

		void swap(Vector4 &other);
		float dotProduct(const Vector4& vec) const;
		bool isNaN(void) const;

		float operator[] (const size_t i) const;
		float& operator[] (const size_t i);

		float* ptr(void);
		const float* ptr(void) const;

		bool operator== (const Vector4& other) const;
		bool operator!= (const Vector4& other) const;

		const Vector4& operator+ (void) const;
		Vector4& operator- (void) const;

		Vector4& operator= (const Vector4& other);
		Vector4& operator= (const Vector3& vec3);
		Vector4& operator= (const float scalar);

		Vector4 operator+ (const Vector4& other) const;
		Vector4 operator+ (const float scalar) const;
		Vector4 operator- (const Vector4& other) const;
		Vector4 operator- (const float scalar) const;
		Vector4 operator* (const Vector4& other) const;
		Vector4 operator* (const float scalar) const;
		Vector4 operator/ (const Vector4& other) const;
		Vector4 operator/ (const float scalar) const;

		Vector4& operator+= (const Vector4& other);
		Vector4& operator+= (const float scalar);
		Vector4& operator-= (const Vector4& other);
		Vector4& operator-= (const float scalar);
		Vector4& operator*= (const Vector4& other);
		Vector4& operator*= (const float scalar);
		Vector4& operator/= (const Vector4& other);
		Vector4& operator/= (const float scalar);

		friend Vector4 operator+ (const float lhs, const Vector4& rhs);
		friend Vector4 operator+ (const Vector4& lhs, const float rhs);
		friend Vector4 operator- (const float lhs, const Vector4& rhs);
		friend Vector4 operator- (const Vector4& lhs, const float rhs);
		friend Vector4 operator* (const float lhs, const Vector4& rhs);
		friend Vector4 operator/ (const float lhs, const Vector4& rhs);

		static const Vector4 ZERO;
	};
}

#endif //__VECTOR_H_