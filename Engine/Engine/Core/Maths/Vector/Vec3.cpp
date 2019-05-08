#include <iomanip>

#include "Vec3.h"

#include "Vec2.h"
#include "Vec4.h"
#include "../Defines.h"

using namespace engine::core::maths;

#pragma region Defines
#define DOT_PRODUCT_BETWEEN(v1, v2) \
	((v1.m_x * v2.m_x) + (v1.m_y * v2.m_y) + (v1.m_z * v2.m_z))



#define DOT_PRODUCT_WITH(vec) \
	((m_x * vec.m_x) + (m_y * vec.m_y) + (m_z * vec.m_z))



#define MAGNITUDE_SQ_OF(vec) \
	((vec.m_x * vec.m_x) + (vec.m_y * vec.m_y) + (vec.m_z * vec.m_z))



#define X(v1, v2) \
	(v1.m_x - v2.m_x)

#define Y(v1, v2) \
	(v1.m_y - v2.m_y)

#define Z(v1, v2) \
	(v1.m_z - v2.m_z)

#define MAGNITUDE_SQ_BETWEEN(v1, v2) \
	((X(v1, v2) * X(v1, v2)) + (Y(v1, v2) * Y(v1,v2)) + (Z(v1, v2) * Z(v1,v2)))

#define MAGNITUDE_BETWEEN(v1, v2) \
	(sqrtf(MAGNITUDE_SQ_BETWEEN(v1, v2)))



#define MAGNITUDE_SQ \
	((m_x * m_x) + (m_y * m_y) + (m_z * m_z))

#define MAGNITUDE \
	(sqrtf(MAGNITUDE_SQ))
#pragma endregion

#pragma region Constructors/destructor
Vec3::Vec3() :
	m_x{ 0.f },
	m_y{ 0.f },
	m_z{ 0.f }
{}

Vec3::Vec3(float x, float y, float z) :
	m_x{ x },
	m_y{ y },
	m_z{ z }
{}

Vec3::Vec3(const Vec2& lVec2, float z) :
	m_x{ lVec2.m_x },
	m_y{ lVec2.m_y },
	m_z{ z }
{}

Vec3::Vec3(const Vec4& lVec4) :
	m_x{ lVec4.m_x },
	m_y{ lVec4.m_y },
	m_z{ lVec4.m_z }
{}
#pragma endregion

#pragma region Shorthands
Vec3 Vec3::Zero()
{
	return Vec3(0.f, 0.f, 0.f);
}

Vec3 Vec3::Left()
{
	return Vec3(-1.f, 0.f, 0.f);
}

Vec3 Vec3::Right()
{
	return Vec3(1.f, 0.f, 0.f);
}

Vec3 Vec3::Down()
{
	return Vec3(0.f, -1.f, 0.f);
}

Vec3 Vec3::Up()
{
	return Vec3(0.f, 1.f, 0.f);
}

Vec3 Vec3::Back()
{
	return Vec3(0.f, 0.f, -1.f);
}

Vec3 Vec3::Forward()
{
	return Vec3(0.f, 0.f, 1.f);
}

Vec3 Vec3::One()
{
	return Vec3(1.f, 1.f, 1.f);
}
#pragma endregion

#pragma region Tools
Vec3 Vec3::Lerp(const Vec3& firstVec, const Vec3& secondVec, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	return Vec3(
		LERP(firstVec.m_x, secondVec.m_x, ratio),
		LERP(firstVec.m_y, secondVec.m_y, ratio),
		LERP(firstVec.m_z, secondVec.m_z, ratio)
	);
}

Vec3 Vec3::NLerp(const Vec3& firstVec, const Vec3& secondVec, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	Vec3 result(
		LERP(firstVec.m_x, secondVec.m_x, ratio),
		LERP(firstVec.m_y, secondVec.m_y, ratio),
		LERP(firstVec.m_z, secondVec.m_z, ratio)
	);

	result.Normalize();

	return result;
}

