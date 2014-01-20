#include <Math/Vector4.h>
#include <Math/Vector3.h>
#include <Math/Math.h>
#include <assert.h>
#include <algorithm>

using namespace Engine;

const Vector4 Vector4::ZERO = Vector4(0,0,0,0);

Vector4::Vector4(void) : x(0), y(0), z(0), w(0) {}
Vector4::Vector4(const float fx, const float fy, const float fz, const float fw) : x(fx), y(fy), z(fz), w(fw) {}
Vector4::Vector4(const float coord[4]) : x(coord[0]), y(coord[1]), z(coord[2]), w(coord[3]) {}
Vector4::Vector4(const int coord[4]) : x((float)coord[0]), y((float)coord[1]), z((float)coord[2]), w((float)coord[3]) {}
Vector4::Vector4(float* const r)  : x(r[0]), y(r[1]), z(r[2]), w(r[3]) {}
Vector4::Vector4(const float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
Vector4::Vector4(const Vector3& rhs, const float fw) : x(rhs.x), y(rhs.y), z(rhs.z), w(fw) {}

void Vector4::swap(Vector4 &other)
{
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(z, other.z);
	std::swap(w, other.w);
}

float Vector4::dotProduct(const Vector4& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

bool Vector4::isNaN(void) const
{
	return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z) || Math::isNaN(w);
}

float Vector4::operator[] (const size_t i) const
{
	assert (i < 4);

	return *(&x+i);
}

float& Vector4::operator[] (const size_t i)
{
	assert (i < 4);

	return *(&x+i);
}

float* Vector4::ptr(void)
{
	return &x;
}

const float* Vector4::ptr(void) const
{
	return &x;
}

bool Vector4::operator== (const Vector4& other) const
{
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

bool Vector4::operator!= (const Vector4& other) const
{
	return (x != other.x || y != other.y || z != other.z || w != other.w);
}

const Vector4& Vector4::operator+ (void) const
{
	return *this;
}

Vector4& Vector4::operator- (void) const
{
	return Vector4(-x,-y,-z,-w);
}

Vector4& Vector4::operator= (const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Vector4& Vector4::operator= (const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = 1.0f;

	return *this;
}

Vector4& Vector4::operator= (const float scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
	w = scalar;

	return *this;
}

Vector4 Vector4::operator+ (const Vector4& other) const
{
	return Vector4(
		x + other.x, 
		y + other.y, 
		z + other.z, 
		w + other.w);
}

Vector4 Vector4::operator+ (const float scalar) const
{
	return Vector4(
		x + scalar, 
		y + scalar, 
		z + scalar, 
		w + scalar);
}

Vector4 Vector4::operator- (const Vector4& other) const
{
	return Vector4(
		x - other.x, 
		y - other.y, 
		z - other.z, 
		w - other.w);
}

Vector4 Vector4::operator- (const float scalar) const
{
	return Vector4(
		x - scalar, 
		y - scalar, 
		z - scalar, 
		w - scalar);
}

Vector4 Vector4::operator* (const Vector4& other) const
{
	return Vector4(
		x * other.x, 
		y * other.y, 
		z * other.z, 
		w * other.w);
}

Vector4 Vector4::operator* (const float scalar) const
{
	return Vector4(
		x * scalar,
		y * scalar,
		z * scalar,
		w * scalar);
}

Vector4 Vector4::operator/ (const Vector4& other) const
{
	return Vector4(
		x / other.x,
		y / other.y,
		z / other.z,
		w / other.w);
}

Vector4 Vector4::operator/ (const float scalar) const
{
	assert(scalar != 0.0f);

	float inv = 1.0f / scalar;
	
	return Vector4(
		x * inv,
		y * inv,
		z * inv,
		w * inv);
}

Vector4& Vector4::operator+= (const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4& Vector4::operator+= (const float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;

	return *this;
}

Vector4& Vector4::operator-= (const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Vector4& Vector4::operator-= (const float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;

	return *this;
}

Vector4& Vector4::operator*= (const Vector4& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;

	return *this;
}

Vector4& Vector4::operator*= (const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

Vector4& Vector4::operator/= (const Vector4& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;

	return *this;
}

Vector4& Vector4::operator/= (const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

Vector4 operator+ (const float lhs, const Vector4& rhs)
{
	return Vector4(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z,
		lhs + rhs.w);
}

Vector4 operator+ (const Vector4& lhs, const float rhs)
{
	return Vector4(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs,
		lhs.w + rhs);
}

Vector4 operator- (const float lhs, const Vector4& rhs)
{
	return Vector4(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z,
		lhs - rhs.w);
}

Vector4 operator- (const Vector4& lhs, const float rhs)
{
	return Vector4(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs,
		lhs.w - rhs);
}

Vector4 operator* (const float lhs, const Vector4& rhs)
{
	return Vector4(
		lhs * rhs.x,
		lhs * rhs.y,
		lhs * rhs.z,
		lhs * rhs.w);
}

Vector4 operator/ (const float lhs, const Vector4 rhs)
{
	return Vector4(
		lhs / rhs.x,
		lhs / rhs.y,
		lhs / rhs.z, 
		lhs / rhs.w);
}