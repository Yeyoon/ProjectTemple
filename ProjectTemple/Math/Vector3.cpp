#include <Math\Vector3.h>
#include <Math\Vector2.h>
#include <algorithm>

using namespace Engine;

const Vector3 Vector3::UNIT_X			= Vector3(1,0,0);
const Vector3 Vector3::UNIT_Y			= Vector3(0,1,0);
const Vector3 Vector3::UNIT_Z			= Vector3(0,0,1);
const Vector3 Vector3::NEGATIVE_UNIT_X	= Vector3(-1,0,0);
const Vector3 Vector3::NEGATIVE_UNIT_Y	= Vector3(0,-1,0);
const Vector3 Vector3::NEGATIVE_UNIT_Z	= Vector3(0,0,-1);
const Vector3 Vector3::ZERO				= Vector3(0,0,0);
const Vector3 Vector3::UNIT_SCALE		= Vector3(1,1,1);

Vector3::Vector3(const Vector2& vec2, const float fz)
{
	x = vec2.x;
	y = vec2.y;
	z = fz;
}

void Vector3::Swap(Vector3& other)
{
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(z, other.z);
}

float Vector3::Length(void) const
{
	return Math::Sqrt(x*x + y*y + z*z);
}

float Vector3::SquaredLength(void) const
{
	return (x*x + y*y + z*z);
}

float Vector3::Distance(const Vector3& other) const
{
	return (*this - other).Length();
}

float Vector3::SquaredDistance(const Vector3& other) const
{
	return (*this - other).SquaredLength();
}

float Vector3::DotProduct(const Vector3& other) const
{
	return (x*other.x + y*other.y + z*other.z);
}

float Vector3::AbsDotProduct(const Vector3& other) const
{
	return Math::Abs(x*other.x) + Math::Abs(y*other.y) + Math::Abs(z*other.z);
}

float Vector3::Normalise(void)
{
	float len = Math::Sqrt(x*x + y*y + z*z);

	if(len > 0.f)
	{
		float invLen = 1.f / len;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}

	return len;
}

Vector3 Vector3::CrossProduct(const Vector3& other) const
{
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vector3 Vector3::MidPoint(const Vector3& other) const
{
	return Vector3( (x*other.x)*0.5f,
					(y*other.y)*0.5f,
					(z*other.z)*0.5f);
}

void Vector3::MakeFloor(const Vector3& other)
{
	if(other.x < x) x = other.x;
	if(other.y < y) y = other.y;
	if(other.z < z) z = other.z;
}

void Vector3::MakeCeil(const Vector3& other)
{
	if(other.x > x) x = other.x;
	if(other.y > y) y = other.y;
	if(other.z > z) z = other.z;
}

Vector3 Vector3::Perpendicular(void) const
{
	static const float sqZero = (float)(1e-06 * 1e-06);

	Vector3 perp = this->CrossProduct(Vector3::UNIT_X);

	if(perp.SquaredLength() < sqZero)
	{
		perp = this->CrossProduct(Vector3::UNIT_Y);
	}
	perp.Normalise();

	return perp;
}

Radian Vector3::AngleBetween(const Vector3& other) const
{
	float lenProduct = Length() * other.Length();

	if(lenProduct < 1e-6f)
		lenProduct = 1e-6f;

	float f = DotProduct(other) / lenProduct;

	f = Math::Clamp(f, -1.0f, 1.0f);
	return Math::ACos(f);
}

/*Quaternion Vector3::GetRotationTo(const Vector3& other, const Vector3& fallbackAxis) const
{

}*/

bool Vector3::isZeroLength(void) const
{
	float sqlen = (x*x) + (y*y) + (z*z);
	return (sqlen < (1e-06 * 1e-06));
}

Vector3 Vector3::NormalisedCopy(void) const
{
	Vector3 ret = *this;
	ret.Normalise();
	return ret;
}

Vector3 Vector3::Reflect(const Vector3& normal) const
{
	return Vector3( *this - (normal * this->DotProduct(normal) * 2.f));
}

bool Vector3::DirectionEquals(const Vector3& other, const Radian& tolerance) const
{
	float dot = DotProduct(other);
	Radian angle = Math::ACos(dot);

	return Math::Abs(angle.valueRadians()) <= tolerance.valueRadians();
}

bool Vector3::isNaN(void) const
{
	return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z);
}

