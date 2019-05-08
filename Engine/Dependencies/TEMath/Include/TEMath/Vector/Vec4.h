#pragma once
#ifndef __CORE__MATHS__VEC4_H__
#define __CORE__MATHS__VEC4_H__

#include "Vec3.h"

namespace temath
{
	struct Vec4
	{
		#pragma region Variables
		float m_x;
		float m_y;
		float m_z;
		float m_w;
		#pragma endregion

		#pragma region Constructors/destructor
		Vec4();
		Vec4(const Vec4& lVec4)	= default;
		Vec4(Vec4&& rVec4)		= default;
		Vec4(float x, float y, float z, float w = 1.f);
		Vec4(const Vec2& lVec2, float z, float w = 1.f);
		Vec4(const Vec3& lVec3, float w = 1.f);
		~Vec4()					= default;
		#pragma endregion

		#pragma region Shorthands
		// Generates a Vec4 : ( 0 ; 0 ; 0 ; 1 ).
		static Vec4 Zero();
		// Generates a Vec4 : ( -1 ; 0 ; 0 ; 1 ).
		static Vec4 Left();
		// Generates a Vec4 : ( 1 ; 0 ; 0 ; 1 ).
		static Vec4 Right();
		// Generates a Vec4 : ( 0 ; -1 ; 0 ; 1 ).
		static Vec4 Down();
		// Generates a Vec4 : ( 0 ; 1 ; 0 ; 1 ).
		static Vec4 Up();
		// Generates a Vec4 : ( 0 ; 0 ; -1 ; 1 ).
		static Vec4 Back();
		// Generates a Vec4 : ( 0 ; 0 ; 1 ; 1 ).
		static Vec4 Forward();
		// Generates a Vec4 : ( 1 ; 1 ; 1 ; 1 ).
		static Vec4 One();
		#pragma endregion

		#pragma region Tools
		// Returns a Vec4 between firstVec and secondVec.
		// The ratio is clamped to the range[0, 1].
		// If the ratio is 0, the Vec4 returned is equal to firstVec.
		// If the ratio is 1, the Vec4 returned is equal to secondVec.
		static Vec4 Lerp(const Vec4& firstVec, const Vec4& secondVec, float ratio);
		static Vec4 NLerp(const Vec4& firstVec, const Vec4& secondVec, float ratio);

		// Returns the angle in radians between the two Vec4.
		static float GetAngle(const Vec4& firstVec, const Vec4& secondVec);
		// Returns the angle in degrees between the two Vec4.
		static float GetAngleInDegrees(const Vec4& firstVec, const Vec4& secondVec);

		// Returns the Vec4 with the smallest magnitude.
		static Vec4& Shortest(Vec4& firstVec, Vec4& secondVec);
		// Returns the const Vec4 with the smallest magnitude.
		static const Vec4& Shortest(const Vec4& firstVec, const Vec4& secondVec);

		// Returns the Vec4 with the biggest magnitude.
		static Vec4& Longest(Vec4& firstVec, Vec4& secondVec);
		// Returns the const Vec4 with the biggest magnitude.
		static const Vec4& Longest(const Vec4& firstVec, const Vec4& secondVec);

		// Returns a Vec4 with the smallest components.
		static Vec4 Min(const Vec4& firstVec, const Vec4& secondVec);
		// Returns a Vec4 with the biggest components.
		static Vec4 Max(const Vec4& firstVec, const Vec4& secondVec);

		// Returns the distance between two vertices.
		static float Distance(const Vec4& firstVertex, const Vec4& secondVertex);
		// Returns the distance squared between two vertices.
		static float DistanceSQ(const Vec4& firstVertex, const Vec4& secondVertex);

		// Returns a Vec2 made from this Vec4.
		// z and w components are lost.
		Vec2 ToVec2() const;
		// Returns a Vec3 made from this Vec4.
		// w component is lost.
		Vec3 ToVec3() const;
		#pragma endregion

		#pragma region Operations
		void Homogenize();
		void Normalize();
		Vec4 GetNormalized() const;
		float GetMagnitude() const;
		float GetMagnitudeSQ() const;
		// Changes the magnitude of the Vec4.
		void SetMagnitude(float magnitude);
		float DotProduct(const Vec4&) const;
		Vec4 CrossProduct(const Vec4&) const;
		#pragma endregion

		#pragma region Operators
		Vec4& operator=(const Vec4&)	= default;
		Vec4& operator=(Vec4&&)			= default;
		Vec4 operator+(const Vec4&) const;
		Vec4& operator+=(const Vec4&);
		Vec4 operator-() const;
		Vec4 operator-(const Vec4&) const;
		Vec4& operator-=(const Vec4&);
		Vec4 operator*(float) const;
		Vec4& operator*=(float);
		Vec4 operator/(float) const;
		Vec4& operator/=(float);
		bool operator==(const Vec4&) const;
		bool operator!=(const Vec4&) const;
		// /!\ Should be used with caution!
		// Returns the associated component.
		float& operator[](int index);
		// (read only)
		float operator[](int index) const;
		#pragma endregion
	};

	std::ostream& operator<<(std::ostream&, const Vec4&);
	Vec4 operator*(float, const Vec4&);
}

#endif
