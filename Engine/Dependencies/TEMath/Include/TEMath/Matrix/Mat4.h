#ifndef _MAT4_H_
#define _MAT4_H_

#include "../Vector/Vec4.h"
#include "../EAxis.h"

namespace temath
{
	class Mat4
	{
	public:
		#pragma region Variables
		float m_matrix[4][4];
		#pragma endregion

		#pragma region Shorthands
		// Generates a matrix full of 0
		static Mat4 Zero();
		// Generates an identity matrix
		static Mat4 Identity();
		#pragma endregion

		#pragma region Constructors/destructor
		Mat4();
		Mat4(const Mat4& other) = default;
		Mat4(Mat4&& other) = default;
		Mat4(float aa, float ab, float ac, float ad,
			float ba, float bb, float bc, float bd,
			float ca, float cb, float cc, float cd,
			float da, float db, float dc, float dd);
		Mat4(float matrix[4][4]);
		~Mat4() = default;
		#pragma endregion

		#pragma region Tools
		static Mat4 CreateTranslationMatrix(const Vec4& translation);
		static Mat4 CreateRotationMatrix(EAxis axis, float angle);
		template<typename... Arguments>
		static Mat4 CreateRotationMatrix(EAxis axis, float angle, Arguments... rotations);
		static Mat4 CreateScaleMatrix(const Vec4& scale);

		// Sets all values to 0
		void Clear();
		// Changes the matrix into a unitary matrix
		void Init();
		void Transpose();
		Mat4 GetTranspose() const;
		bool IsOrthogonal() const;
		float GetDeterminant() const;
		bool Inverse();
		Mat4 GetInverse(bool* succed = NULL) const;
		bool GetInverseByRef(Mat4& out) const;
		// Uses 'out' as a buffer (faster)
		bool GetInverseByRefUsingParameter(Mat4& out) const;
		#pragma endregion

		#pragma region Operators
		Mat4& operator=(const Mat4& mat) = default;
		Mat4& operator=(Mat4&& mat) = default;
		Mat4 operator+(const Mat4& mat) const;
		Mat4& operator+=(const Mat4& mat);
		Mat4 operator-() const;
		Mat4 operator-(const Mat4& mat) const;
		Mat4& operator-=(const Mat4& mat);
		Mat4 operator*(float scalar) const;
		Mat4 operator*(const Mat4& mat) const;
		Mat4& operator*=(float scalar);
		Mat4& operator*=(const Mat4& mat);
		Vec4 operator*(const Vec4& vec) const;
		bool operator==(const Mat4& mat) const;
		bool operator!=(const Mat4& mat) const;
		// /!\ Should be used with caution!
		// Returns the associated component.
		float* operator[](int index);
		// (read only)
		const float* operator[](int index) const;
		#pragma endregion

	private:
		template<typename... Arguments>
		static Mat4 CreateRotationMatrix(Arguments... invalidArgs);
	};

	#pragma region External operators
	std::ostream& operator<<(std::ostream& stream, const Mat4& mat);
	Mat4 operator*(float scalar, const Mat4& mat);
	#pragma endregion
}

template<typename... Arguments>
inline temath::Mat4 temath::Mat4::CreateRotationMatrix(Arguments... invalidArgs)
{
	std::cout << "Invalid argument(s)" << std::endl;

	return Mat4();
}

template<typename... Arguments>
inline temath::Mat4 temath::Mat4::CreateRotationMatrix(EAxis axis, float angle, Arguments... rotations)
{
	float angleInRadian{ angle * DEG_TO_RAD_f };
	float c{ cosf(angleInRadian) };
	float s{ sinf(angleInRadian) };

	switch (axis)
	{
	case EAxis::X:
		return Mat4(
			1.f, 0.f, 0.f, 0.f,
			0.f, c, -s, 0.f,
			0.f, s, c, 0.f,
			0.f, 0.f, 0.f, 1.f
		) * CreateRotationMatrix(rotations...);
		break;
	case EAxis::Y:
		return Mat4(
			c, 0.f, s, 0.f,
			0.f, 1.f, 0.f, 0.f,
			-s, 0.f, c, 0.f,
			0.f, 0.f, 0.f, 1.f
		) * CreateRotationMatrix(rotations...);
		break;
	case EAxis::Z:
		return Mat4(
			c, -s, 0.f, 0.f,
			s, c, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		) * CreateRotationMatrix(rotations...);
		break;
	default:
		return Mat4();
		break;
	}
}

#endif
