#include <iomanip>

#include "Quaternion.h"

#include "Matrix\Mat4.h"
#include "Defines.h"

using namespace engine::core::maths;

#pragma region Defines
#define DOT_PRODUCT_BETWEEN(q1, q2) \
	((q1.m_w * q2.m_w) + (q1.m_x * q2.m_x) + (q1.m_y * q2.m_y) + (q1.m_z * q2.m_z))



#define DOT_PRODUCT_WITH(quat) \
	((m_w * quat.m_w) + (m_x * quat.m_x) + (m_y * quat.m_y) + (m_z * quat.m_z))



#define MODULUS_SQ \
	((m_w * m_w) + (m_x * m_x) + (m_y * m_y) + (m_z * m_z))

#define MODULUS \
	(sqrtf(MODULUS_SQ))
#pragma endregion

#pragma region Constructors/destructor
Quaternion::Quaternion() :
	m_w{ 1.f },
	m_x{ 0.f },
	m_y{ 0.f },
	m_z{ 0.f }
{}

Quaternion::Quaternion(float scalar) :
	m_w{ scalar },
	m_x{ 0.f },
	m_y{ 0.f },
	m_z{ 0.f }
{}

Quaternion::Quaternion(float w, float x, float y, float z) :
	m_w{ w },
	m_x{ x },
	m_y{ y },
	m_z{ z }
{}

Quaternion::Quaternion(float scalar, const Vec3& vector) :
	m_w{ scalar },
	m_x{ vector.m_x },
	m_y{ vector.m_y },
	m_z{ vector.m_z }
{}
#pragma endregion

#pragma region Shorthands
Quaternion Quaternion::Identity()
{
	return Quaternion(1.0f);
}
#pragma endregion

#pragma region Tools
Quaternion Quaternion::Euler(const Vec3& eulerAngles)
{
	float yaw = eulerAngles.m_x * DEG_TO_RAD_f;
	float pitch = eulerAngles.m_y * DEG_TO_RAD_f;
	float roll = eulerAngles.m_z * DEG_TO_RAD_f;
	float rollOver2 = roll * 0.5f;
	float sinRollOver2 = sinf(rollOver2);
	float cosRollOver2 = cosf(rollOver2);
	float pitchOver2 = pitch * 0.5f;
	float sinPitchOver2 = sinf(pitchOver2);
	float cosPitchOver2 = cosf(pitchOver2);
	float yawOver2 = yaw * 0.5f;
	float sinYawOver2 = sinf(yawOver2);
	float cosYawOver2 = cosf(yawOver2);
	return Quaternion(
		//cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2,
		cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2, // confirmed (ccc+sss)
		//sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2,
		sinYawOver2 * cosPitchOver2 * cosRollOver2 + cosYawOver2 * sinPitchOver2 * sinRollOver2, // confirmed (scc+css)
		//cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2,
		cosYawOver2 * sinPitchOver2 * cosRollOver2 - sinYawOver2 * cosPitchOver2 * sinRollOver2, // confirmed (csc-scs)
		//cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2
		cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2 // confirmed (ccs-ssc)
	);
}

// pitch = eulerAngles.m_x
// yaw = eulerAngles.m_y
// roll = eulerAngles.m_z
Quaternion Quaternion::Euler2(const Vec3& eulerAngles)
{
	float c1 = cosf(DEG_TO_RAD_f * eulerAngles.m_y / 2.0f);
	float c2 = cosf(DEG_TO_RAD_f * eulerAngles.m_z / 2.0f);
	float c3 = cosf(DEG_TO_RAD_f * eulerAngles.m_x / 2.0f);

	float s1 = sinf(DEG_TO_RAD_f * eulerAngles.m_y / 2.0f);
	float s2 = sinf(DEG_TO_RAD_f * eulerAngles.m_z / 2.0f);
	float s3 = sinf(DEG_TO_RAD_f * eulerAngles.m_x / 2.0f);

	return Quaternion(
		c1 * c2 * c3 - s1 * s2 * s3,
		s1 * s2 * c3 + c1 * c2 * s3,
		s1 * c2 * c3 + c1 * s2 * s3,
		c1 * s2 * c3 - s1 * c2 * s3
	);
}

