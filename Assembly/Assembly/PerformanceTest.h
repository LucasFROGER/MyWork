#pragma once

#include "Math.h"
#include "Test.h"
#include "Vec3/AVec3.h"
#include "Vec3/CppVec3.h"

class PerformanceTest
{
public:
	PerformanceTest();
	~PerformanceTest();

	void Launch();


private:
	void Loop();

	void ChangeLoopSettings();
	void ChangeVec();


	void Addition();
	void Substraction();
	void Multiplication();
	void Division();

	void Vec3Addition();
	void Vec3Substraction();
	void Vec3Multiplication();
	void Vec3Division();
	void Vec3AddEqu();
	void Vec3SubEqu();
	void Vec3MulEqu();
	void Vec3DivEqu();
	void DotProduct();
	void CrossProduct();
	
	Vec3 vecA;
	Vec3 vecB;


	bool run;
	size_t loopCount;
	size_t loopIteration;
};