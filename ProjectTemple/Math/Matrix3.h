#ifndef __MATRIX3_H_
#define __MATRIX3_H_

#include "Math\Vector3.h"

namespace Engine
{
	class Matrix3
	{
	protected:
		float m[3][3];
	public:
		Matrix3(void){}
		explicit Matrix3(const float arr[3][3]);
		Matrix3(const Matrix3& other);
		Matrix3(float f00, float f01, float f02,
				float f10, float f11, float f12,
				float f20, float f21, float f22);
		
		void Swap(Matrix3& other);
		Vector3 GetColumn(size_t iCol) const;
		void SetColumn(size_t iCol, const Vector3& vec);
		void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		Matrix3 Transpose(void) const;
		bool Inverse(Matrix3& inv, float tolerance=1e-06) const;
		Matrix3 Inverse(float tolerance=1e-06) const;
		float Determinant(void) const;
		void SingularValueDecomposition(Matrix3& l, Matrix3& s, Matrix3& r) const;
		void SingularValueComposition(const Matrix3& l, const Matrix3& s, const Matrix3& r);
		void Orthonormalize(void);
		void QDUDecomposition(Matrix3& q, Vector3& d, Vector3& u) const;
		float SpectralNorm(void) const;
		void ToAngleAxis(Vector3& axis, Radian& angle) const;
		void ToAngleAxis(Vector3& axis, Degree& angle) const;
		void FromAngleAxis(const Vector3& axis, const Radian& rads);

		bool ToEulerAnglesXYZ(Radian& yaw, Radian& pitch, Radian& roll) const;
		bool ToEulerAnglesXZY(Radian& yaw, Radian& pitch, Radian& roll) const;
		bool ToEulerAnglesYXZ(Radian& yaw, Radian& pitch, Radian& roll) const;
		bool ToEulerAnglesYZX(Radian& yaw, Radian& pitch, Radian& roll) const;
		bool ToEulerAnglesZXY(Radian& yaw, Radian& pitch, Radian& roll) const;
		bool ToEulerAnglesZYX(Radian& yaw, Radian& pitch, Radian& roll) const;

		void FromEulerAnglesXYZ(const Radian& yaw, const Radian& pitch, const Radian& roll);
		void FromEulerAnglesXZY(const Radian& yaw, const Radian& pitch, const Radian& roll);
		void FromEulerAnglesYXZ(const Radian& yaw, const Radian& pitch, const Radian& roll);
		void FromEulerAnglesYZX(const Radian& yaw, const Radian& pitch, const Radian& roll);
		void FromEulerAnglesZXY(const Radian& yaw, const Radian& pitch, const Radian& roll);
		void FromEulerAnglesZYX(const Radian& yaw, const Radian& pitch, const Radian& roll);

		void EigenSolveSymmetric(float EigenValue[3], Vector3 EigenVector[3]) const;
		bool HasScale(void) const;
		static void TensorProduct(const Vector3& u, const Vector3& v, Matrix3& prod);

		Matrix3 operator- (void) const;

		float* operator[] (size_t iRow) const;
		Matrix3& operator= (const Matrix3& other);
		bool operator== (const Matrix3& other) const;
		bool operator!= (const Matrix3& other) const;
		Matrix3 operator+ (const Matrix3& other) const;
		Matrix3 operator- (const Matrix3& other) const;
		Matrix3 operator* (const Matrix3& other) const;
		Vector3 operator* (const Vector3& vec) const;
		Matrix3 operator* (const float scalar) const;

		friend Vector3 operator* (const Vector3& vec, const Matrix3& mat);
		friend Matrix3 operator* (float scalar, const Matrix3& mat);

		static const float EPSILON;
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;

	protected:
		void Tridiagonal(float diag[3], float subDiag[3]);
		bool QLAlgorithm(float diag[3], float subDiag[3]);

		static void Bidiagonalize(Matrix3& a, Matrix3& l, Matrix3& r);
		static void GolubKahanStep(Matrix3& a, Matrix3& l, Matrix3& r);
		static float MaxCubicRoot(float coeff[3]);

		static const float msSvdEpsilon;
		static const unsigned int msSvdMaxIterations;
	};
}

#endif //__MATRIX3_H_