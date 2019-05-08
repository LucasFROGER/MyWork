#include "PerformanceTest.h"

#include <iomanip>
#include <time.h>


PerformanceTest::PerformanceTest()
{
}

PerformanceTest::~PerformanceTest()
{
}

void PerformanceTest::Launch()
{
	run = true;
	std::cout << std::setprecision(7) << std::fixed;
	
	loopCount = 2;
	loopIteration = 1500;
	
	vecA = Vec3(1);
	vecB = Vec3(2);
	Loop();
}

void PerformanceTest::Loop()
{
	while (run)
	{
		system("cls");
		std::cout << "1) Change loop settings" << std::endl;
		std::cout << "2) Change test vec" << std::endl;
		std::cout << std::endl;
		std::cout << "11) int + int" << std::endl;
		std::cout << "12) int - int" << std::endl;
		std::cout << "13) int * int" << std::endl;
		std::cout << "14) int / int" << std::endl;
		std::cout << std::endl;
		std::cout << "21) Vec3 + Vec3" << std::endl;
		std::cout << "22) Vec3 += Vec3" << std::endl;
		std::cout << "23) Vec3 - Vec3" << std::endl;
		std::cout << "24) Vec3 -= Vec3" << std::endl;
		std::cout << "25) Vec3 * Vec3" << std::endl;
		std::cout << "26) Vec3 *= Vec3" << std::endl;
		std::cout << "27) Vec3 / Vec3" << std::endl;
		std::cout << "28) Vec3 /= Vec3" << std::endl;
		std::cout << std::endl;
		std::cout << "31) dotproduct" << std::endl;
		std::cout << "32) crossproduct" << std::endl;
		std::cout << std::endl;
		std::cout << "0) exit" << std::endl;

		int input{ 0 };
		std::cin >> input;
		switch (input)
		{
		case 0: run = false; break;

		case 1: ChangeLoopSettings(); break;
		case 2: ChangeVec(); break;

		case 11: Addition(); break;
		case 12: Substraction(); break;
		case 13: Multiplication(); break;
		case 14: Division(); break;

		case 21: Vec3Addition(); break;
		case 22: Vec3AddEqu(); break;
		case 23: Vec3Substraction(); break;
		case 24: Vec3SubEqu(); break;
		case 25: Vec3Multiplication(); break;
		case 26: Vec3MulEqu(); break;
		case 27: Vec3Division(); break;
		case 28: Vec3DivEqu(); break;

		case 31: CrossProduct(); break;
		case 32: DotProduct(); break;

		default: break;
		}
	}
}

