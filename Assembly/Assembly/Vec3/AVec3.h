#pragma once

#include "Vec3.h"

struct AVec3 : public Vec3
{
	AVec3();
	AVec3(int value);
	AVec3(int _x, int _y, int _z);
	~AVec3();

	AVec3 operator+(AVec3 vec);
	AVec3 operator-(AVec3 vec);
	AVec3 operator*(AVec3 vec);
	AVec3 operator/(AVec3 vec);

	AVec3 operator+=(AVec3 vec);
	AVec3 operator-=(AVec3 vec);
	AVec3 operator*=(AVec3 vec);
	AVec3 operator/=(AVec3 vec);

	int DotProduct(AVec3 vec);
	AVec3 CrossProduct(AVec3 vec);
private:
};

std::ostream& operator<<(std::ostream& os, const AVec3& vec);

#ifdef __cplusplus
extern "C"
{
#endif //

	// int, int, int, int, int, int
	AVec3 vec3add(AVec3 vec1, AVec3 vec2);
	AVec3 vec3sub(AVec3 vec1, AVec3 vec2);
	AVec3 vec3mul(AVec3 vec1, AVec3 vec2);
	AVec3 vec3div(AVec3 vec1, AVec3 vec2);
	
	// ptr, int, int, int
	AVec3 vec3setadd(AVec3* vec1, AVec3 vec2);
	
	
	void vec3setsub(AVec3* vec1, AVec3 vec2);

	// ptr, int, int, int
	AVec3 vec3setmul(AVec3* vec1, AVec3 vec2);


	void vec3setdiv(AVec3* vec1, AVec3 vec2);

	int vec3dotproduct(AVec3 vec1, AVec3 vec2);
	AVec3 vec3crossproduct(AVec3 vec1, AVec3 vec2);
#ifdef __cplusplus
}
#endif*