#include "SceneEventCallback.h"
#include "PxPhysicsAPI.h"
#include "../Object/Object.h"
#include "../Scene/Scene.h"

void engine::physic::SceneCallbackEvent::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32  	count)
{

}

void engine::physic::SceneCallbackEvent::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count)
{

}

void engine::physic::SceneCallbackEvent::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{

}

void engine::physic::SceneCallbackEvent::onSleep(physx::PxActor** actors, physx::PxU32 count)
{

}

void engine::physic::SceneCallbackEvent::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{

}

void engine::physic::SceneCallbackEvent::onWake(physx::PxActor** actors, physx::PxU32 count)
{

}

physx::PxFilterFlags engine::physic::SceneCallbackEvent::SampleFilterShader(physx::PxFilterObjectAttributes attributes0, 
	physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, 
	physx::PxPairFlags & pairFlags, const void * constantBlock, physx::PxU32 constantBlockSize)
{
	// let triggers through
	if (physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	// generate contacts for all that were not filtered above
	pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT | physx::PxPairFlag::eMODIFY_CONTACTS;

	// trigger the contact callback for pairs (A,B) where
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return physx::PxFilterFlag::eDEFAULT;
}