#ifndef _SCENE_CALLBACK_EVENT_H_
#define _SCENE_CALLBACK_EVENT_H_

#include "PxSimulationEventCallback.h"

namespace engine
{
	namespace physic
	{
		struct SceneCallbackEvent: public physx::PxSimulationEventCallback
		{
			virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32  count);
			virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count);
			virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs);
			virtual void onSleep(physx::PxActor** actors, physx::PxU32 count);
			virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count);
			virtual void onWake(physx::PxActor** actors, physx::PxU32 count);
		
			static physx::PxFilterFlags SampleFilterShader(
				physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
				physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
				physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize);
		};
	}
}



#endif