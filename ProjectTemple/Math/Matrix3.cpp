#include <Math\Matrix3.h>
#include <Math\Vector3.h>
#include <Math\Math.h>
#include <memory>
#include <assert.h>

using namespace Engine;

const float Matrix3::EPSILON = 1e-06f;
const Matrix3 Matrix3::ZERO(0,0,0,0,0,0,0,0,0);
const Matrix3 Matrix3::IDENTITY(1,0,0,0,1,0,0,0,1);
const float Matrix3::msSvdEpsilon = 1e-04f;
const unsigned int Matrix3::msSvdMaxIterations = 32;

Matrix3::Matrix3(const float arr[3][3])
{
	memcpy(m,arr,9*sizeof(float));
}

Matrix3::Matrix3(const Matrix3& other)
{
	memcpy(m,other.m,9*sizeof(float));
}

Matrix3::Matrix3(float f00, float f01, float f02,
				 float f10, float f11, float f12,
				 float f20, float f21, float f22)
{
	m[0][0] = f00;
	m[0][1] = f01;
	m[0][2] = f02;
	m[1][0] = f10;
	m[1][1] = f11;
	m[1][2] = f12;
	m[2][0] = f20;
	m[2][1] = f21;
	m[2][2] = f22;
}

void Matrix3::Swap(Matrix3& other)
{
	std::swap(m[0][0], other.m[0][0]);
	std::swap(m[0][1], other.m[0][1]);
	std::swap(m[0][2], other.m[0][2]);
	std::swap(m[1][0], other.m[1][0]);
	std::swap(m[1][1], other.m[1][1]);
	std::swap(m[1][2], other.m[1][2]);
	std::swap(m[2][0], other.m[2][0]);
	std::swap(m[2][1], other.m[2][1]);
	std::swap(m[2][2], other.m[2][2]);
}

Vector3 Matrix3::GetColumn(size_t iCol) const
{
	assert(iCol < 3);
	return Vector3(m[0][iCol], m[1][iCol], m[2][iCol]);
}

void Matrix3::SetColumn(size_t iCol, const Vector3& vec)
{
	assert(iCol < 3);
	m[0][iCol] = vec.x;
	m[1][iCol] = vec.y;
	m[2][iCol] = vec.z;
}

void Matrix3::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
	SetColumn(0,xAxis);
	SetColumn(1,yAxis);
	SetColumn(2,zAxis);
}

Matrix3 Matrix3::Transpose(void) const
{
	Matrix3 trans;
	for(size_t iRow = 0; iRow < 3; iRow++)
	{
		for(size_t iCol = 0; iCol < 3; iCol++)
		{
			trans[iRow][iCol] = m[iCol][iRow];
		}
	}
	return trans;
}

bool Matrix3::Inverse(Matrix3& inv, float tolerance) const
{
	inv[0][0] = m[1][1]*m[2][2] - m[1][2]*m[2][1];
	inv[0][1] = m[0][2]*m[2][1] - m[0][1]*m[2][2];
	inv[0][2] = m[0][1]*m[1][2] - m[0][2]*m[1][1];
	inv[1][0] = m[1][2]*m[2][0] - m[1][0]*m[2][2];
	inv[1][1] = m[0][0]*m[2][2] - m[0][2]*m[2][0];
	inv[1][2] = m[0][2]*m[1][0] - m[0][0]*m[1][2];
	inv[2][0] = m[1][0]*m[2][1] - m[1][1]*m[2][0];
	inv[2][1] = m[0][1]*m[2][0] - m[0][0]*m[2][1];
	inv[2][2] = m[0][0]*m[1][1] - m[0][1]*m[1][0];

	float det = m[0][0]*inv[0][0] +
				m[0][1]*inv[1][0] +
				m[0][2]*inv[2][0];

	if(Math::Abs(det) <= tolerance)
		return false;

	float invDet = 1.0f/det;
	for(size_t iRow = 0; iRow < 3; iRow++)
	{
		for(size_t iCol = 0; iCol < 3; iCol++)
		{
			inv[iRow][iCol] *= invDet;
		}
	}

	return true;
}

Matrix3 Matrix3::Inverse(float tolerance) const
{
	Matrix3 inv = Matrix3::ZERO;
	Inverse(inv, tolerance);
	return inv;
}

