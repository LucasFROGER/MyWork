#include "Vec3.h"

Vec3::Vec3() : x{ 0 }, y{ 0 }, z{ 0 }
{

}

Vec3::Vec3(int value) : x{ value }, y{ value }, z{ value }
{

}

Vec3::Vec3(int _x, int _y, int _z) : x{ _x }, y{ _y }, z{ _z }
{

}

Vec3::~Vec3()
{

}

std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
	os << '[' << vec.x << ',' << vec.y << ',' << vec.z << ']';
	return os;
}