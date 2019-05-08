#ifndef _VEC2_H_
#define _VEC2_H_

#include <iostream>

namespace engine
{
	namespace core
	{
		namespace maths
		{
			struct Vec3;
			struct Vec4;

			struct Vec2
			{
#pragma region Variables
				float m_x;
				float m_y;
#pragma endregion

#pragma region Constructors/destructor
				Vec2();
				Vec2(const Vec2& lVec2) = default;
				Vec2(Vec2&& rVec2) = default;
				Vec2(float x, float y);
				// z component is lost.
				Vec2(const Vec3& lVec3);
				// z and w components are lost.
				Vec2(const Vec4& lVec4);
				~Vec2() = default;
#pragma endregion

#pragma region Shorthands
				// Generates a Vec2 : ( 0 ; 0 ).
				static Vec2 Zero();
				// Generates a Vec2 : ( -1 ; 0 ).
				static Vec2 Left();
				// Generates a Vec2 : ( 1 ; 0 ).
				static Vec2 Right();
				// Generates a Vec2 : ( 0 ; -1 ).
				static Vec2 Down();
				// Generates a Vec2 : ( 0 ; 1 ).
				static Vec2 Up();
				// Generates a Vec2 : ( 1 ; 1 ).
				static Vec2 One();
#pragma endregion

#pragma region Tools
				// Returns a Vec2 between firstVec and secondVec.
				// The ratio is clamped to the range[0, 1].
				// If the ratio is 0, the Vec2 returned is equal to firstVec.
				// If the ratio is 1, the Vec2 returned is equal to secondVec.
				static Vec2 Lerp(const Vec2& firstVec, const Vec2& secondVec, float ratio);
				static Vec2 NLerp(const Vec2& firstVec, const Vec2& secondVec, float ratio);

				// Returns the angle in radians between the two Vec2.
				static float GetAngle(const Vec2& firstVec, const Vec2& secondVec);
				// Returns the angle in degrees between the two Vec2.
				static float GetAngleInDegrees(const Vec2& firstVec, const Vec2& secondVec);

				// Returns the Vec2 with the smallest magnitude.
				static Vec2& Shortest(Vec2& firstVec, Vec2& secondVec);
				// Returns the const Vec2 with the smallest magnitude.
				static const Vec2& Shortest(const Vec2& firstVec, const Vec2& secondVec);

				// Returns the Vec2 with the biggest magnitude.
				static Vec2& Longest(Vec2& firstVec, Vec2& secondVec);
				// Returns the const Vec2 with the biggest magnitude.
				static const Vec2& Longest(const Vec2& firstVec, const Vec2& secondVec);

				// Returns a Vec2 with the smallest components.
				static Vec2 Min(const Vec2& firstVec, const Vec2& secondVec);
				// Returns a Vec2 with the biggest components.
				static Vec2 Max(const Vec2& firstVec, const Vec2& secondVec);

				// Returns the distance between two vertices.
				static float Distance(const Vec2& firstVertex, const Vec2& secondVertex);
				// Returns the distance squared between two vertices.
				static float DistanceSQ(const Vec2& firstVertex, const Vec2& secondVertex);
#pragma endregion

#pragma region Operations
				void Normalize();
				void ReverseValues();
				Vec2 GetNormalized() const;
				float GetMagnitude() const;
				float GetMagnitudeSQ() const;
				Vec2 GetInverseValues() const;
				// Changes the magnitude of the Vec2.
				void SetMagnitude(float magnitude);
				float DotProduct(const Vec2&) const;
#pragma endregion

#pragma region Operators
				Vec2& operator=(const Vec2&) = default;
				Vec2& operator=(Vec2&&) = default;
				Vec2 operator+(const Vec2&) const;
				Vec2& operator+=(const Vec2&);
				Vec2 operator-() const;
				Vec2 operator-(const Vec2&) const;
				Vec2& operator-=(const Vec2&);
				Vec2 operator*(float) const;
				Vec2& operator*=(float);
				Vec2 operator/(float) const;
				Vec2& operator/=(float);
				bool operator==(const Vec2&) const;
				bool operator!=(const Vec2&) const;
				// /!\ Should be used with caution!
				// Returns the associated component.
				float& operator[](int index);
				// (read only)
				float operator[](int index) const;
#pragma endregion
			};

			std::ostream& operator<<(std::ostream&, const Vec2&);
			Vec2 operator*(float, const Vec2&);
		}
	}
}

#endif