float Matrix3::Determinant(void) const
{
	float f00 = m[1][1]*m[2][2] - m[1][2]*m[2][1];
	float f10 = m[1][2]*m[2][0] - m[1][0]*m[2][2];
	float f20 = m[1][0]*m[2][1] - m[1][1]*m[2][0];

	float det = m[0][0]*f00 +
				m[0][1]*f10 +
				m[0][2]*f20;

	return det;
}

void Matrix3::Bidiagonalize(Matrix3& a, Matrix3& l, Matrix3& r)
{
	float v[3], w[3];
	float len, sign, t1, t1Inv, t2;
	bool identity;

	//map first column to (*,0,0)
	len = Math::Sqrt(a[0][0]*a[0][0] + a[1][0]*a[1][0] + a[2][0]*a[2][0]);
	if(len > 0.0)
	{
		sign = (a[0][0] > 0.0f ? 1.0f : -1.0f);
		t1 = a[0][0] + sign*len;
		t1Inv = 1.0f/t1;
		v[1] = a[1][0]*t1Inv;
		v[2] = a[2][0]*t1Inv;

		t2 = -2.0f/(1.0f+v[1]*v[1]+v[2]*v[2]);
		w[0] = t2*(a[0][0]+a[1][0]*v[1]*a[2][0]*v[2]);
		w[1] = t2*(a[0][1]+a[1][1]*v[1]*a[2][1]*v[2]);
		w[2] = t2*(a[0][2]+a[1][2]*v[1]*a[2][2]*v[2]);

		a[0][0] += w[0];
		a[0][1] += w[1];
		a[0][2] += w[2];
		a[1][1] += v[1]*w[1];
		a[1][2] += v[1]*w[2];
		a[2][1] += v[2]*w[1];
		a[2][2] += v[2]*w[2];

		l[0][0] = 1.0f+t2;
		l[0][1] = l[1][0] = t2*v[1];
		l[0][2] = l[2][0] = t2*v[2];
		l[1][1] = 1.0f+t2*v[1]*v[1];
		l[1][2] = l[2][1] = t2*v[1]*v[2];
		l[2][2] = 1.0f+t2*v[2]*v[2];
		identity = false;
	}
	else
	{
		l = Matrix3::IDENTITY;
		identity = true;
	}

	//map first row to (*,*,0)
	len = Math::Sqrt(a[0][1]*a[0][1]+a[0][2]*a[0][2]);
	if(len > 0.0)
	{
		sign = (a[0][1] > 0.0f ? 1.0f : -1.0f);
		t1 = a[0][1] + sign*len;
		v[2] = a[0][2]/t1;

		t2 = -2.0f/(1.0f+v[2]*v[2]);
		w[0] = t2*(a[0][1]+a[0][2]*v[2]);
		w[1] = t2*(a[1][1]+a[1][2]*v[2]);
		w[2] = t2*(a[2][1]+a[2][2]*v[2]);

		a[0][1] += w[0];
		a[1][1] += w[1];
		a[1][2] += w[1]*v[2];
		a[2][1] += w[2];
		a[2][2] += w[2]*v[2];

		r[0][0] = 1.0;
		r[0][1] = r[1][0] = 0.0;
		r[0][2] = r[2][0] = 0.0;
		r[1][1] = 1.0f+t2;
		r[1][2] = r[2][1] = t2*v[2];
		r[2][2] = 1.0f+t2*v[2]*v[2];
	}
	else
	{
		r = Matrix3::IDENTITY;
	}

	//map second column to (*,*,0)
	len = Math::Sqrt(a[1][1]*a[1][1]+a[2][1]*a[2][1]);
	if(len > 0.0)
	{
		sign = (a[1][1] > 0.0f ? 1.0f : -1.0f);
		t1 = a[1][1] + sign*len;
		v[2] = a[2][1]/t1;

		t2 = -2.0f/(1.0f+v[2]*v[2]);
		w[1] = t2*(a[1][1]+a[2][1]*v[2]);
		w[2] = t2*(a[1][2]+a[2][2]*v[2]);
		a[1][1] += w[1];
		a[1][2] += w[2];
		a[2][2] += v[2]*w[2];

		float fA = 1.0f+t2;
		float fB = t2*v[2];
		float fC = 1.0f+fB*v[2];

		if(identity)
		{
			l[0][0] = 1.0;
			l[0][1] = l[1][0] = 0.0;
			l[0][2] = l[2][0] = 0.0;
			l[1][1] = fA;
			l[1][2] = l[2][1] = fB;
			l[2][2] = fC;
		}
		else
		{
			for(int iRow = 0; iRow < 3; iRow++)
			{
				float tmp0 = l[iRow][1];
				float tmp1 = l[iRow][2];
				l[iRow][1] = fA*tmp0+fB*tmp1;
				l[iRow][2] = fB*tmp0+fC*tmp1;
			}
		}
	}
}