float Vec3::GetAngle(const Vec3& firstVec, const Vec3& secondVec)
{
	return acosf(DOT_PRODUCT_BETWEEN(firstVec, secondVec) / sqrtf(MAGNITUDE_SQ_OF(firstVec) * MAGNITUDE_SQ_OF(secondVec)));
}

float Vec3::GetAngleInDegrees(const Vec3& firstVec, const Vec3& secondVec)
{
	return acosf(DOT_PRODUCT_BETWEEN(firstVec, secondVec) / sqrtf(MAGNITUDE_SQ_OF(firstVec) * MAGNITUDE_SQ_OF(secondVec))) * RAD_TO_DEG_f;
}

Vec3& Vec3::Shortest(Vec3& firstVec, Vec3& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) < MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

const Vec3& Vec3::Shortest(const Vec3& firstVec, const Vec3& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) < MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

Vec3& Vec3::Longest(Vec3& firstVec, Vec3& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) > MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

const Vec3& Vec3::Longest(const Vec3& firstVec, const Vec3& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) > MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

Vec3 Vec3::Min(const Vec3& firstVec, const Vec3& secondVec)
{
	return Vec3(
		MIN(firstVec.m_x, secondVec.m_x),
		MIN(firstVec.m_y, secondVec.m_y),
		MIN(firstVec.m_z, secondVec.m_z)
	);
}

Vec3 Vec3::Max(const Vec3& firstVec, const Vec3& secondVec)
{
	return Vec3(
		MAX(firstVec.m_x, secondVec.m_x),
		MAX(firstVec.m_y, secondVec.m_y),
		MAX(firstVec.m_z, secondVec.m_z)
	);
}

float Vec3::Distance(const Vec3& firstVertex, const Vec3& secondVertex)
{
	return MAGNITUDE_BETWEEN(firstVertex, secondVertex);
}

float Vec3::DistanceSQ(const Vec3& firstVertex, const Vec3& secondVertex)
{
	return MAGNITUDE_SQ_BETWEEN(firstVertex, secondVertex);
}

Vec3 Vec3::MultComponents(const Vec3& firstVec, const Vec3& secondVec)
{
	return Vec3(
		firstVec.m_x * secondVec.m_x,
		firstVec.m_y * secondVec.m_y,
		firstVec.m_z * secondVec.m_z
	);
}
#pragma endregion

