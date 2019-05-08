#pragma once

#include "Vec3.h"

#include <iostream>

struct CppVec3 : public Vec3
{
	CppVec3();
	CppVec3(int value);
	CppVec3(int _x, int _y, int _z);
	~CppVec3();

	CppVec3 operator+(CppVec3 vec);
	CppVec3 operator-(CppVec3 vec);
	CppVec3 operator*(CppVec3 vec);
	CppVec3 operator/(CppVec3 vec);

	CppVec3 operator+=(CppVec3 vec);
	CppVec3 operator-=(CppVec3 vec);
	CppVec3 operator*=(CppVec3 vec);
	CppVec3 operator/=(CppVec3 vec);

	int DotProduct(CppVec3 vec);
	CppVec3 CrossProduct(CppVec3 vec);
};

std::ostream& operator<<(std::ostream& os, const CppVec3& vec);
