#include <iomanip>

#include "Vec4.h"

#include "Vec2.h"
#include "Vec3.h"
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
Vec4::Vec4() :
	m_x{ 0.f },
	m_y{ 0.f },
	m_z{ 0.f },
	m_w{ 1.f }
{}

Vec4::Vec4(float x, float y, float z, float w) :
	m_x{ x },
	m_y{ y },
	m_z{ z },
	m_w{ w }
{}

Vec4::Vec4(const Vec2& lVec2, float z, float w) :
	m_x{ lVec2.m_x },
	m_y{ lVec2.m_y },
	m_z{ z },
	m_w{ w }
{}

Vec4::Vec4(const Vec3& lVec3, float w) :
	m_x{ lVec3.m_x },
	m_y{ lVec3.m_y },
	m_z{ lVec3.m_z },
	m_w{ w }
{}
#pragma endregion

#pragma region Shorthands
Vec4 Vec4::Zero()
{
	return Vec4(0.f, 0.f, 0.f, 1.f);
}

Vec4 Vec4::Left()
{
	return Vec4(-1.f, 0.f, 0.f, 1.f);
}

Vec4 Vec4::Right()
{
	return Vec4(1.f, 0.f, 0.f, 1.f);
}

Vec4 Vec4::Down()
{
	return Vec4(0.f, -1.f, 0.f, 1.f);
}

Vec4 Vec4::Up()
{
	return Vec4(0.f, 1.f, 0.f, 1.f);
}

Vec4 Vec4::Back()
{
	return Vec4(0.f, 0.f, -1.f, 1.f);
}

Vec4 Vec4::Forward()
{
	return Vec4(0.f, 0.f, 1.f, 1.f);
}

Vec4 Vec4::One()
{
	return Vec4(1.f, 1.f, 1.f, 1.f);
}
#pragma endregion

#pragma region Tools
Vec4 Vec4::Lerp(const Vec4& firstVec, const Vec4& secondVec, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	return Vec4(
		LERP(firstVec.m_x, secondVec.m_x, ratio),
		LERP(firstVec.m_y, secondVec.m_y, ratio),
		LERP(firstVec.m_z, secondVec.m_z, ratio)
	);
}

Vec4 Vec4::NLerp(const Vec4& firstVec, const Vec4& secondVec, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	Vec4 result(
		LERP(firstVec.m_x, secondVec.m_x, ratio),
		LERP(firstVec.m_y, secondVec.m_y, ratio),
		LERP(firstVec.m_z, secondVec.m_z, ratio)
	);

	result.Normalize();

	return result;
}

float Vec4::GetAngle(const Vec4& firstVec, const Vec4& secondVec)
{
	return acosf(DOT_PRODUCT_BETWEEN(firstVec, secondVec) / sqrtf(MAGNITUDE_SQ_OF(firstVec) * MAGNITUDE_SQ_OF(secondVec)));
}

float Vec4::GetAngleInDegrees(const Vec4& firstVec, const Vec4& secondVec)
{
	return acosf(DOT_PRODUCT_BETWEEN(firstVec, secondVec) / sqrtf(MAGNITUDE_SQ_OF(firstVec) * MAGNITUDE_SQ_OF(secondVec))) * RAD_TO_DEG_f;
}

Vec4& Vec4::Shortest(Vec4& firstVec, Vec4& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) < MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

const Vec4& Vec4::Shortest(const Vec4& firstVec, const Vec4& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) < MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

Vec4& Vec4::Longest(Vec4& firstVec, Vec4& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) > MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

const Vec4& Vec4::Longest(const Vec4& firstVec, const Vec4& secondVec)
{
	return (MAGNITUDE_SQ_OF(firstVec) > MAGNITUDE_SQ_OF(secondVec)) ? firstVec : secondVec;
}

Vec4 Vec4::Min(const Vec4& firstVec, const Vec4& secondVec)
{
	return Vec4(
		MIN(firstVec.m_x, secondVec.m_x),
		MIN(firstVec.m_y, secondVec.m_y),
		MIN(firstVec.m_z, secondVec.m_z)
	);
}

Vec4 Vec4::Max(const Vec4& firstVec, const Vec4& secondVec)
{
	return Vec4(
		MAX(firstVec.m_x, secondVec.m_x),
		MAX(firstVec.m_y, secondVec.m_y),
		MAX(firstVec.m_z, secondVec.m_z)
	);
}

float Vec4::Distance(const Vec4& firstVertex, const Vec4& secondVertex)
{
	return MAGNITUDE_BETWEEN(firstVertex, secondVertex);
}

float Vec4::DistanceSQ(const Vec4& firstVertex, const Vec4& secondVertex)
{
	return MAGNITUDE_SQ_BETWEEN(firstVertex, secondVertex);
}
#pragma endregion

#pragma region Operations
void Vec4::Homogenize()
{
	if (m_w != 0.f)
	{
		m_x /= m_w;
		m_y /= m_w;
		m_z /= m_w;
	}
}

