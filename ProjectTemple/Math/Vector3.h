#ifndef __VECTOR3_H_
#define __VECTOR3_H_

namespace Engine
{
	class Vector2;
	class Quaternion;
	class Radian;

	class Vector3
	{
	public:
		float x, y, z;
	public:
		Vector3(void);
		Vector3(const Vector2& vec2, const float fz);
		Vector3(const float fx, const float fy, const float fz);
		Vector3(const float coord[3]);
		Vector3(const int coord[3]);
		Vector3(float *const r);
		Vector3(const float scalar);

		void Swap(Vector3& other);
		float Length(void) const;
		float SquaredLength(void) const;
		float Distance(const Vector3& other) const;
		float SquaredDistance(const Vector3& other) const;
		float DotProduct(const Vector3& other) const;
		float AbsDotProduct(const Vector3& other) const;
		float Normalise(void);
		Vector3 CrossProduct(const Vector3& other) const;
		Vector3 MidPoint(const Vector3& other) const;
		void MakeFloor(const Vector3& other);
		void MakeCeil(const Vector3& other);
		Vector3 Perpendicular(void) const;
		Radian AngleBetween(const Vector3& other) const;
		//Quaternion GetRotationTo(const Vector3& other, const Vector3& fallbackAxis=Vector3::ZERO) const;
		bool isZeroLength(void) const;
		Vector3 NormalisedCopy(void) const;
		Vector3 Reflect(const Vector3& normal) const;
		//bool PositionEquals(const Vector3& other, float tolerance = 1e-03) const;
		//bool PositionCloses(const Vector3& other, float tolerance = 1e-03) const;
		bool DirectionEquals(const Vector3& other, const Radian &tolerance) const;
		bool isNaN(void) const;
		Vector3 PrimaryAxis(void) const;

		float* ptr(void);
		const float* ptr(void) const;

		float  operator[] (const size_t i) const;
		float& operator[] (const size_t i);

		bool operator== (const Vector3& other) const;
		bool operator!= (const Vector3& other) const;
		bool operator< (const Vector3& other) const;
		bool operator> (const Vector3& other) const;

		Vector3& operator= (const Vector3& other);
		Vector3& operator= (const Vector2& vec2);
		Vector3& operator= (const float scalar);
		const Vector3& operator+ (void) const;
		Vector3 operator- (void) const;

		Vector3 operator+ (const Vector3& other) const;
		Vector3 operator+ (const float scalar) const;
		Vector3 operator- (const Vector3& other) const;
		Vector3 operator- (const float scalar) const;
		Vector3 operator* (const Vector3& other) const;
		Vector3 operator* (const float scalar) const;
		Vector3 operator/ (const Vector3& other) const;
		Vector3 operator/ (const float scalar) const;

		Vector3& operator+= (const Vector3& other);
		Vector3& operator+= (const float scalar);
		Vector3& operator-= (const Vector3& other);
		Vector3& operator-= (const float scalar);
		Vector3& operator*= (const Vector3& other);
		Vector3& operator*= (const float scalar);
		Vector3& operator/= (const Vector3& other);
		Vector3& operator/= (const float scalar);

		friend Vector3 operator+ (const float lhs, const Vector3& rhs);
		friend Vector3 operator+ (const Vector3& lhs, const float rhs);
		friend Vector3 operator- (const float lhs, const Vector3& rhs);
		friend Vector3 operator- (const Vector3& lhs, const float rhs);
		friend Vector3 operator* (const float lhs, const Vector3& rhs);
		friend Vector3 operator/ (const float lhs, const Vector3& rhs);

		static const Vector3 UNIT_SCALE;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 ZERO;
	};
}

#endif //__VECTOR_H_