void Matrix3::GolubKahanStep(Matrix3& a, Matrix3& l, Matrix3& r)
{
	float t11 = a[0][1]*a[0][1]+a[1][1]*a[1][1];
	float t22 = a[1][2]*a[1][2]+a[2][2]*a[2][2];
	float t12 = a[1][1]*a[1][2];
	float trace = t11+t22;
	float diff = t11-t22;
	float discr = Math::Sqrt(diff*diff+4.0f*t12*t12);
	float root1 = 0.5f*(trace+discr);
	float root2 = 0.5f*(trace-discr);

	// adjust right
	float y = a[0][0] - (Math::Abs(root1-t22) <= Math::Abs(root2-t22) ? root1 : root2);
	float z = a[0][1];
	float invLen = 1.0f/(Math::Sqrt(y*y+z*z));
	float sin = z*invLen;
	float cos = -y*invLen;

	float tmp0 = a[0][0];
	float tmp1 = a[0][1];
	a[0][0] = cos*tmp0-sin*tmp1;
	a[0][1] = sin*tmp0+cos*tmp1;
	a[1][0] = -sin*a[1][1];
	a[1][1] *= cos;

	size_t iRow;
	for (iRow = 0; iRow < 3; iRow++)
	{
		tmp0 = r[0][iRow];
		tmp1 = r[1][iRow];
		r[0][iRow] = cos*tmp0-sin*tmp1;
		r[1][iRow] = sin*tmp0+cos*tmp1;
	}

	// adjust left
	y = a[0][0];
	z = a[1][0];
	invLen = 1.0f/(Math::Sqrt(y*y+z*z));
	sin = z*invLen;
	cos = -y*invLen;

	a[0][0] = cos*a[0][0]-sin*a[1][0];
	tmp0 = a[0][1];
	tmp1 = a[1][1];
	a[0][1] = cos*tmp0-sin*tmp1;
	a[1][1] = sin*tmp0+cos*tmp1;
	a[0][2] = -sin*a[1][2];
	a[1][2] *= cos;

	size_t iCol;
	for (iCol = 0; iCol < 3; iCol++)
	{
		tmp0 = l[iCol][0];
		tmp1 = l[iCol][1];
		l[iCol][0] = cos*tmp0-sin*tmp1;
		l[iCol][1] = sin*tmp0+cos*tmp1;
	}

	// adjust right
	y = a[0][1];
	z = a[0][2];
	invLen = 1.0f/(Math::Sqrt(y*y+z*z));
	sin = z*invLen;
	cos = -y*invLen;

	a[0][1] = cos*a[0][1]-sin*a[0][2];
	tmp0 = a[1][1];
	tmp1 = a[1][2];
	a[1][1] = cos*tmp0-sin*tmp1;
	a[1][2] = sin*tmp0+cos*tmp1;
	a[2][1] = -sin*a[2][2];
	a[2][2] *= cos;

	for (iRow = 0; iRow < 3; iRow++)
	{
		tmp0 = r[1][iRow];
		tmp1 = r[2][iRow];
		r[1][iRow] = cos*tmp0-sin*tmp1;
		r[2][iRow] = sin*tmp0+cos*tmp1;
	}

	// adjust left
	y = a[1][1];
	z = a[2][1];
	invLen = 1.0f/(Math::Sqrt(y*y+z*z));
	sin = z*invLen;
	cos = -y*invLen;

	a[1][1] = cos*a[1][1]-sin*a[2][1];
	tmp0 = a[1][2];
	tmp1 = a[2][2];
	a[1][2] = cos*tmp0-sin*tmp1;
	a[2][2] = sin*tmp0+cos*tmp1;

	for (iCol = 0; iCol < 3; iCol++)
	{
		tmp0 = l[iCol][1];
		tmp1 = l[iCol][2];
		l[iCol][1] = cos*tmp0-sin*tmp1;
		l[iCol][2] = sin*tmp0+cos*tmp1;
	}
}

/*float Matrix3::MaxCubicRoot(float coeff[3])
{

}*/