void Vec4::Normalize()
{
	if (m_x != 0.f || m_y != 0.f || m_z != 0.f)
	{
		float magnitude{ MAGNITUDE };

		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

void Vec4::ReverseValues()
{
	m_x != 0.f ? (1.f / m_x) : 0.f;
	m_y != 0.f ? (1.f / m_y) : 0.f;
	m_z != 0.f ? (1.f / m_z) : 0.f;
	m_w != 0.f ? (1.f / m_w) : 0.f;
}

Vec4 Vec4::GetNormalized() const
{
	if (m_x == 0.f && m_y == 0.f && m_z == 0.f)
		return *this;

	float magnitude{ MAGNITUDE };

	return Vec4(
		m_x / magnitude,
		m_y / magnitude,
		m_z / magnitude,
		m_w
	);
}

float Vec4::GetMagnitude() const
{
	return MAGNITUDE;
}

float Vec4::GetMagnitudeSQ() const
{
	return MAGNITUDE_SQ;
}

Vec4 Vec4::GetInverseValues() const
{
	return Vec4(
		m_x != 0.f ? (1.f / m_x) : 0.f,
		m_y != 0.f ? (1.f / m_y) : 0.f,
		m_z != 0.f ? (1.f / m_z) : 0.f,
		m_w != 0.f ? (1.f / m_w) : 0.f
	);
}

void Vec4::SetMagnitude(float magnitude)
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

	float magnitudeDividedByCurrentMagnitude{ sqrtf(magnitudeSQ / currentMagnitudeSQ) };

	m_x *= magnitudeDividedByCurrentMagnitude;
	m_y *= magnitudeDividedByCurrentMagnitude;
	m_z *= magnitudeDividedByCurrentMagnitude;
}

float Vec4::DotProduct(const Vec4& vec) const
{
	return DOT_PRODUCT_WITH(vec);
}

Vec4 Vec4::CrossProduct(const Vec4& vec) const
{
	return Vec4(
		(m_y * vec.m_z) - (m_z * vec.m_y),
		(m_z * vec.m_x) - (m_x * vec.m_z),
		(m_x * vec.m_y) - (m_y * vec.m_x)
	);
}
#pragma endregion

#pragma region Operators
Vec4 Vec4::operator+(const Vec4& vec) const
{
	return Vec4(
		m_x + vec.m_x,
		m_y + vec.m_y,
		m_z + vec.m_z
	);
}

Vec4& Vec4::operator+=(const Vec4& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	m_z += vec.m_z;

	return *this;
}

Vec4 Vec4::operator-() const
{
	return Vec4(
		-m_x,
		-m_y,
		-m_z,
		m_w
	);
}

Vec4 Vec4::operator-(const Vec4& vec) const
{
	return Vec4(
		m_x - vec.m_x,
		m_y - vec.m_y,
		m_z - vec.m_z
	);
}

Vec4& Vec4::operator-=(const Vec4& vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;
	m_z -= vec.m_z;

	return *this;
}

Vec4 Vec4::operator*(float factor) const
{
	return Vec4(
		m_x * factor,
		m_y * factor,
		m_z * factor,
		m_w
	);
}

Vec4& Vec4::operator*=(float factor)
{
	m_x *= factor;
	m_y *= factor;
	m_z *= factor;

	return *this;
}

Vec4 Vec4::operator/(float divisor) const
{
	if (divisor == 0.f)
		return Vec4::Zero();

	else
		return Vec4(
			m_x / divisor,
			m_y / divisor,
			m_z / divisor,
			m_w
		);
}

Vec4& Vec4::operator/=(float divisor)
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

bool Vec4::operator==(const Vec4& vec) const
{
	return (m_x == vec.m_x) && (m_y == vec.m_y) && (m_z == vec.m_z) && (m_w == vec.m_w);
}

bool Vec4::operator!=(const Vec4& vec) const
{
	return (m_x != vec.m_x) || (m_y != vec.m_y) || (m_z != vec.m_z) || (m_w != vec.m_w);
}

float& Vec4::operator[](int index)
{
	if (index <= 0)
		return m_x;
	else if (index == 1)
		return m_y;
	else if (index == 2)
		return m_z;
	else
		return m_w;
}

float Vec4::operator[](int index) const
{
	if (index <= 0)
		return m_x;
	else if (index == 1)
		return m_y;
	else if (index == 2)
		return m_z;
	else
		return m_w;
}
#pragma endregion

#pragma region External operators
std::ostream& engine::core::maths::operator<<(std::ostream& out, const Vec4& vec)
{
	std::cout << std::setprecision(2) << std::fixed;
	out << "Vec4( " << vec.m_x << " ; " << vec.m_y << " ; " << vec.m_z << " ; " << vec.m_w << " )";
	std::cout << std::setprecision(0) << std::defaultfloat;

	return out;
}

Vec4 engine::core::maths::operator*(float factor, const Vec4& vec)
{
	return Vec4(
		vec.m_x * factor,
		vec.m_y * factor,
		vec.m_z * factor,
		vec.m_w
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