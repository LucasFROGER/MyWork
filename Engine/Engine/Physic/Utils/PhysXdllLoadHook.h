#ifndef _PHYSX_DLL_LOAD_HOOK_H_
#define _PHYSX_DLL_LOAD_HOOK_H_

#include "common/windows/PxWindowsDelayLoadHook.h"

namespace engine
{
	namespace physic
	{
		class SampleDelayLoadHook : public physx::PxDelayLoadHook
		{
			virtual const char* getPhysXCommonDEBUGDllName() const
			{
				return "PhysX3CommonDEBUG_x64.dll";
			}
			virtual const char* getPhysXCommonCHECKEDDllName() const
			{
				return "PhysX3CommonCHECKED_x64.dll";
			}
			virtual const char* getPhysXCommonPROFILEDllName() const
			{
				return "PhysX3CommonPROFILE_x64.dll";
			}
			virtual const char* getPhysXCommonDllName() const
			{
				return "PhysX3Common_x64.dll";
			}
			virtual const char* getPxFoundationDEBUGDllName() const
			{
				return "PxFoundationDEBUG_x64.dll";
			}
			virtual const char* getPxFoundationCHECKEDDllName() const
			{
				return "PxFoundationCHECKED_x64.dll";
			}
			virtual const char* getPxFoundationPROFILEDllName() const
			{
				return "PxFoundationPROFILE_x64.dll";
			}
			virtual const char* getPxFoundationDllName() const
			{
				return "PxFoundation_x64.dll";
			}
			virtual const char* getPxPvdSDKDEBUGDllName() const
			{
				return "PxPvdSDKDEBUG_x64.dll";
			}
			virtual const char* getPxPvdSDKCHECKEDDllName() const
			{
				return "PxPvdSDKCHECKED_x64.dll";
			}
			virtual const char* getPxPvdSDKPROFILEDllName() const
			{
				return "PxPvdSDKPROFILE_x64.dll";
			}
			virtual const char* getPxPvdSDKDllName() const
			{
				return "PxPvdSDK_x64.dll";
			}
		};
	}
}

#endif
