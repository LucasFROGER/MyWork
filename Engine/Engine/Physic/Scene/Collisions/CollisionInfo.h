#ifndef _COLLISION_INFO_H_
#define _COLLISION_INFO_H_

namespace engine
{
	namespace scene_graph { class GameObject; }
	namespace physic
	{
		class Object;

		struct CollisionInfo
		{
			CollisionInfo(Object* other);
			engine::scene_graph::GameObject* m_otherObject;
		};
	}
}


#endif // !_COLLISION_INFO_H_
