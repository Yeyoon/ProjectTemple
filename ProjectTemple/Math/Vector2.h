#ifndef __VECTOR2_H_
#define __VECTOR2_H_

namespace Engine
{
	class Vector3;
	class Radian;

	class Vector2
	{
	public:
		float x, y;
	public:
		Vector2(void);
		Vector2(const float fx, const float fy);
		Vector2(const float scalar);
		Vector2(const float coord[2]);
		Vector2(float* const r);

		void Swap(Vector2 &other);
		float Length(void) const;
		float SquaredLength(void) const;
		float Distance(const Vector2 &other) const;
		float SquaredDistance(const Vector2 &other) const;
		float DotProduct(const Vector2 &other) const;
		float Normalise(void);
		Vector2 MidPoint(const Vector2 &other) const;
		Vector2 Perpendicular(void) const;
		float CrossProduct(const Vector2 &other) const;
		bool isZeroLength(void) const;
		Vector2 NormalisedCopy(void) const;
		Vector2 Reflect(const Vector2 &normal) const;
		bool isNaN(void) const;
		Radian AngleBetween(const Vector2 &other) const;
		Radian AngleTo(const Vector2 &other) const;

		float* ptr(void);
		const float* ptr(void) const;

		float		operator[]  (const size_t i) const;
		float&		operator[]  (const size_t i);

		Vector2&	operator=   (const Vector2 &other);
		Vector2&	operator=   (const float scalar);

		bool		operator==  (const Vector2 &other) const;
		bool		operator!=  (const Vector2 &other) const;
		bool		operator<	(const Vector2 &other) const;
		bool		operator>	(const Vector2 &other) const;

		Vector2		operator+	(const Vector2 &other) const;
		Vector2		operator-	(const Vector2 &other) const;
		Vector2		operator*	(const float scalar) const;
		Vector2		operator*	(const Vector2 &other) const;
		Vector2		operator/	(const float scalar) const;
		Vector2		operator/	(const Vector2 &other) const;

		Vector2&	operator+=	(const Vector2 &other);
		Vector2&	operator+=	(const float scalar);
		Vector2&	operator-=	(const Vector2 &other);
		Vector2&	operator-=	(const float scalar);
		Vector2&	operator*=	(const Vector2 &other);
		Vector2&	operator*=	(const float scalar);
		Vector2&	operator/=	(const Vector2 &other);
		Vector2&	operator/=	(const float scalar);

		const Vector2& operator+  (void) const;
		Vector2		   operator-  (void) const;

		friend Vector2 operator+ (const float lhs, const Vector2& rhs);
		friend Vector2 operator+ (const Vector2& lhs, const float rhs);
		friend Vector2 operator- (const float lhs, const Vector2& rhs);
		friend Vector2 operator- (const Vector2& lhs, const float rhs);
		friend Vector2 operator* (const float lhs, const Vector2& rhs);
		friend Vector2 operator/ (const float lhs, const Vector2& rhs);
		friend Vector2 operator/ (const Vector2& lhs, const float rhs);

		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;
		static const Vector2 NEGATIVE_UNIT_X;
		static const Vector2 NEGATIVE_UNIT_Y;
	};
}

#endif //__VECTOR2_H_