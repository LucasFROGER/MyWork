#include "CppVec3.h"

CppVec3::CppVec3() : Vec3()
{

}

CppVec3::CppVec3(int value) : Vec3(value)
{

}

CppVec3::CppVec3(int _x, int _y, int _z) : Vec3(_x, _y, _z)
{

}

CppVec3::~CppVec3()
{
}

CppVec3 CppVec3::operator+(CppVec3 vec)
{
	return CppVec3(x + vec.x, y + vec.y, z + vec.z);
}

CppVec3 CppVec3::operator-(CppVec3 vec)
{
	return CppVec3(x - vec.x, y - vec.y, z - vec.z);
}

CppVec3 CppVec3::operator*(CppVec3 vec)
{
	return CppVec3(x * vec.x, y * vec.y, z * vec.z);
}

CppVec3 CppVec3::operator/(CppVec3 vec)
{
	return CppVec3(x / vec.x, y / vec.y, z / vec.z);
}

CppVec3 CppVec3::operator+=(CppVec3 vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

CppVec3 CppVec3::operator-=(CppVec3 vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

CppVec3 CppVec3::operator*=(CppVec3 vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

CppVec3 CppVec3::operator/=(CppVec3 vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

int CppVec3::DotProduct(CppVec3 vec)
{
	return ((x * vec.x) + (y * vec.y) + (z * vec.z));
}

CppVec3 CppVec3::CrossProduct(CppVec3 vec)
{
	return CppVec3((y * vec.z) - (z * vec.y),
		 (z * vec.x) - (x * vec.z),
		 (x * vec.y) - (y * vec.x));
}

std::ostream& operator<<(std::ostream& os, const CppVec3& vec)
{
	os << '[' << vec.x << ',' << vec.y << ',' << vec.z << ']';
	return os;
}