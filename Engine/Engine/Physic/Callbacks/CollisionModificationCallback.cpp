#include "CollisionModificationCallback.h"

#include "../Scene/Scene.h"
#include "../Object/Object.h"
#include "../../SceneGraph/GameObject.h"
#include "../Utils/ConvertionHandler.h"
#include <iostream>

void engine::physic::CollisionModificationCallback::onContactModify(physx::PxContactModifyPair* const pairs, physx::PxU32 count)
{
	for (physx::PxU32 i = 0; i < count; i++)
	{
		physx::PxContactModifyPair& pair = pairs[i];
		physx::PxContactSet set = pair.contacts;

		const physx::PxShape* shape1 = pair.shape[0];
		component::ACollider* coll1 = reinterpret_cast<component::ACollider*>(shape1->userData);

		const physx::PxShape* shape2 = pair.shape[1];
		component::ACollider* coll2 = reinterpret_cast<component::ACollider*>(shape2->userData);

		const physx::PxRigidActor* actor1 = pair.actor[0];
		engine::physic::Object* obj1 = reinterpret_cast<engine::physic::Object*>(actor1->userData);

		const physx::PxRigidActor* actor2 = pair.actor[1];
		engine::physic::Object* obj2 = reinterpret_cast<engine::physic::Object*>(actor2->userData);



		if (coll1->IsTrigger())
		{
			TriggerCollision(set, obj1, obj2, coll2);			
		}
		else if (coll2->IsTrigger())
		{
			TriggerCollision(set, obj2, obj1, coll1);
		}
		else if ((obj1->HasRigidbody() && (obj2->IsStatic() || !obj2->HasRigidbody())))
		{
			SolidCollision(set, obj1, obj2);
		}
		else if ((obj1->IsStatic() || !obj1->HasRigidbody()) && obj2->HasRigidbody())
		{
			SolidCollision(set, obj2, obj1);
		}
		else if (obj1->HasRigidbody() && obj2->HasRigidbody())
		{
			for (physx::PxU32 j = 0; j < set.size(); j++)
			{
				if (ConvertionHandler::PhysxToEngine(set.getNormal(j)).GetNormalized() == -obj1->GetScene()->GetGravity().GetNormalized())
				{

					if (obj1->IsLanding())
						obj2->SetIsLanding(true);
					else if (obj2->IsLanding())
						obj1->SetIsLanding(true);
				}
			}

			obj2->GetScene()->GetCollisionMgr()->ObjectsCollision(obj1, obj2);
			obj2->GetScene()->GetCollisionMgr()->ObjectsCollision(obj2, obj1);

			obj1->Stop();
			obj2->Stop();
		}
		else if (!obj1->HasRigidbody() && !obj2->HasRigidbody())
		{
			if (obj1->GetGameObject()->GetName() == "Player" || obj2->GetGameObject()->GetName() == "Player")
				std::cout << "else if (!obj1->HasRigidbody() && !obj2->HasRigidbody())" << std::endl;

			for (physx::PxU32 j = 0; j < set.size(); j++)
			{
				set.ignore(j);
			}
		}

	}
}

void engine::physic::CollisionModificationCallback::TriggerCollision(physx::PxContactSet set, engine::physic::Object* trigger, engine::physic::Object* other, component::ACollider* otherColl)
{
	for (physx::PxU32 j = 0; j < set.size(); j++)
	{
		set.ignore(j);
	}
	if (other->HasRigidbody() && !otherColl->IsTrigger())
		trigger->GetScene()->GetCollisionMgr()->ObjectsTrigger(trigger, other);
}

void engine::physic::CollisionModificationCallback::SolidCollision(physx::PxContactSet set, engine::physic::Object* collision, engine::physic::Object* other)
{
	set.setInvMassScale1(0);
	set.setInvInertiaScale0(0); 
	for (physx::PxU32 j = 0; j < set.size(); j++)
	{
		set.setRestitution(j, 0);
		if (ConvertionHandler::PhysxToEngine(set.getNormal(j)).GetNormalized() == -collision->GetScene()->GetGravity().GetNormalized())
			collision->SetIsLanding(true);
	}
	
	other->GetScene()->GetCollisionMgr()->ObjectsCollision(other, collision);

	collision->Stop();
	other->Stop();
}