Quaternion Quaternion::Lerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	return Quaternion(
		LERP(leftQuat.m_w, rightQuat.m_w, ratio),
		LERP(leftQuat.m_x, rightQuat.m_x, ratio),
		LERP(leftQuat.m_y, rightQuat.m_y, ratio),
		LERP(leftQuat.m_z, rightQuat.m_z, ratio)
	);
}

Quaternion Quaternion::NLerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	Quaternion result(
		LERP(leftQuat.m_w, rightQuat.m_w, ratio),
		LERP(leftQuat.m_x, rightQuat.m_x, ratio),
		LERP(leftQuat.m_y, rightQuat.m_y, ratio),
		LERP(leftQuat.m_z, rightQuat.m_z, ratio)
	);

	result.Normalize();

	return result;
}

Quaternion Quaternion::Slerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float ratio)
{
	ratio = CLAMP(ratio, 0.f, 1.f);

	Quaternion q;

	float cosOmega{ DOT_PRODUCT_BETWEEN(leftQuat, rightQuat) };
	if (cosOmega < 0.f)
	{
		q = Quaternion(-rightQuat.m_w, -rightQuat.m_x, -rightQuat.m_y, -rightQuat.m_z);
		cosOmega = -cosOmega;
	}
	else
		q = rightQuat;

	float k0, k1;
	if (cosOmega > 0.9999f)
	{
		k0 = 1.f - ratio;
		k1 = ratio;
	}
	else
	{
		float sinOmega{ sqrtf(1.f - cosOmega * cosOmega) };
		float omega{ atan2f(sinOmega, cosOmega) };

		k0 = sinf((1.f - ratio) * omega) / sinOmega;
		k1 = sinf(ratio * omega) / sinOmega;
	}

	Quaternion result(k0 * leftQuat.m_w, k0 * leftQuat.m_x, k0 * leftQuat.m_y, k0 * leftQuat.m_z);
	return result += q * k1;
}

//Quaternion Quaternion::Slerp1(const Quaternion& leftQuat, const Quaternion& rightQuat, float t)
//{
//	// Only unit quaternions are valid rotations.
//	// Normalize to avoid undefined behavior.
//	Quaternion v0(leftQuat.GetNormalized());
//	Quaternion v1(rightQuat.GetNormalized());
//
//	// Compute the cosine of the angle between the two vectors.
//	float dot = v0.DotProduct(v1);
//
//	const float DOT_THRESHOLD = 0.9995f;
//	if (fabs(dot) > DOT_THRESHOLD) 
//	{
//		// If the inputs are too close for comfort, linearly interpolate
//		// and normalize the result.
//
//		Quaternion result = v0 + Quaternion(t)*(v1 - v0);
//		result.Normalize();
//		return result;
//	}
//
//	// If the dot product is negative, the quaternions
//	// have opposite handed-ness and slerp won't take
//	// the shorter path. Fix by reversing one quaternion.
//	if (dot < 0.0f)
//	{
//		v1 = -v1;
//		dot = -dot;
//	}
//
//	CLAMP(dot, -1.f, 1.f);           // Robustness: Stay within domain of acos()
//	float theta_0 = acosf(dot);  // theta_0 = angle between input vectors
//	float theta = theta_0 * t;    // theta = angle between v0 and result 
//
//	Quaternion v2(v1 - v0 * dot);
//	v2.Normalize();              // { v0, v2 } is now an orthonormal basis
//
//	return v0*cosf(theta) + v2*sinf(theta);
//}
#pragma endregion

#pragma region Operators
Quaternion& Quaternion::operator=(float scalar)
{
	m_w = scalar;
	m_x = 0.f;
	m_y = 0.f;
	m_z = 0.f;

	return *this;
}