Vector3 Vector3::PrimaryAxis(void) const
{
	float absx = Math::Abs(x);
	float absy = Math::Abs(y);
	float absz = Math::Abs(z);

	if(absx > absy)
		if(absx > absz)
			return x > 0 ? Vector3::UNIT_X : Vector3::NEGATIVE_UNIT_X;
		else
			return z > 0 ? Vector3::UNIT_Z : Vector3::NEGATIVE_UNIT_Z;
	else
		if (absy > absz)
			return y > 0 ? Vector3::UNIT_Y : Vector3::NEGATIVE_UNIT_Y;
		else
			return z > 0 ? Vector3::UNIT_Z : Vector3::NEGATIVE_UNIT_Z;

}

float* Vector3::ptr(void)
{
	return &x;
}

const float* Vector3::ptr(void) const
{
	return &x;
}

float Vector3::operator[] (const size_t i) const
{
	assert(i<3);
	return *(&x+i);
}

float& Vector3::operator[] (const size_t i)
{
	assert(i<3);
	return *(&x+i);
}

bool Vector3::operator== (const Vector3& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::operator!= (const Vector3& other) const
{
	return (x != other.x || y != other.y || z != other.z);
}

bool Vector3::operator< (const Vector3& other) const
{
	if(x < other.x && y < other.y && z < other.z)
		return true;
	return false;
}

bool Vector3::operator> (const Vector3& other) const
{
	if(x > other.x && y > other.y && z > other.z)
		return true;
	return false;
}

Vector3& Vector3::operator= (const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3& Vector3::operator= (const Vector2& other)
{
	x = other.x;
	y = other.y;
	z = 0.0f;

	return *this;
}

Vector3& Vector3::operator= (const float scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;

	return *this;
}

const Vector3& Vector3::operator+ (void) const
{
	return *this;
}

Vector3 Vector3::operator- (void) const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+ (const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+ (const float scalar) const
{
	return Vector3(x+scalar, y+scalar, z+scalar);
}

Vector3 Vector3::operator- (const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator- (const float scalar) const
{
	return Vector3(x-scalar, y-scalar, z-scalar);
}

Vector3 Vector3::operator* (const Vector3& other) const
{
	return Vector3(x*other.x, y*other.y, z*other.z);
}

Vector3 Vector3::operator* (const float scalar) const
{
	return Vector3(x*scalar, y*scalar, z*scalar);
}

Vector3 Vector3::operator/ (const Vector3& other) const
{
	assert(other.x != 0.0f);
	assert(other.y != 0.0f);
	assert(other.z != 0.0f);
	return Vector3(x/other.x, y/other.y, z/other.z);
}

Vector3 Vector3::operator/ (const float scalar) const
{
	assert(scalar != 0.0f);
	return Vector3(x/scalar, y/scalar, z/scalar);
}

Vector3& Vector3::operator+= (const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3& Vector3::operator+= (const float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;

	return *this;
}

Vector3& Vector3::operator-= (const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3& Vector3::operator-= (const float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;

	return *this;
}

Vector3& Vector3::operator*= (const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3& Vector3::operator*= (const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator/= (const Vector3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

Vector3& Vector3::operator/= (const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

Vector3 operator+ (const float lhs, const Vector3& rhs)
{
	return Vector3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

Vector3 operator+ (const Vector3& lhs, const float rhs)
{
	return Vector3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

Vector3 operator- (const float lhs, const Vector3& rhs)
{
	return Vector3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

Vector3 operator- (const Vector3& lhs, const float rhs)
{
	return Vector3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

Vector3 operator* (const float lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vector3 operator/ (const float lhs, const Vector3& rhs)
{
	return Vector3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}