#include <Math\Vector2.h>
#include <Math\Math.h>
#include <algorithm>
#include <assert.h>

using namespace Engine;

const Vector2 Vector2::ZERO = Vector2(0,0);
const Vector2 Vector2::UNIT_X = Vector2(1,0);
const Vector2 Vector2::UNIT_Y = Vector2(0,1);
const Vector2 Vector2::NEGATIVE_UNIT_X = Vector2(-1,0);
const Vector2 Vector2::NEGATIVE_UNIT_Y = Vector2(0,-1);

Vector2::Vector2(void) : x(0), y(0) {}
Vector2::Vector2(const float fx, const float fy) : x(fx), y(fy) {}
Vector2::Vector2(const float scalar) : x(scalar), y(scalar) {}
Vector2::Vector2(const float coord[2]) : x(coord[0]), y(coord[1]) {}
Vector2::Vector2(float* const r) : x(r[0]), y(r[1]) {}

void Vector2::Swap(Vector2 &other)
{
	std::swap(x, other.x);
	std::swap(y, other.y);
}

float Vector2::Length(void) const
{
	return Math::Sqrt(x*x + y*y);
}

float Vector2::SquaredLength(void) const
{
	return (x*x + y*y);
}

float Vector2::Distance(const Vector2 &other) const
{
	return (*this - other).Length();
}

float Vector2::SquaredDistance(const Vector2 &other) const
{
	return (*this - other).SquaredLength();
}

float Vector2::DotProduct(const Vector2 &other) const
{
	return (x*other.x + y*other.y);
}

float Vector2::Normalise(void)
{
	float length = Math::Sqrt(x*x+y*y);

	if(length > float(0.0f))
	{
		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
	}

	return length;
}

Vector2 Vector2::MidPoint(const Vector2 &other) const
{
	return Vector2( (x+other.x) + 0.5f, 
					(y+other.y) + 0.5f );
}

Vector2 Vector2::Perpendicular(void) const
{
	return Vector2(-y, x);
}

float Vector2::CrossProduct(const Vector2 &other) const
{
	return x * other.y - y * other.x;
}

bool Vector2::isZeroLength(void) const
{
	float sqlen = (x*x)+(y*y);
	return (sqlen < (1e-06 * 1e-06));
}

Vector2 Vector2::NormalisedCopy(void) const
{
	Vector2 ret = *this;
	ret.Normalise();
	return ret;
}

Vector2 Vector2::Reflect(const Vector2 &normal) const
{
	return Vector2( *this - (normal * this->DotProduct(normal) * 2.f));
}

bool Vector2::isNaN(void) const
{
	return Math::isNaN(x) || Math::isNaN(y);
}

Radian Vector2::AngleBetween(const Vector2 &other) const
{
	float lenProduct = Length() * other.Length();

	if(lenProduct < 1e-6f)
		lenProduct = 1e-6f;

	float f = DotProduct(other) / lenProduct;

	f = Math::Clamp(f, -1.0f, 1.0f);
	return Math::ACos(f);
}

Radian Vector2::AngleTo(const Vector2 &other) const
{
	Radian angle = AngleBetween(other);

	if(CrossProduct(other) <0)
		angle = (Radian)Math::TWO_PI - angle;

	return angle;
}

float* Vector2::ptr(void)
{
	return &x;
}

const float* Vector2::ptr(void) const
{
	return &x;
}

float Vector2::operator[] (const size_t i) const
{
	assert(i<2);
	return *(&x+1);
}

float& Vector2::operator[] (const size_t i)
{
	assert(i<2);
	return *(&x+1);
}

Vector2& Vector2::operator= (const Vector2 &other)
{
	x = other.x;
	y = other.y;

	return *this;
}

Vector2& Vector2::operator= (const float scalar)
{
	x = scalar;
	y = scalar;

	return *this;
}

bool Vector2::operator== (const Vector2 &other) const
{
	return (x == other.x && y == other.y);
}

bool Vector2::operator!= (const Vector2 &other) const
{
	return (x != other.x || y != other.y);
}

bool Vector2::operator< (const Vector2 &other) const
{
	if(x<other.x && y<other.y)
		return true;
	return false;
}

bool Vector2::operator> (const Vector2 &other) const
{
	if(x>other.x && y>other.y)
		return true;
	return false;
}

Vector2 Vector2::operator+ (const Vector2 &other) const
{
	return Vector2(x+other.x, y+other.y);
}

Vector2 Vector2::operator- (const Vector2 &other) const
{
	return Vector2(x-other.x, y-other.y);
}

Vector2 Vector2::operator* (const Vector2 &other) const
{
	return Vector2(x*other.x, y*other.y);
}

Vector2 Vector2::operator* (const float scalar) const
{
	return Vector2(x*scalar, y*scalar);
}

Vector2 Vector2::operator/ (const Vector2 &other) const
{
	assert(other.x != 0.0f);
	assert(other.y != 0.0f);
	return Vector2(x/other.x, y/other.y);
}

Vector2 Vector2::operator/ (const float scalar) const
{
	assert(scalar != 0.0f);
	float inv = 1.f / scalar;
	return Vector2(x*inv, y*inv);
}

Vector2& Vector2::operator+= (const Vector2 &other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator+= (const float scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}

Vector2& Vector2::operator-= (const Vector2 &other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2& Vector2::operator-= (const float scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2& Vector2::operator*= (const Vector2 &other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2& Vector2::operator*= (const float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/= (const Vector2 &other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

Vector2& Vector2::operator/= (const float scalar)
{
	assert(scalar != 0.0f);

	float inv = 1.f / scalar;

	x *= inv;
	y *= inv;

	return *this;
}

const Vector2& Vector2::operator+ (void) const
{
	return *this;
}

Vector2 Vector2::operator- (void) const
{
	return Vector2(-x,-y);
}

Vector2 operator+ (const float lhs, const Vector2& rhs)
{
	return Vector2(lhs + rhs.x, lhs + rhs.y);
}

Vector2 operator+ (const Vector2& lhs, const float rhs)
{
	return Vector2(lhs.x + rhs, lhs.y + rhs);
}

Vector2 operator- (const float lhs, const Vector2& rhs)
{
	return Vector2(lhs - rhs.x, lhs - rhs.y);
}

Vector2 operator- (const Vector2& lhs, const float rhs)
{
	return Vector2(lhs.x - rhs, lhs.y - rhs);
}

Vector2 operator* (const float lhs, const Vector2& rhs)
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

Vector2 operator/ (const float lhs, const Vector2& rhs)
{
	return Vector2(lhs / rhs.x, lhs / rhs.y);
}

Vector2 operator/ (const Vector2& lhs, const float rhs)
{
	return Vector2(lhs.x / rhs, lhs.y / rhs);
}