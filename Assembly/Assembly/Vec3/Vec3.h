#pragma once

#include <iostream>

struct Vec3
{
	int x;
	int y;
	int z;

	Vec3();
	Vec3(int value);
	Vec3(int _x, int _y, int _z);
	~Vec3();
};

std::ostream& operator<<(std::ostream& os, const Vec3& vec);