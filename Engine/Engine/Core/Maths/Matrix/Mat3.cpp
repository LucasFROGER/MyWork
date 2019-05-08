#include "Mat3.h"

using namespace oe_math;

Mat3::Mat3()
{
	for (int i{ 0 }; i < 3; ++i)
	{
		for (int j{ 0 }; j < 3; ++j)
			m_mat[i][j] = 0.f;

		m_mat[i][i] = 1.f;
	}
}

Mat3::Mat3(const Mat3& mat)
{
	for (int i{ 0 }; i < 3; ++i)
		for (int j{ 0 }; j < 3; ++j)
			m_mat[i][j] = mat.m_mat[i][j];
}

Mat3::~Mat3()
{

}

float* const Mat3::operator[](int index)
{
	return m_mat[index];
}
