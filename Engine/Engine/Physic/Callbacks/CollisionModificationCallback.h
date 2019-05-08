#ifndef _COLLISION_MODIFICATION_CALLBACK_H_
#define _COLLISION_MODIFICATION_CALLBACK_H_

#include "PxContactModifyCallback.h"

namespace engine
{
	namespace physic
	{
		class Object;
		namespace component { class ACollider; }

		class CollisionModificationCallback : public physx::PxContactModifyCallback
		{
		public:

		private:
			void onContactModify(physx::PxContactModifyPair* const pairs, physx::PxU32 count);
			void TriggerCollision(physx::PxContactSet set, engine::physic::Object* trigger, engine::physic::Object* other, component::ACollider* otherColl);
			void SolidCollision(physx::PxContactSet set, engine::physic::Object* trigger, engine::physic::Object* other);
		};
	}
}

#endif