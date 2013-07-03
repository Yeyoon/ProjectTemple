#include <Math\Vector4.h>
#include <algorithm>

using namespace Engine;

const Vector4 Vector4::ZERO = Vector4(0,0,0,0);

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