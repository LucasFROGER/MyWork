#ifndef _COLLISION_MGR_H_
#define _COLLISION_MGR_H_

#include <vector>

#include "Trigger.h"
#include "Collision.h"

namespace engine
{
	namespace physic
	{
		class CollisionMgr
		{
		public:
			CollisionMgr();

			void Update();
			void FixedUpdate();

			void ObjectsTrigger(Object* trigger, Object* other);
			void ObjectsCollision(Object* collision, Object* other);

			void RemoveObject(Object* obj);
		private:
			std::vector<Collision> m_collisions;
			std::vector<Trigger> m_triggers;

		};
	}
}

#endif
