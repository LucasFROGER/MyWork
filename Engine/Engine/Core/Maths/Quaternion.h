#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "Vector\Vec3.h"

namespace engine
{
	namespace core
	{
		namespace maths
		{
			class Mat4;

			struct Quaternion
			{
#pragma region Variables
				float m_w;
				float m_x;
				float m_y;
				float m_z;
#pragma endregion

#pragma region Constructors/destructor
				Quaternion();
				Quaternion(const Quaternion& lQuaternion) = default;
				Quaternion(Quaternion&& rQuaternion) = default;
				Quaternion(float scalar);
				Quaternion(float w, float x, float y, float z);
				Quaternion(float scalar, const Vec3& vector);
				~Quaternion() = default;
#pragma endregion

#pragma region Shorthands
				// Generates a Quaternion : ( 1 ; 0 ; 0 ; 0 ).
				static Quaternion Identity();
#pragma endregion

#pragma region Tools
				static Quaternion Euler(const Vec3& eulerAngles);
				static Quaternion Euler2(const Vec3& eulerAngles);
				static Quaternion Lerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio);
				static Quaternion NLerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio);
				static Quaternion Slerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio);
				//static Quaternion Slerp1(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio); // slower
#pragma endregion

#pragma region Operations
				bool Normalize();
				bool Reverse();
				Quaternion GetNormalized(bool* succed = nullptr) const;
				float GetModulus() const;
				float GetModulusSQ() const;
				float GetScalarPart() const;
				Vec3 GetVectorPart() const;
				float GetAngle() const;
				Vec3 GetEulerAngles() const;
				Vec3 GetEulerAngles2() const;
				Vec3 GetEulerAngles3() const;
				Vec3 NormalizeAngles(Vec3 angles) const;
				float NormalizeAngle(float angle) const;
				Vec3 GetAxis() const;
				Quaternion GetConjugate() const;
				Quaternion GetInverse(bool* succed = nullptr) const;
				Mat4 GetRotationMatrix() const;
				void RotateVertex(Vec3& vertex) const;
				Vec3 GetRotatedVertex(const Vec3& vertex) const;
				float DotProduct(const Quaternion& quat) const;
#pragma endregion

#pragma region Operators
				Quaternion&	operator=	(const Quaternion&	quaternion) = default;
				Quaternion&	operator=	(Quaternion&&		quaternion) = default;
				Quaternion&	operator=	(float				scalar);
				Quaternion	operator+	(float				scalar)	const;
				Quaternion	operator+	(const Quaternion&	quaternion)	const;
				Quaternion&	operator+=	(float				scalar);
				Quaternion&	operator+=	(const Quaternion&	quaternion);
				Quaternion&	operator-	();
				Quaternion	operator-	(float				scalar)	const;
				Quaternion	operator-	(const Quaternion&	quaternion)	const;
				Quaternion&	operator-=	(float				scalar);
				Quaternion&	operator-=	(const Quaternion&	quaternion);
				Quaternion	operator*	(float				scalar)	const;
				Quaternion	operator*	(const Quaternion&	quaternion)	const;
				Quaternion&	operator*=	(float				scalar);
				Quaternion&	operator*=	(const Quaternion&	quaternion);
				Quaternion	operator/	(float				scalar)	const;
				Quaternion	operator/	(const Quaternion&	quaternion)	const;
				Quaternion&	operator/=	(float				scalar);
				Quaternion&	operator/=	(const Quaternion&	quaternion);
				bool		operator==	(const Quaternion&	quaternion)	const;
				bool		operator!=	(const Quaternion&	quaternion)	const;
				// /!\ Should be used with caution!
				// Returns the associated component.
				float&		operator[]	(int				index);
				// (read only)
				float		operator[]	(int				index)	const;
#pragma endregion
			};

#pragma region External operators
			std::ostream& operator<<(std::ostream&, const Quaternion&);
			Quaternion operator+(float scalar, const Quaternion&);
			Quaternion operator-(float scalar, const Quaternion&);
			Quaternion operator*(float scalar, const Quaternion&);
			Quaternion operator/(float scalar, const Quaternion&);
#pragma endregion
		}
	}
}
#endif