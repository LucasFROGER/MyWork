#ifndef _PHYSIC_LIBRAIRY_LOADER_H_
#define _PHYSIC_LIBRAIRY_LOADER_H_

#ifndef _DEBUG
#define RELEASE
#endif

#ifndef CHECKED
#ifndef PROFILE
#ifndef RELEASE

#ifdef _DEBUG
#pragma comment(lib, "PhysX3DEBUG_x64.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x64.lib")
#pragma comment(lib, "PxFoundationDEBUG_x64.lib")
#pragma comment(lib, "PxPvdSDKDEBUG_x64.lib")
#pragma comment(lib, "PhysX3CookingDEBUG_x64.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#endif // DEBUG

#endif // !RELEASE
#endif // !PROFILE
#endif // !CHECKED

#ifndef _DEBUG
#ifndef PROFILE
#ifndef RELEASE

#ifdef CHECKED
#pragma comment(lib, "PhysX3CHECKED_x64.lib")
#pragma comment(lib, "PhysX3CommonCHECKED_x64.lib")
#pragma comment(lib, "PxFoundationCHECKED_x64.lib")
#pragma comment(lib, "PxPvdSDKCHECKED_x64.lib")
#pragma comment(lib, "PhysX3CookingCHECKED_x64.lib")
#endif // CHECKED

#endif // !RELEASE
#endif // !PROFILE
#endif // !DEBUG

#ifndef CHECKED
#ifndef _DEBUG
#ifndef RELEASE

#ifdef PROFILE
#pragma comment(lib, "PhysX3PROFILE_x64.lib")
#pragma comment(lib, "PhysX3CommonPROFILE_x64.lib")
#pragma comment(lib, "PxFoundationPROFILE_x64.lib")
#pragma comment(lib, "PxPvdSDKPROFILE_x64.lib")
#pragma comment(lib, "PhysX3CookingPROFILE_x64.lib")
#endif // PROFILE

#endif // !RELEASE
#endif // !DEBUG
#endif // !CHECKED

#ifndef CHECKED
#ifndef PROFILE
#ifndef _DEBUG

#ifdef RELEASE
#pragma comment(lib, "PhysX3_x64.lib")
#pragma comment(lib, "PhysX3Common_x64.lib")
#pragma comment(lib, "PxFoundation_x64.lib")
#pragma comment(lib, "PxPvdSDK_x64.lib")
#pragma comment(lib, "PhysX3Cooking_x64.lib")
#endif // RELEASE

#endif // !DEBUG
#endif // !PROFILE
#endif // !CHECKED

#endif