Quaternion Quaternion::operator+(float scalar) const
{
	return Quaternion(
		m_w + scalar,
		m_x,
		m_y,
		m_z
	);
}

Quaternion Quaternion::operator+(const Quaternion& quat) const
{
	return Quaternion(
		m_w + quat.m_w,
		m_x + quat.m_x,
		m_y + quat.m_y,
		m_z + quat.m_z
	);
}

Quaternion& Quaternion::operator+=(float scalar)
{
	m_w += scalar;

	return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
	m_w += quat.m_w;
	m_x += quat.m_x;
	m_y += quat.m_y;
	m_z += quat.m_z;

	return *this;
}

Quaternion& Quaternion::operator-()
{
	m_w = -m_w;
	m_x = -m_x;
	m_y = -m_y;
	m_z = -m_z;

	return *this;
}

Quaternion Quaternion::operator-(float scalar) const
{
	return Quaternion(
		m_w - scalar,
		m_x,
		m_y,
		m_z
	);
}

Quaternion Quaternion::operator-(const Quaternion& quat) const
{
	return Quaternion(
		m_w - quat.m_w,
		m_x - quat.m_x,
		m_y - quat.m_y,
		m_z - quat.m_z
	);
}

Quaternion& Quaternion::operator-=(float scalar)
{
	m_w -= scalar;

	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quat)
{
	m_w -= quat.m_w;
	m_x -= quat.m_x;
	m_y -= quat.m_y;
	m_z -= quat.m_z;

	return *this;
}

Quaternion Quaternion::operator*(float scalar) const
{
	return Quaternion(
		m_w * scalar,
		m_x * scalar,
		m_y * scalar,
		m_z * scalar
	);
}

Quaternion Quaternion::operator*(const Quaternion& quat) const
{
	return Quaternion(
		(m_w * quat.m_w) - (m_x * quat.m_x) - (m_y * quat.m_y) - (m_z * quat.m_z),
		(m_w * quat.m_x) + (m_x * quat.m_w) + (m_y * quat.m_z) - (m_z * quat.m_y),
		(m_w * quat.m_y) - (m_x * quat.m_z) + (m_y * quat.m_w) + (m_z * quat.m_x),
		(m_w * quat.m_z) + (m_x * quat.m_y) - (m_y * quat.m_x) + (m_z * quat.m_w)
	);
}

Quaternion& Quaternion::operator*=(float scalar)
{
	m_w *= scalar;
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;

	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& quat)
{
	float w{ m_w };
	float x{ m_x };
	float y{ m_y };
	float z{ m_z };

	m_w = (w * quat.m_w) - (x * quat.m_x) - (y * quat.m_y) - (z * quat.m_z);
	m_x = (w * quat.m_x) + (x * quat.m_w) + (y * quat.m_z) - (z * quat.m_y);
	m_y = (w * quat.m_y) - (x * quat.m_z) + (y * quat.m_w) + (z * quat.m_x);
	m_z = (w * quat.m_z) + (x * quat.m_y) - (y * quat.m_x) + (z * quat.m_w);

	return *this;
}

Quaternion Quaternion::operator/(float scalar) const
{
	return Quaternion(
		m_w / scalar,
		m_x / scalar,
		m_y / scalar,
		m_z / scalar
	);
}

Quaternion Quaternion::operator/(const Quaternion& quat) const
{
	Quaternion invQuat(quat.GetInverse());

	return *this * invQuat;
}

Quaternion& Quaternion::operator/=(float scalar)
{
	m_w /= scalar;
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;

	return *this;
}

Quaternion& Quaternion::operator/=(const Quaternion& quat)
{
	Quaternion invQuat(quat.GetInverse());

	*this *= invQuat;

	return *this;
}

bool Quaternion::operator==(const Quaternion& quat) const
{
	return (m_w == quat.m_w) && (m_x == quat.m_x) && (m_y == quat.m_y) && (m_z == quat.m_z);
}

bool Quaternion::operator!=(const Quaternion& quat) const
{
	return (m_w != quat.m_w) || (m_x != quat.m_x) || (m_y != quat.m_y) || (m_z != quat.m_z);
}

