#include <iomanip>

#include "Vec2.h"

#include "Vec3.h"
#include "Vec4.h"
#include "../Defines.h"

using namespace engine::core::maths;

#pragma region Defines
#define DOT_PRODUCT_BETWEEN(v1, v2) \
	((v1.m_x * v2.m_x) + (v1.m_y * v2.m_y))



#define DOT_PRODUCT_WITH(vec) \
	((m_x * vec.m_x) + (m_y * vec.m_y))



#define MAGNITUDE_SQ_OF(vec) \
	((vec.m_x * vec.m_x) + (vec.m_y * vec.m_y))

#define MAGNITUDE_OF(vec) \
	(sqrtf(MAGNITUDE_SQ_OF(vec))



#define X(v1, v2) \
	(v2.m_x - v1.m_x)

#define Y(v1, v2) \
	(v2.m_y - v1.m_y)

#define MAGNITUDE_SQ_BETWEEN(v1, v2) \
	((X(v1, v2) * X(v1, v2)) + (Y(v1, v2) * Y(v1,v2)))

#define MAGNITUDE_BETWEEN(v1, v2) \
	(sqrtf(MAGNITUDE_SQ_BETWEEN(v1, v2)))



#define MAGNITUDE_SQ \
	((m_x * m_x) + (m_y * m_y))

#define MAGNITUDE \
	(sqrtf(MAGNITUDE_SQ))
#pragma endregion

#pragma region Constructors/destructor
Vec2::Vec2() :
	m_x{ 0.f },
	m_y{ 0.f }
{}

Vec2::Vec2(float x, float y) :
	m_x{ x },
	m_y{ y }
{}

Vec2::Vec2(const Vec3& lVec3) :
	m_x{ lVec3.m_x },
	m_y{ lVec3.m_y }
{}

Vec2::Vec2(const Vec4& lVec4) :
	m_x{ lVec4.m_x },
	m_y{ lVec4.m_y }
{}
#pragma endregion

#pragma region Shorthands
Vec2 Vec2::Zero()
{
	return Vec2(0.f, 0.f);
}

Vec2 Vec2::Left()
{
	return Vec2(-1.f, 0.f);
}

Vec2 Vec2::Right()
{
	return Vec2(1.f, 0.f);
}

Vec2 Vec2::Down()
{
	return Vec2(0.f, -1.f);
}

Vec2 Vec2::Up()
{
	return Vec2(0.f, 1.f);
}

Vec2 Vec2::One()
{
	return Vec2(1.f, 1.f);
}
#pragma endregion

#pragma region Tools
Vec2 Vec2::Lerp(const Vec2& firstVec, const Vec2& secondVec, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	return Vec2(
		LERP(firstVec.m_x, secondVec.m_x, ratio),
		LERP(firstVec.m_y, secondVec.m_y, ratio)
	);
}

Vec2 Vec2::NLerp(const Vec2& firstVec, const Vec2& secondVec, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	Vec2 result(
		LERP(firstVec.m_x, secondVec.m_x, ratio),
		LERP(firstVec.m_y, secondVec.m_y, ratio)
	);

	result.Normalize();

	return result;
}

float Vec2::GetAngle(const Vec2& firstVec, const Vec2& secondVec)
{
	return acosf(DOT_PRODUCT_BETWEEN(firstVec, secondVec) / sqrtf(MAGNITUDE_SQ_OF(firstVec) * MAGNITUDE_SQ_OF(secondVec)));
}

float Vec2::GetAngleInDegrees(const Vec2& firstVec, const Vec2& secondVec)
{
	return acosf(DOT_PRODUCT_BETWEEN(firstVec, secondVec) / sqrtf(MAGNITUDE_SQ_OF(firstVec) * MAGNITUDE_SQ_OF(secondVec))) * RAD_TO_DEG_f;
}

Vec2& Vec2::Shortest(Vec2& firstVec, Vec2& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) < MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

const Vec2& Vec2::Shortest(const Vec2& firstVec, const Vec2& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) < MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

Vec2& Vec2::Longest(Vec2& firstVec, Vec2& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) > MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

const Vec2& Vec2::Longest(const Vec2& firstVec, const Vec2& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) > MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

Vec2 Vec2::Min(const Vec2& firstVec, const Vec2& secondVec)
{
	return Vec2(
		MIN(firstVec.m_x, secondVec.m_x),
		MIN(firstVec.m_y, secondVec.m_y)
	);
}

Vec2 Vec2::Max(const Vec2& firstVec, const Vec2& secondVec)
{
	return Vec2(
		MAX(firstVec.m_x, secondVec.m_x),
		MAX(firstVec.m_y, secondVec.m_y)
	);
}

float Vec2::Distance(const Vec2& firstVertex, const Vec2& secondVertex)
{
	return MAGNITUDE_BETWEEN(firstVertex, secondVertex);
}

float Vec2::DistanceSQ(const Vec2& firstVertex, const Vec2& secondVertex)
{
	return MAGNITUDE_SQ_BETWEEN(firstVertex, secondVertex);
}
#pragma endregion

#pragma region Operations
void Vec2::Normalize()
{
	if (m_x != 0.f || m_y != 0.f)
	{
		float magnitude{ MAGNITUDE };

		m_x /= magnitude;
		m_y /= magnitude;
	}
}

void Vec2::ReverseValues()
{
	m_x != 0.f ? (1.f / m_x) : 0.f;
	m_y != 0.f ? (1.f / m_y) : 0.f;
}

Vec2 Vec2::GetNormalized() const
{
	if (m_x == 0.f && m_y == 0.f)
		return *this;

	else
	{
		float magnitude{ MAGNITUDE };

		return Vec2(
			m_x / magnitude,
			m_y / magnitude
		);
	}
}

float Vec2::GetMagnitude() const
{
	return MAGNITUDE;
}

float Vec2::GetMagnitudeSQ() const
{
	return MAGNITUDE_SQ;
}

Vec2 Vec2::GetInverseValues() const
{
	return Vec2(
		m_x != 0.f ? (1.f / m_x) : 0.f,
		m_y != 0.f ? (1.f / m_y) : 0.f
	);
}

void Vec2::SetMagnitude(float magnitude)
{
	if (magnitude == 0.f)
	{
		m_x = 0.f;
		m_y = 0.f;
	}

	else if ((m_x == 0.f && m_y == 0.f) || (magnitude * magnitude == MAGNITUDE_SQ))
		return;

	else
	{
		float magnitudeDividedByCurrentMagnitude{ magnitude / MAGNITUDE };
		m_x *= magnitudeDividedByCurrentMagnitude;
		m_y *= magnitudeDividedByCurrentMagnitude;
	}
}

float Vec2::DotProduct(const Vec2& vec) const
{
	return DOT_PRODUCT_WITH(vec);
}
#pragma endregion

#pragma region Operators
Vec2 Vec2::operator+(const Vec2& vec) const
{
	return Vec2(
		m_x + vec.m_x,
		m_y + vec.m_y
	);
}

Vec2& Vec2::operator+=(const Vec2& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;

	return *this;
}

Vec2 Vec2::operator-() const
{
	return Vec2(
		-m_x,
		-m_y
	);
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	return Vec2(
		m_x - vec.m_x,
		m_y - vec.m_y
	);
}

Vec2& Vec2::operator-=(const Vec2& vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;

	return *this;
}

Vec2 Vec2::operator*(float factor) const
{
	return Vec2(
		m_x * factor,
		m_y * factor
	);
}

Vec2& Vec2::operator*=(float factor)
{
	m_x *= factor;
	m_y *= factor;

	return *this;
}

Vec2 Vec2::operator/(float divisor) const
{
	if (divisor == 0.f)
		return Vec2::Zero();

	else
		return Vec2(
			m_x / divisor,
			m_y / divisor
		);
}

Vec2& Vec2::operator/=(float divisor)
{
	if (divisor == 0.f)
	{
		m_x = 0.f;
		m_y = 0.f;
	}

	else
	{
		m_x /= divisor;
		m_y /= divisor;
	}

	return *this;
}

bool Vec2::operator==(const Vec2& vec) const
{
	return (m_x == vec.m_x) && (m_y == vec.m_y);
}

bool Vec2::operator!=(const Vec2& vec) const
{
	return (m_x != vec.m_x) || (m_y != vec.m_y);
}

float& Vec2::operator[](int index)
{
	if (index <= 0)
		return m_x;
	else
		return m_y;
}

float Vec2::operator[](int index) const
{
	if (index <= 0)
		return m_x;
	else
		return m_y;
}
#pragma endregion

#pragma region External operators
std::ostream& engine::core::maths::operator<<(std::ostream& out, const Vec2& vec)
{
	std::cout << std::setprecision(2) << std::fixed;
	out << "Vec2( " << vec.m_x << " ; " << vec.m_y << " )";
	std::cout << std::setprecision(0) << std::defaultfloat;

	return out;
}

Vec2 engine::core::maths::operator*(float factor, const Vec2& vec)
{
	return Vec2(
		vec.m_x * factor,
		vec.m_y * factor
	);
}
#pragma endregion

#pragma region Undefs
#undef MAGNITUDE
#undef MAGNITUDE_SQ
#undef MAGNITUDE_BETWEEN
#undef MAGNITUDE_SQ_BETWEEN
#undef Y
#undef X
#undef MAGNITUDE_OF
#undef MAGNITUDE_SQ_OF
#undef DOT_PRODUCT_WITH
#undef DOT_PRODUCT_BETWEEN
#pragma endregion
