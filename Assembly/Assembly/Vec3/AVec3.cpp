#include "AVec3.h"

AVec3::AVec3() : Vec3()
{

}

AVec3::AVec3(int value) : Vec3(value)
{

}

AVec3::AVec3(int _x, int _y, int _z) : Vec3(_x, _y, _z)
{

}

AVec3::~AVec3()
{
}

AVec3 AVec3::operator+(AVec3 vec)
{
	return vec3add(AVec3(x, y, z), vec);
}

AVec3 AVec3::operator-(AVec3 vec)
{ 
	return vec3sub(AVec3(x, y, z), vec);
}

AVec3 AVec3::operator*(AVec3 vec)
{
	return vec3mul(AVec3(x, y, z), vec);
}

AVec3 AVec3::operator/(AVec3 vec)
{
	return vec3div(AVec3(x, y, z), vec);
}

	AVec3 AVec3::operator+=(AVec3 vec)
	{
		return vec3setadd(this, vec);
	}

AVec3 AVec3::operator-=(AVec3 vec)
{
	vec3setsub(this, vec);
	return *this;
}

	AVec3 AVec3::operator*=(AVec3 vec)
	{
		return vec3setmul(this, vec);
	}

AVec3 AVec3::operator/=(AVec3 vec)
{
	vec3setdiv(this, vec);
	return *this;
}

int AVec3::DotProduct(AVec3 vec)
{
	return vec3dotproduct(*this, vec);
}

AVec3 AVec3::CrossProduct(AVec3 vec)
{
	return vec3crossproduct(*this, vec);
}

std::ostream& operator<<(std::ostream& os, const AVec3& vec)
{
	os << '[' << vec.x << ',' << vec.y << ',' << vec.z << ']';
	return os;
}