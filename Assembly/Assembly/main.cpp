#include <iostream>

#include "PerformanceTest.h"




void MathTest()
{
	int a = 20;
	int b = 4;

	int add = addition(a, b);
	int sub = substraction(a, b);
	int mult = multiplication(a, b);
	int div = division(a, b);
	
	
	{
		AVec3 vecA(8, 6, 4);
		AVec3 vecB(2, 3, 6);

		AVec3 resultA = vecA + vecB;
		AVec3 resultB = vecA - vecB;
		AVec3 resultC = vecA * vecB;
		AVec3 resultD = vecA / vecB;


		AVec3 vec1(8, 6, 4);
		AVec3 vec2(8, 6, 4);
		AVec3 vec3(8, 6, 4);
		AVec3 vec4(8, 6, 4);

		vec1 += vecB;
		vec2 -= vecB;
		vec3 *= vecB;
		vec4 /= vecB;

		AVec3 dot1(1, 2, 1);
		AVec3 dot2(2, 2, 2);

		int dotProd1 = dot1.DotProduct(dot1);
		int dotProd2 = dot1.DotProduct(dot2);

		int dotProd3 = dot2.DotProduct(dot1);
		int dotProd4 = dot2.DotProduct(dot2);

		AVec3 cross1(3, 6, 18);
		AVec3 cross2(2, 9, 5);

		AVec3 crossProd1 = cross1.CrossProduct(cross1);
		AVec3 crossProd2 = cross1.CrossProduct(cross2);

		AVec3 crossProd3 = cross2.CrossProduct(cross1);
		AVec3 crossProd4 = cross2.CrossProduct(cross2);
	}
	{
		CppVec3 vecA(8, 6, 4);
		CppVec3 vecB(2, 3, 6);

		CppVec3 resultA = vecA + vecB;
		CppVec3 resultB = vecA - vecB;
		CppVec3 resultC = vecA * vecB;
		CppVec3 resultD = vecA / vecB;


		CppVec3 vec1(8, 6, 4);
		CppVec3 vec2(8, 6, 4);
		CppVec3 vec3(8, 6, 4);
		CppVec3 vec4(8, 6, 4);

		vec1 += vecB;
		vec2 -= vecB;
		vec3 *= vecB;
		vec4 /= vecB;

		CppVec3 dot1(1, 2, 1);
		CppVec3 dot2(2, 2, 2);

		int dotProd1 = dot1.DotProduct(dot1);
		int dotProd2 = dot1.DotProduct(dot2);

		int dotProd3 = dot2.DotProduct(dot1);
		int dotProd4 = dot2.DotProduct(dot2);

		CppVec3 cross1(3, 6, 18);
		CppVec3 cross2(2, 9, 5);

		CppVec3 crossProd1 = cross1.CrossProduct(cross1);
		CppVec3 crossProd2 = cross1.CrossProduct(cross2);

		CppVec3 crossProd3 = cross2.CrossProduct(cross1);
		CppVec3 crossProd4 = cross2.CrossProduct(cross2);
	}
}

void FunctionsTest()
{
	int a = returnint();
	pair pA = returnpair();
	int b = addpairvalues(pair(1, 3));
	int c = addpairsvalues(pair(1, 3), pair(4, 6));

	Vec4 vec4 = combinepairs(pair(1, 3), pair(4, 6));

	pair pa = addpair(pair(1, 2), pair(8, 6));

	int intA{ 1 };
	changeint(&intA);

	Vec4 vec4A{ 1,1,1,1 };

	changevec4(&vec4A);
}

void CppAssemblyCompare()
{
	PerformanceTest test;
	test.Launch();
}

int main()
{
	int a = 3;
	int b = 2;

	//FunctionsTest();
	MathTest();

	CppAssemblyCompare();

	//int i;
	//std::cin >> i;

	return 0;
}