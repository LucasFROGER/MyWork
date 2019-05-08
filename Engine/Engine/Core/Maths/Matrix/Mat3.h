#ifndef _MAT3_H_
#define _MAT3_H_

namespace oe_math
{
	struct Mat3
	{
		float m_mat[3][3];

		Mat3();
		Mat3(const Mat3& mat);
		~Mat3();

		float* const operator[](int index);
	};
}

#endif