#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers.
#endif


#include <DirectXMath.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"
#include <string>

#include <vector>


// this will only call release if an object exists (prevents exceptions calling release on non existant objects)
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

#define SAFE_DELETE(p)\
if (p != nullptr)\
{\
	delete p;\
	p = nullptr;\
}

#define SAFE_DELETE_ARRAY(p)\
if (p != nullptr)\
{\
	delete[] p;\
	p = nullptr;\
}

#define SAFE_DELETE_VECTOR(v)\
if (v.size() > 0)\
{\
	for(unsigned int i { 0 }; i < v.size(); ++i)\
	{\
		SAFE_DELETE(v[i])\
	}\
}\
v.clear();

#define SAFE_DELETE_VECTOR_ARRAY(v)\
if (v.size() > 0)\
{\
	for(unsigned int i { 0 }; i < v.size(); ++i)\
	{\
		SAFE_DELETE_ARRAY(v[i])\
	}\
}\
v.clear();

#endif