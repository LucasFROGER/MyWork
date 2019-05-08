#pragma once
#ifndef __CORE__MATHS__VEC3_H__
#define __CORE__MATHS__VEC3_H__

#include "Vec2.h"

namespace temath
{
	struct Vec3
	{
		#pragma region Variables
		float m_x;
		float m_y;
		float m_z;
		#pragma endregion

		#pragma region Constructors/destructor
		Vec3();
		Vec3(const Vec3& lVec3)	= default;
		Vec3(Vec3&& rVec3)		= default;
		Vec3(float x, float y, float z);
		Vec3(const Vec2& lVec2, float z);
		~Vec3()					= default;
		#pragma endregion

		#pragma region Shorthands
		// Generates a Vec3 : ( 0 ; 0 ; 0 ).
		static Vec3 Zero();
		// Generates a Vec3 : ( -1 ; 0 ; 0 ).
		static Vec3 Left();
		// Generates a Vec3 : ( 1 ; 0 ; 0 ).
		static Vec3 Right();
		// Generates a Vec3 : ( 0 ; -1 ; 0 ).
		static Vec3 Down();
		// Generates a Vec3 : ( 0 ; 1 ; 0 ).
		static Vec3 Up();
		// Generates a Vec3 : ( 0 ; 0 ; -1 ).
		static Vec3 Back();
		// Generates a Vec3 : ( 0 ; 0 ; 1 ).
		static Vec3 Forward();
		// Generates a Vec3 : ( 1 ; 1 ; 1 ).
		static Vec3 One();
		#pragma endregion

		#pragma region Tools
		// Returns a Vec3 between firstVec and secondVec.
		// The ratio is clamped to the range[0, 1].
		// If the ratio is 0, the Vec3 returned is equal to firstVec.
		// If the ratio is 1, the Vec3 returned is equal to secondVec.
		static Vec3 Lerp(const Vec3& firstVec, const Vec3& secondVec, float ratio);
		static Vec3 NLerp(const Vec3& firstVec, const Vec3& secondVec, float ratio);

		// Returns the angle in radians between the two Vec3.
		static float GetAngle(const Vec3& firstVec, const Vec3& secondVec);
		// Returns the angle in degrees between the two Vec3.
		static float GetAngleInDegrees(const Vec3& firstVec, const Vec3& secondVec);

		// Returns the Vec3 with the smallest magnitude.
		static Vec3& Shortest(Vec3& firstVec, Vec3& secondVec);
		// Returns the const Vec3 with the smallest magnitude.
		static const Vec3& Shortest(const Vec3& firstVec, const Vec3& secondVec);

		// Returns the Vec3 with the biggest magnitude.
		static Vec3& Longest(Vec3& firstVec, Vec3& secondVec);
		// Returns the const Vec3 with the biggest magnitude.
		static const Vec3& Longest(const Vec3& firstVec, const Vec3& secondVec);

		// Returns a Vec3 with the smallest components.
		static Vec3 Min(const Vec3& firstVec, const Vec3& secondVec);
		// Returns a Vec3 with the biggest components.
		static Vec3 Max(const Vec3& firstVec, const Vec3& secondVec);

		// Returns the distance between two vertices.
		static float Distance(const Vec3& firstVertex, const Vec3& secondVertex);
		// Returns the distance squared between two vertices.
		static float DistanceSQ(const Vec3& firstVertex, const Vec3& secondVertex);

		// Returns a Vec2 made from this Vec3.
		// z component is lost.
		Vec2 ToVec2() const;
		#pragma endregion

		#pragma region Operations
		void Normalize();
		Vec3 GetNormalized() const;
		float GetMagnitude() const;
		float GetMagnitudeSQ() const;
		// Changes the magnitude of the Vec3.
		void SetMagnitude(float magnitude);
		float DotProduct(const Vec3&) const;
		Vec3 CrossProduct(const Vec3&) const;
		#pragma endregion

		#pragma region Operators
		Vec3& operator=(const Vec3&)	= default;
		Vec3& operator=(Vec3&&)			= default;
		Vec3 operator+(const Vec3&) const;
		Vec3& operator+=(const Vec3&);
		Vec3 operator-() const;
		Vec3 operator-(const Vec3&) const;
		Vec3& operator-=(const Vec3&);
		Vec3 operator*(float) const;
		Vec3& operator*=(float);
		Vec3 operator/(float) const;
		Vec3& operator/=(float);
		bool operator==(const Vec3&) const;
		bool operator!=(const Vec3&) const;
		// /!\ Should be used with caution!
		// Returns the associated component.
		float& operator[](int index);
		// (read only)
		float operator[](int index) const;
		#pragma endregion
	};

	std::ostream& operator<<(std::ostream&, const Vec3&);
	Vec3 operator*(float, const Vec3&);
}

#endif
