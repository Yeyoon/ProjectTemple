#include <Math\Math.h>
#include <math.h>

using namespace Engine;

const float Math::PI = 3.14159265358979323846f;
const float Math::TWO_PI = Math::PI * 2.f;
const float Math::HALF_PI = Math::PI / 2.f;
const float Math::fDeg2Rad = Math::PI/180.f;
const float Math::fRad2Deg = 180.0f/Math::PI;
int Math::m_seed = 0;
long Math::m_ran1idnum = 0;

////////////////////////////////////////////////////////////
//
// RADIAN
//
////////////////////////////////////////////////////////////
Radian::Radian(const Degree& d)
{
	m_rad = d.valueRadians();
}

Radian::Radian(const Radian& other)
{
	m_rad = other.m_rad;
}

Radian& Radian::operator= (const float& f)
{
	m_rad = f;
	return *this;
}

Radian& Radian::operator= (const Radian& r)
{
	m_rad = r.m_rad;
	return *this;
}

Radian& Radian::operator= (const Degree& d)
{
	m_rad = d.valueRadians();
	return *this;
}

float Radian::valueDegrees(void) const
{
	return Math::RadiansToDegrees(m_rad);
}

float Radian::valueRadians(void) const
{
	return m_rad;
}

const Radian& Radian::operator+ (void) const
{
	return *this;
}

Radian Radian::operator- (void) const
{
	return Radian(-m_rad);
}

Radian Radian::operator+ (const Radian& r) const
{
	return Radian(m_rad + r.m_rad);
}

Radian Radian::operator+ (const Degree& d) const
{
	return Radian(m_rad + d.valueRadians());
}

Radian Radian::operator- (const Radian& r) const
{
	return Radian(m_rad - r.m_rad);
}

Radian Radian::operator- (const Degree& d) const
{
	return Radian(m_rad - d.valueRadians());
}

Radian Radian::operator* (float f) const
{
	return Radian(m_rad * f);
}

Radian Radian::operator* (const Radian& r) const
{
	return Radian(m_rad * r.m_rad);
}

Radian Radian::operator/ (float f) const
{
	return Radian(m_rad / f);
}

Radian& Radian::operator+= (const Radian& r)
{
	m_rad += r.m_rad;

	return *this;
}

Radian& Radian::operator+= (const Degree& d)
{
	m_rad += d.valueRadians();

	return *this;
}

Radian& Radian::operator-= (const Radian& r)
{
	m_rad -= r.m_rad;

	return *this;
}

Radian& Radian::operator-= (const Degree& d)
{
	m_rad -= d.valueRadians();

	return *this;
}

Radian& Radian::operator*= (float f)
{
	m_rad *= f;

	return *this;
}

Radian& Radian::operator/= (float f)
{
	m_rad /= f;

	return *this;
}

bool Radian::operator<  (const Radian& r) const
{
	return (m_rad < r.m_rad);
}

bool Radian::operator<= (const Radian& r) const
{
	return (m_rad <= r.m_rad);
}

bool Radian::operator== (const Radian& r) const
{
	return (m_rad == r.m_rad);
}

bool Radian::operator!= (const Radian& r) const
{
	return (m_rad != r.m_rad);
}

bool Radian::operator>= (const Radian& r) const
{
	return (m_rad >= r.m_rad);
}

bool Radian::operator>  (const Radian& r) const
{
	return (m_rad > r.m_rad);
}

////////////////////////////////////////////////////////////
//
// DEGREE
//
////////////////////////////////////////////////////////////
Degree::Degree(const Radian& r)
{
	m_deg = r.valueDegrees();
}

Degree::Degree(const Degree& other)
{
	m_deg = other.m_deg;
}

Degree& Degree::operator= (const float& f)
{
	m_deg = f;
	return *this;
}

Degree& Degree::operator= (const Degree& d)
{
	m_deg = d.m_deg;
	return *this;
}

Degree& Degree::operator= (const Radian& r)
{
	m_deg = r.valueDegrees();
	return *this;
}

float Degree::valueDegrees(void) const
{
	return m_deg;
}

float Degree::valueRadians(void) const
{
	return Math::DegreesToRadians(m_deg);
}

const Degree& Degree::operator+ (void) const
{
	return *this;
}

Degree Degree::operator- (void) const
{
	return Degree(-m_deg);
}
		
Degree Degree::operator+ (const Degree& d) const
{
	return Degree(m_deg + d.m_deg);
}

Degree Degree::operator+ (const Radian& r) const
{
	return Degree(m_deg + r.valueDegrees());
}

Degree Degree::operator- (const Degree& d) const
{
	return Degree(m_deg - d.m_deg);
}

Degree Degree::operator- (const Radian& r) const
{
	return Degree(m_deg - r.valueDegrees());
}

Degree Degree::operator* (float f) const
{
	return Degree(m_deg * f);
}

Degree Degree::operator* (const Degree& d) const
{
	return Degree(m_deg * d.m_deg);
}

Degree Degree::operator/ (float f) const
{
	return Degree(m_deg / f);
}
		
Degree& Degree::operator+= (const Degree& d)
{
	m_deg += d.m_deg;
	return *this;
}

Degree& Degree::operator+= (const Radian& r)
{
	m_deg += r.valueDegrees();
	return *this;
}