void PerformanceTest::ChangeLoopSettings()
{
	system("cls");
	std::cout << "How many iteratrion per loop?" << std::endl; 
	std::cin >> loopIteration;
	std::cout << "How many loop will be execute" << std::endl;
	std::cin >> loopCount;

	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::ChangeVec()
{
	system("cls");
	std::cout << "VecA.x?" << std::endl;
	std::cin >> vecA.x;
	std::cout << "VecA.y?" << std::endl;
	std::cin >> vecA.y;
	std::cout << "VecA.z?" << std::endl;
	std::cin >> vecA.z;
	std::cout << "VecA: " << vecA << std::endl;
	std::cout << std::endl;
	std::cout << "vecB.x?" << std::endl;
	std::cin >> vecB.x;
	std::cout << "vecB.y?" << std::endl;
	std::cin >> vecB.y;
	std::cout << "vecB.z?" << std::endl;
	std::cin >> vecB.z;
	std::cout << "vecB: " << vecB << std::endl;
	std::cout << std::endl;

	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Addition()
{
	system("cls");
	std::cout << "[Addition]" << std::endl;
	std::cout << ">> A: " << vecA.x << std::endl;
	std::cout << ">> B: " << vecB.x << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			addition(vecA.x, vecB.x);
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA.x + vecB.x;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Substraction()
{
	system("cls");
	std::cout << "[Substraction]" << std::endl;
	std::cout << ">> A: " << vecA.x << std::endl;
	std::cout << ">> B: " << vecB.x << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			substraction(vecA.x, vecB.x);
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA.x - vecB.x;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Multiplication()
{
	system("cls");
	std::cout << "[Multiplication]" << std::endl;
	std::cout << ">> A: " << vecA.x << std::endl;
	std::cout << ">> B: " << vecB.x << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			multiplication(vecA.x, vecB.x);
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA.x * vecB.x;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Division()
{
	system("cls");
	std::cout << "[Division]" << std::endl;
	std::cout << ">> A: " << vecA.x << std::endl;
	std::cout << ">> B: " << vecB.x << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			division(vecA.x, vecB.x);
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA.x / vecB.x;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3Addition()
{
	system("cls");
	std::cout << "[Vec3Addition]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		AVec3 AvecA(vecA.x, vecA.y, vecA.z);
		AVec3 AvecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			AvecA + AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		CppVec3 vecA(vecA.x, vecA.y, vecA.z);
		CppVec3 vecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA + vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3Substraction()
{
	system("cls");
	std::cout << "[Vec3Substraction]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		AVec3 AvecA(vecA.x, vecA.y, vecA.z);
		AVec3 AvecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			AvecA - AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		CppVec3 vecA(vecA.x, vecA.y, vecA.z);
		CppVec3 vecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA - vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3Multiplication()
{
	system("cls");
	std::cout << "[Vec3Multiplication]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		AVec3 AvecA(vecA.x, vecA.y, vecA.z);
		AVec3 AvecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			AvecA * AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		CppVec3 vecA(vecA.x, vecA.y, vecA.z);
		CppVec3 vecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA * vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3Division()
{
	system("cls");
	std::cout << "[Vec3Division]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		AVec3 AvecA(vecA.x, vecA.y, vecA.z);
		AVec3 AvecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			AvecA / AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		CppVec3 vecA(vecA.x, vecA.y, vecA.z);
		CppVec3 vecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA / vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3AddEqu()
{
	system("cls");
	std::cout << "[Assign addition]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		for (size_t it = 0; it < loopIteration; it++)
		{
			AVec3 AvecA(vecA.x, vecA.y, vecA.z);
			AVec3 AvecB(vecB.x, vecB.y, vecB.z);
			AvecA += AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			CppVec3 vecA(vecA.x, vecA.y, vecA.z);
			CppVec3 vecB(vecB.x, vecB.y, vecB.z);
			vecA += vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3SubEqu()
{
	system("cls");
	std::cout << "[Assign substraction]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			AVec3 AvecA(vecA.x, vecA.y, vecA.z);
			AVec3 AvecB(vecB.x, vecB.y, vecB.z);
			AvecA -= AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			CppVec3 vecA(vecA.x, vecA.y, vecA.z);
			CppVec3 vecB(vecB.x, vecB.y, vecB.z);
			vecA -= vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3MulEqu()
{
	system("cls");
	std::cout << "[Assign multiplication]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			AVec3 AvecA(vecA.x, vecA.y, vecA.z);
			AVec3 AvecB(vecB.x, vecB.y, vecB.z);
			AvecA *= AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			CppVec3 vecA(vecA.x, vecA.y, vecA.z);
			CppVec3 vecB(vecB.x, vecB.y, vecB.z);
			vecA *= vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::Vec3DivEqu()
{
	system("cls");
	std::cout << "[Assign division]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			AVec3 AvecA(vecA.x, vecA.y, vecA.z);
			AVec3 AvecB(vecB.x, vecB.y, vecB.z);
			AvecA /= AvecB;
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		
		for (size_t it = 0; it < loopIteration; it++)
		{
			CppVec3 vecA(vecA.x, vecA.y, vecA.z);
			CppVec3 vecB(vecB.x, vecB.y, vecB.z);
			vecA /= vecB;
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::DotProduct()
{
	system("cls");
	std::cout << "[Dot product]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		AVec3 AvecA(vecA.x, vecA.y, vecA.z);
		AVec3 AvecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			AvecA.DotProduct(AvecB);
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		CppVec3 vecA(vecA.x, vecA.y, vecA.z);
		CppVec3 vecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA.DotProduct(vecB);
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	if(diff >= 0.000001)
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;
	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}

void PerformanceTest::CrossProduct()
{
	system("cls");
	std::cout << "[Cross product]" << std::endl;
	std::cout << ">> VecA: " << vecA << std::endl;
	std::cout << ">> VecB: " << vecB << std::endl;
	std::cout << ">> Loop count: " << loopCount << std::endl;
	std::cout << ">> Interation per loop: " << loopIteration << std::endl;
	std::cout << std::endl;

	std::cout << "Test start" << std::endl;

	std::clock_t begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		AVec3 AvecA(vecA.x, vecA.y, vecA.z);
		AVec3 AvecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			AvecA.CrossProduct(AvecB);
		}
	}
	clock_t end = clock();
	double assemblyTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Assembly completed!" << std::endl;

	begin = clock();
	for (size_t count = 0; count < loopCount; count++)
	{
		CppVec3 vecA(vecA.x, vecA.y, vecA.z);
		CppVec3 vecB(vecB.x, vecB.y, vecB.z);
		for (size_t it = 0; it < loopIteration; it++)
		{
			vecA.CrossProduct(vecB);
		}
	}
	end = clock();
	double cppTime = double(end - begin) / CLOCKS_PER_SEC / 1000;
	std::cout << "Cpp completed!" << std::endl;

	std::cout << std::endl;
	std::cout << "Assembly: " << assemblyTime << "ms" << std::endl;
	std::cout << "Cpp: " << cppTime << "ms" << std::endl;
	bool assemblyFaster = assemblyTime < cppTime;
	double diff = assemblyFaster ? cppTime - assemblyTime : assemblyTime - cppTime;
	std::cout << "You gain " << diff << "ms by using " << (assemblyFaster ? "assembly" : "cpp") << std::endl;

	int input{ -1 };
	std::cout << "Continue..." << std::endl;
	std::cin >> input;
}