#pragma region Operations
void Vec3::Normalize()
{
	if (m_x != 0.f || m_y != 0.f || m_z != 0.f)
	{
		float magnitude{ MAGNITUDE };

		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

void Vec3::ReverseValues()
{
	m_x != 0.f ? (1.f / m_x) : 0.f;
	m_y != 0.f ? (1.f / m_y) : 0.f;
	m_z != 0.f ? (1.f / m_z) : 0.f;
}

Vec3 Vec3::GetNormalized() const
{
	if (m_x == 0.f && m_y == 0.f && m_z == 0.f)
		return *this;

	else
	{
		float magnitude{ MAGNITUDE };

		return Vec3(
			m_x / magnitude,
			m_y / magnitude,
			m_z / magnitude
		);
	}
}

float Vec3::GetMagnitude() const
{
	return MAGNITUDE;
}

float Vec3::GetMagnitudeSQ() const
{
	return MAGNITUDE_SQ;
}

Vec3 Vec3::GetInverseValues() const
{
	return Vec3(
		m_x != 0.f ? (1.f / m_x) : 0.f,
		m_y != 0.f ? (1.f / m_y) : 0.f,
		m_z != 0.f ? (1.f / m_z) : 0.f
	);
}

void Vec3::SetMagnitude(float magnitude)
{
	if (magnitude == 0.f)
	{
		m_x = 0.f;
		m_y = 0.f;
		m_z = 0.f;

		return;
	}

	float magnitudeSQ{ magnitude * magnitude };
	float currentMagnitudeSQ{ MAGNITUDE_SQ };

	if ((m_x == 0.f && m_y == 0.f && m_z == 0.f) || (magnitudeSQ == currentMagnitudeSQ))
		return;

	else
	{
		float magnitudeDividedByCurrentMagnitude{ sqrtf(magnitudeSQ / currentMagnitudeSQ) };

		m_x *= magnitudeDividedByCurrentMagnitude;
		m_y *= magnitudeDividedByCurrentMagnitude;
		m_z *= magnitudeDividedByCurrentMagnitude;
	}
}

float Vec3::DotProduct(const Vec3& vec) const
{
	return DOT_PRODUCT_WITH(vec);
}

Vec3 Vec3::CrossProduct(const Vec3& vec) const
{
	return Vec3(
		(m_y * vec.m_z) - (m_z * vec.m_y),
		(m_z * vec.m_x) - (m_x * vec.m_z),
		(m_x * vec.m_y) - (m_y * vec.m_x)
	);
}
#pragma endregion

#pragma region Operators
Vec3 Vec3::operator+(const Vec3& vec) const
{
	return Vec3(
		m_x + vec.m_x,
		m_y + vec.m_y,
		m_z + vec.m_z
	);
}

Vec3& Vec3::operator+=(const Vec3& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	m_z += vec.m_z;

	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(
		-m_x,
		-m_y,
		-m_z
	);
}

Vec3 Vec3::operator-(const Vec3& vec) const
{
	return Vec3(
		m_x - vec.m_x,
		m_y - vec.m_y,
		m_z - vec.m_z
	);
}

Vec3& Vec3::operator-=(const Vec3& vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;
	m_z -= vec.m_z;

	return *this;
}

Vec3 Vec3::operator*(float factor) const
{
	return Vec3(
		m_x * factor,
		m_y * factor,
		m_z * factor
	);
}

Vec3& Vec3::operator*=(float factor)
{
	m_x *= factor;
	m_y *= factor;
	m_z *= factor;

	return *this;
}

Vec3 Vec3::operator/(float divisor) const
{
	if (divisor == 0.f)
		return Vec3::Zero();

	else
		return Vec3(
			m_x / divisor,
			m_y / divisor,
			m_z / divisor
		);
}

Vec3& Vec3::operator/=(float divisor)
{
	if (divisor == 0.f)
	{
		m_x = 0.f;
		m_y = 0.f;
		m_z = 0.f;
	}

	else
	{
		m_x /= divisor;
		m_y /= divisor;
		m_z /= divisor;
	}

	return *this;
}

bool Vec3::operator==(const Vec3& vec) const
{
	return (m_x == vec.m_x) && (m_y == vec.m_y) && (m_z == vec.m_z);
}

bool Vec3::operator!=(const Vec3& vec) const
{
	return (m_x != vec.m_x) || (m_y != vec.m_y) || (m_z != vec.m_z);
}

float& Vec3::operator[](int index)
{
	if (index <= 0)
		return m_x;
	else if (index == 1)
		return m_y;
	else
		return m_z;
}

float Vec3::operator[](int index) const
{
	if (index <= 0)
		return m_x;
	else if (index == 1)
		return m_y;
	else
		return m_z;
}
#pragma endregion

#pragma region External operators
std::ostream& engine::core::maths::operator<<(std::ostream& out, const Vec3& vec)
{
	std::cout << std::setprecision(2) << std::fixed;
	out << "Vec3( " << vec.m_x << " ; " << vec.m_y << " ; " << vec.m_z << " )";
	std::cout << std::setprecision(0) << std::defaultfloat;

	return out;
}

Vec3 engine::core::maths::operator*(float factor, const Vec3& vec)
{
	return Vec3(
		vec.m_x * factor,
		vec.m_y * factor,
		vec.m_z * factor
	);
}
#pragma endregion

#pragma region Undefs
#undef MAGNITUDE
#undef MAGNITUDE_SQ
#undef MAGNITUDE_BETWEEN
#undef MAGNITUDE_SQ_BETWEEN
#undef Z
#undef Y
#undef X
#undef MAGNITUDE_SQ_OF
#undef DOT_PRODUCT_WITH
#undef DOT_PRODUCT_BETWEEN
#pragma endregion