#pragma once

	struct pair
	{
		int a;
		int b;
		pair(int val) : a{ val }, b{ val }{}
		pair(int _a, int _b) : a{ _a }, b{ _b }{}
	};

struct Vec4
{
	int x;
	int y;
	int z;
	int w;
	Vec4(int val) : x{ val }, y{ val }, z{ val }, w{ val }{}
	Vec4(int a, int b, int c, int d) : x{ a }, y{ b }, z{ c }, w{ d }{}
};

#ifdef __cplusplus
extern "C"
{
#endif // 
	// test returning value
	int returnint();
	// test using parameters 
	int addpairvalues(pair p);
	int addpairsvalues(pair p1, pair p2);
	// test returning struct
	pair returnpair();
	// check parameter order
	Vec4 combinepairs(pair p1, pair p2);
	// test using parameters to return struct
	pair addpair(pair p1, pair p2);

	// changing parameter value
	void changeint(int* i);
	// changing struct value
	void changevec4(Vec4* vec4);


#ifdef __cplusplus
}
#endif