Degree& Degree::operator-= (const Degree& d)
{
	m_deg -= d.m_deg;
	return *this;
}

Degree& Degree::operator-= (const Radian& r)
{
	m_deg -= r.valueDegrees();
	return *this;
}

Degree& Degree::operator*= (float f)
{
	m_deg *= f;
	return *this;
}

Degree& Degree::operator/= (float f)
{
	m_deg /= f;
	return *this;
}

bool Degree::operator<  (const Degree& d) const
{
	return (m_deg < d.m_deg);
}

bool Degree::operator<= (const Degree& d) const
{
	return (m_deg <= d.m_deg);
}

bool Degree::operator== (const Degree& d) const
{
	return (m_deg == d.m_deg);
}

bool Degree::operator!= (const Degree& d) const
{
	return (m_deg != d.m_deg);
}

bool Degree::operator>= (const Degree& d) const
{
	return (m_deg >= d.m_deg);
}

bool Degree::operator>  (const Degree& d) const
{
	return (m_deg > d.m_deg);
}

////////////////////////////////////////////////////////////
//
// MATH
//
////////////////////////////////////////////////////////////
float Math::Abs(float f)
{
	return abs(f);
}

Degree Math::Abs(Degree& d)
{
	return Degree(abs(d.valueDegrees()));
}

Radian Math::Abs(Radian& r)
{
	return Radian(abs(r.valueRadians()));
}

Radian Math::ACos(float f)
{
	return Radian(acos(f));
}

Radian Math::ASin(float f)
{
	return Radian(asin(f));
}

Radian Math::ATan(float f)
{
	return Radian(atan(f));
}

Radian Math::ATan2(float fx, float fy)
{
	return Radian(atan2(fy, fx));
}

bool Math::isNaN(float f)
{
	return (f != f);
}

float Math::Ceil(float f)
{
	return ceil(f);
}

float Math::Floor(float f)
{
	return floor(f);
}

float Math::Cos(const Radian& r)
{
	return cos(r.valueRadians());
}

float Math::Cos(const float r)
{
	return cos(r);
}

float Math::Cos(const Degree& d)
{
	return cos(d.valueRadians());
}

float Math::Sin(const Radian& r)
{
	return sin(r.valueRadians());
}

float Math::Sin(const float r)
{
	return sin(r);
}

float Math::Sin(const Degree& d)
{
	return sin(d.valueRadians());
}

float Math::Tan(const Radian& r)
{
	return tan(r.valueRadians());
}

float Math::Tan(const float r)
{
	return tan(r);
}

float Math::Tan(const Degree& d)
{
	return tan(d.valueRadians());
}

float Math::Exp(float f)
{
	return exp(f);
}

float Math::Log(float f)
{
	return log(f);
}

float Math::LogN(float base, float value)
{
	return (log(value)/log(base));
}

float Math::Pow(float base, float exp)
{
	return pow(base, exp);
}

float Math::Sqr(float f)
{
	return f*f;
}

float Math::Sqrt(float f)
{
	return sqrt(f);
}

Radian Math::Sqrt(Radian& r)
{
	return Radian(sqrt(r.valueRadians()));
}

Degree Math::Sqrt(Degree& d)
{
	return Degree(sqrt(d.valueDegrees()));
}

float Math::DegreesToRadians(float f)
{
	return f*fDeg2Rad;
}

float Math::RadiansToDegrees(float f)
{
	return f*fRad2Deg;
}

#include <time.h>
#include <stdlib.h>
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float Math::UnitRandom(void)
{
	m_seed = (unsigned)time(NULL);
	m_ran1idnum = -(long)m_seed;
	//m_qd2idnum = -(int)m_seed;
	srand(m_seed);

	int j;
	long k;
	static long iy = 0;
	static long iv[NTAB];
	float temp;

	if(m_ran1idnum <= 0 || !iy)
	{
		if(-(m_ran1idnum) < 1) m_ran1idnum = 1;
		else m_ran1idnum = -(m_ran1idnum);
		for (j = NTAB + 7; j >= 0; j--)
		{
			k = (m_ran1idnum)/IQ;
			m_ran1idnum = IA * (m_ran1idnum - k * IQ) - IR * k;
			if(m_ran1idnum < 0) m_ran1idnum += IM;
			if(j < NTAB) iv[j] = m_ran1idnum;
		}
		iy = iv[0];
	}
	k = (m_ran1idnum) / IQ;
	m_ran1idnum = IA * (m_ran1idnum - k * IQ) - IR * k;
	if(m_ran1idnum < 0) m_ran1idnum += IM;
	j = iy/NDIV;
	iy = iv[j];
	iv[j] = m_ran1idnum;
	if(temp > RNMX)
		return (float)RNMX;
	else
		return temp;
}

#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

float Math::RangeRandom(float min, float max)
{
	return (UnitRandom() * (max - min)) + min;
}

float Math::BoxMullerRandom(float mean, float standardDev)
{
	int idnum = -1;
	double x1, x2, w, y1;
	static double y2;
	static int use_last = 0;

	if(use_last)
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do
		{
			x1 = 2.0 * UnitRandom() - 1.0;
			x2 = 2.0 * UnitRandom() - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return (mean + y1 * standardDev);
}