float& Quaternion::operator[](int index)
{
	index = MAX(0, MIN(index, 3));

	switch (index)
	{
	case 0:
		return m_w;
		break;
	case 1:
		return m_x;
		break;
	case 2:
		return m_y;
		break;
	default:
		return m_z;
		break;
	}
}

float Quaternion::operator[](int index) const
{
	index = MAX(0, MIN(index, 3));

	switch (index)
	{
	case 0:
		return m_w;
		break;
	case 1:
		return m_x;
		break;
	case 2:
		return m_y;
		break;
	default:
		return m_z;
		break;
	}
}
#pragma endregion

#pragma region Operations
bool Quaternion::Normalize()
{
	if (m_x != 0.f || m_y != 0.f || m_z != 0.f || m_w != 0.f)
	{
		float modulus{ MODULUS };

		m_w /= modulus;
		m_x /= modulus;
		m_y /= modulus;
		m_z /= modulus;

		return true;
	}

	return false;
}

bool Quaternion::Reverse()
{
	if (m_x != 0.f || m_y != 0.f || m_z != 0.f || m_w != 0.f)
	{
		float modulusSQ{ MODULUS_SQ };

		m_w /= modulusSQ;
		m_x = -m_x / modulusSQ;
		m_y = -m_y / modulusSQ;
		m_z = -m_z / modulusSQ;

		return true;
	}

	return false;
}

Quaternion Quaternion::GetNormalized(bool* succed) const
{
	if (m_x == 0.f && m_y == 0.f && m_z == 0.f && m_w == 0.f)
	{
		if (succed)
			*succed = false;

		return *this;
	}

	if (succed)
		*succed = true;

	float modulus{ MODULUS };

	return Quaternion(
		m_w / modulus,
		m_x / modulus,
		m_y / modulus,
		m_z / modulus
	);
}

float Quaternion::GetModulus() const
{
	return MODULUS;
}

float Quaternion::GetModulusSQ() const
{
	return MODULUS_SQ;
}

float Quaternion::GetScalarPart() const
{
	return m_w;
}

Vec3 Quaternion::GetVectorPart() const
{
	return Vec3(m_x, m_y, m_z);
}

float Quaternion::GetAngle() const
{
	// Note : m_w = cosf(0.5f * angle)

	return acosf(m_w) * 2.f;
}

Vec3 Quaternion::GetEulerAngles() const
{
	float sinr = 2.f * (m_w * m_x + m_y * m_z);
	float cosr = 1.f - 2.f * (m_x * m_x + m_y * m_y);
	float pitch = atan2f(sinr, cosr);

	float sinp = 2.f * (m_w * m_y - m_z * m_x);
	float yaw{ 0.f };
	if (fabsf(sinp) >= 1.f)
		yaw = copysignf(PI_f / 2.f, sinp);
	else
		yaw = asinf(sinp);

	float siny = 2.f * (m_w * m_z + m_x * m_y);
	float cosy = 1.f - 2.f * (m_y * m_y + m_z * m_z);
	float roll = atan2f(siny, cosy);

	return Vec3(
		pitch * RAD_TO_DEG_f,
		yaw * RAD_TO_DEG_f,
		roll * RAD_TO_DEG_f
	);
}

Vec3 Quaternion::GetEulerAngles2() const
{
	float roll = atan2f(2.f * (m_x * m_y + m_w * m_z), m_w * m_w + m_x * m_x - m_y * m_y - m_z * m_z);

	float pitch;

	const float y = 2.f * (m_y * m_z + m_w * m_x);
	const float x = m_w * m_w - m_x * m_x - m_y * m_y + m_z * m_z;

	if (y == 0.f && x == 0.f)
		pitch = 2.f * atan2f(m_x, m_w);

	else
		pitch = atan2f(y, x);

	float yaw = asinf(CLAMP(-2.f * (m_x * m_z - m_w * m_y), -1.f, 1.f));

	return Vec3(
		pitch * RAD_TO_DEG_f,
		yaw * RAD_TO_DEG_f,
		roll * RAD_TO_DEG_f
	);
}

