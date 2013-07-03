#ifndef __MATH_H_
#define __MATH_H_

#include <assert.h>

namespace Engine
{
	class Degree;

	class Radian
	{
		float m_rad;
	public:
		explicit Radian(float r=0) : m_rad(r) {}
		Radian(const Degree& d);
		Radian(const Radian& other);
		Radian& operator= (const float& f);
		Radian& operator= (const Radian& r);
		Radian& operator= (const Degree& d);

		float valueDegrees(void) const;
		float valueRadians(void) const;

		const Radian& operator+ (void) const;
		Radian operator- (void) const;

		Radian operator+ (const Radian& r) const;
		Radian operator+ (const Degree& d) const;
		Radian operator- (const Radian& r) const;
		Radian operator- (const Degree& d) const;
		Radian operator* (float f) const;
		Radian operator* (const Radian& r) const;
		Radian operator/ (float f) const;

		Radian& operator+= (const Radian& r);
		Radian& operator+= (const Degree& d);
		Radian& operator-= (const Radian& r);
		Radian& operator-= (const Degree& d);
		Radian& operator*= (float f);
		Radian& operator/= (float f);

		bool operator<  (const Radian& r) const;
		bool operator<= (const Radian& r) const;
		bool operator== (const Radian& r) const;
		bool operator!= (const Radian& r) const;
		bool operator>= (const Radian& r) const;
		bool operator>  (const Radian& r) const;
	};

	class Degree
	{
		float m_deg;
	public:
		explicit Degree(float d=0) : m_deg(d) {}
		Degree(const Radian& r);
		Degree(const Degree& other);
		Degree& operator= (const float& f);
		Degree& operator= (const Degree& d);
		Degree& operator= (const Radian& r);

		float valueDegrees(void) const;
		float valueRadians(void) const;

		const Degree& operator+ (void) const;
		Degree operator- (void) const;
		
		Degree operator+ (const Degree& d) const;
		Degree operator+ (const Radian& r) const;
		Degree operator- (const Degree& d) const;
		Degree operator- (const Radian& r) const;
		Degree operator* (float f) const;
		Degree operator* (const Degree& d) const;
		Degree operator/ (float f) const;
		
		Degree& operator+= (const Degree& d);
		Degree& operator+= (const Radian& r);
		Degree& operator-= (const Degree& d);
		Degree& operator-= (const Radian& r);
		Degree& operator*= (float f);
		Degree& operator/= (float f);

		bool operator<  (const Degree& d) const;
		bool operator<= (const Degree& d) const;
		bool operator== (const Degree& d) const;
		bool operator!= (const Degree& d) const;
		bool operator>= (const Degree& d) const;
		bool operator>  (const Degree& d) const;
	};

	class Math
	{
	public:
		static float	Abs		(float f);
		static Degree	Abs		(Degree& d);
		static Radian	Abs		(Radian& r);
		static Radian	ACos	(float f);
		static Radian	ASin	(float f);
		static Radian	ATan	(float f);
		static Radian	ATan2	(float fx, float fy);
		static bool		isNaN	(float f);
		static float	Ceil	(float f);
		static float	Floor	(float f);
		static float	Cos		(const Radian& r);
		static float	Cos		(const float r);
		static float	Cos		(const Degree& d);
		static float	Sin		(const Radian& r);
		static float	Sin		(const float r);
		static float	Sin		(const Degree& d);
		static float	Tan		(const Radian& r);
		static float	Tan		(const float r);
		static float	Tan		(const Degree& d);
		static float	Exp		(float f);
		static float	Log		(float f);
		static float	LogN	(float base, float value);
		static float	Pow		(float base, float exp);
		static float	Sqr		(float f);
		static float	Sqrt	(float f);
		static Radian	Sqrt	(Radian& r);
		static Degree	Sqrt	(Degree& d);
		static float	DegreesToRadians(float f);
		static float	RadiansToDegrees(float f);

		//Random
	private:
		static int m_seed;
		static long m_ran1idnum;
		//static int m_qd2idnum;
	public:
		static float UnitRandom(void);
		static float RangeRandom(float min, float max);
		static float BoxMullerRandom(float m, float s);
		//EndRandom

		template<typename T>
		static T Clamp(T val, T min, T max)
		{
			assert(min <= max);
			return std::max(std::min(val, max), min);
		}

		static const float PI;
		static const float TWO_PI;
		static const float HALF_PI;
		static const float fDeg2Rad;
		static const float fRad2Deg;
	};
}

#endif //__MATH_H_