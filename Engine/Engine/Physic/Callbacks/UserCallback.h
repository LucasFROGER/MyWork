#ifndef _USER_CALLBACK_H_
#define _USER_CALLBACK_H_

#include "foundation/PxErrorCallback.h"

namespace engine 
{
	namespace physic
	{
		class UserErrorCallback : public physx::PxErrorCallback
		{
		public:
			virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
			{
				const char* errorCode = NULL;
				switch (code)
				{
				case physx::PxErrorCode::eINVALID_PARAMETER:
					errorCode = "invalid parameter";
					break;
				case physx::PxErrorCode::eINVALID_OPERATION:
 					errorCode = "invalid operation";
					break;
				case physx::PxErrorCode::eOUT_OF_MEMORY:
					errorCode = "out of memory";
					break;
				case physx::PxErrorCode::eDEBUG_INFO:
					errorCode = "info";
					break;
				case physx::PxErrorCode::eDEBUG_WARNING:
					errorCode = "warning";
					break;
				default:
					errorCode = "unknown error";
					break;
				}
			}
		};
	}
}

#endif