Vec3 Quaternion::GetEulerAngles3() const
{
	float sqw = m_w * m_w;
	float sqx = m_x * m_x;
	float sqy = m_y * m_y;
	float sqz = m_z * m_z;
	float unit = sqx + sqy + sqz + sqw;
	float test = m_x * m_w - m_y * m_z;
	Vec3 v;

	if (test > 0.4995f * unit)
	{
		v.m_y = 2.0f * atan2f(m_y, m_x);
		v.m_x = PI_f / 2.0f;
		v.m_z = 0.0f;
		return NormalizeAngles(v * RAD_TO_DEG_f);
	}
	if (test < -0.4995f * unit)
	{
		v.m_y = -2.0f * atan2f(m_y, m_x);
		v.m_x = -PI_f / 2.0f;
		v.m_z = 0.0f;
		return NormalizeAngles(v * RAD_TO_DEG_f);
	}
	Quaternion q(m_y, m_w, m_z, m_x);
	v.m_y = atan2f(2.0f * q.m_x * q.m_w + 2.0f * q.m_y * q.m_z, 1.0f - 2.0f * (q.m_z * q.m_z + q.m_w * q.m_w));
	v.m_x = asinf(2.0f * (q.m_x * q.m_z - q.m_w * q.m_y));
	v.m_z = atan2f(2.0f * q.m_x * q.m_y + 2.0f * q.m_z * q.m_w, 1.0f - 2.0f * (q.m_y * q.m_y + q.m_z * q.m_z));
	return NormalizeAngles(v * RAD_TO_DEG_f);
}

Vec3 Quaternion::NormalizeAngles(Vec3 angles) const
{
	angles.m_x = NormalizeAngle(angles.m_x);
	angles.m_y = NormalizeAngle(angles.m_y);
	angles.m_z = NormalizeAngle(angles.m_z);
	return angles;
}
float Quaternion::NormalizeAngle(float angle) const
{
	while (angle > 360.0f)
		angle -= 360.0f;
	while (angle < 0.0f)
		angle += 360.0f;
	return angle;
}

Vec3 Quaternion::GetAxis() const
{
	// Note : (m_x, m_y, m_z) = axe * sinf(0.5f * angle)
	
	float value{ 0.f };

	if (m_w > 1.f)
	{
		Quaternion n(GetNormalized());
		value = sqrtf(1.f - n.m_w * n.m_w);
	}
	else
		value = sqrtf(1.f - m_w * m_w);

	return Vec3(
		m_x / value,
		m_y / value,
		m_z / value
	);
}

Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(
		m_w,
		-m_x,
		-m_y,
		-m_z
	);
}

Quaternion Quaternion::GetInverse(bool* succed) const
{
	if (m_w == 0.f && m_x == 0.f && m_y == 0.f && m_z == 0.f)
	{
		if (succed)
			*succed = false;

		return *this;
	}

	if (succed)
		*succed = true;

	float modulusSQ{ MODULUS_SQ };

	return Quaternion(
		m_w / modulusSQ,
		-m_x / modulusSQ,
		-m_y / modulusSQ,
		-m_z / modulusSQ
	);
}

Mat4 Quaternion::GetRotationMatrix() const
{
	// Note : w*w + x*x + y*y + z*z = 1

	return Mat4(
		(m_w * m_w) + (m_x * m_x) - (m_y * m_y) - (m_z * m_z),
		2.f * ((m_x * m_y) - (m_w * m_z)),
		2.f * ((m_x * m_z) + (m_w * m_y)),
		0.f,

		2.f * ((m_x * m_y) + (m_w * m_z)),
		(m_w * m_w) - (m_x * m_x) + (m_y * m_y) - (m_z * m_z),
		2.f * ((m_y * m_z) - (m_w * m_x)),
		0.f,

		2.f * ((m_x * m_z) - (m_w * m_y)),
		2.f * ((m_y * m_z) + (m_w * m_x)),
		(m_w * m_w) - (m_x * m_x) - (m_y * m_y) + (m_z * m_z),
		0.f,

		0.f, 0.f, 0.f, 1.f
	);
}

void Quaternion::RotateVertex(Vec3& vertex) const
{
	// vertex = (*this * Quaternion(0.f, vec) * GetConjugate()).GetVectorPart();

	float qp_w{ -(m_x * vertex.m_x) - (m_y * vertex.m_y) - (m_z * vertex.m_z) };
	float qp_x{ (m_w * vertex.m_x) + (m_y * vertex.m_z) - (m_z * vertex.m_y) };
	float qp_y{ (m_w * vertex.m_y) - (m_x * vertex.m_z) + (m_z * vertex.m_x) };
	float qp_z{ (m_w * vertex.m_z) + (m_x * vertex.m_y) - (m_y * vertex.m_x) };

	vertex.m_x = (qp_w * -m_x) + (qp_x * m_w) + (qp_y * -m_z) - (qp_z * -m_y);
	vertex.m_y = (qp_w * -m_y) - (qp_x * -m_z) + (qp_y * m_w) + (qp_z * -m_x);
	vertex.m_z = (qp_w * -m_z) + (qp_x * -m_y) - (qp_y * -m_x) + (qp_z * m_w);
}

Vec3 Quaternion::GetRotatedVertex(const Vec3& vertex) const
{
	// return (*this * Quaternion(0.f, vec) * GetConjugate()).GetVectorPart();

	float qp_w{ -(m_x * vertex.m_x) - (m_y * vertex.m_y) - (m_z * vertex.m_z) };
	float qp_x{ (m_w * vertex.m_x) + (m_y * vertex.m_z) - (m_z * vertex.m_y) };
	float qp_y{ (m_w * vertex.m_y) - (m_x * vertex.m_z) + (m_z * vertex.m_x) };
	float qp_z{ (m_w * vertex.m_z) + (m_x * vertex.m_y) - (m_y * vertex.m_x) };

	return Vec3(
		(qp_w * -m_x) + (qp_x * m_w) + (qp_y * -m_z) - (qp_z * -m_y),
		(qp_w * -m_y) - (qp_x * -m_z) + (qp_y * m_w) + (qp_z * -m_x),
		(qp_w * -m_z) + (qp_x * -m_y) - (qp_y * -m_x) + (qp_z * m_w)
	);
}

float Quaternion::DotProduct(const Quaternion& quat) const
{
	return DOT_PRODUCT_WITH(quat);
}
#pragma endregion

#pragma region External operators
std::ostream& engine::core::maths::operator<<(std::ostream& stream, const Quaternion& quat)
{
	std::cout << std::setprecision(2) << std::fixed;
	stream << std::defaultfloat << "Quat : ( " << quat.m_w << " ; " << quat.m_x << " ; " << quat.m_y << " ; " << quat.m_z << " )";
	std::cout << std::setprecision(0) << std::defaultfloat;

	return stream;
}

Quaternion engine::core::maths::operator+(float scalar, const Quaternion& quat)
{
	return Quaternion(
		quat.m_w + scalar,
		quat.m_x,
		quat.m_y,
		quat.m_z
	);
}

Quaternion engine::core::maths::operator-(float scalar, const Quaternion& quat)
{
	return Quaternion(
		quat.m_w - scalar,
		quat.m_x,
		quat.m_y,
		quat.m_z
	);
}

Quaternion engine::core::maths::operator*(float scalar, const Quaternion& quat)
{
	return Quaternion(
		quat.m_w * scalar,
		quat.m_x * scalar,
		quat.m_y * scalar,
		quat.m_z * scalar
	);
}

Quaternion engine::core::maths::operator/(float scalar, const Quaternion& quat)
{
	return Quaternion(
		scalar / quat.m_w,
		scalar / quat.m_x,
		scalar / quat.m_y,
		scalar / quat.m_z
	);
}
#pragma endregion
