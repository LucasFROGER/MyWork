#ifndef _TRIGGER_INFO_H_
#define _TRIGGER_INFO_H_

namespace engine
{
	namespace scene_graph { class GameObject; }
	namespace physic
	{
		class Object;

		struct TriggerInfo
		{
			TriggerInfo(Object* other);
			engine::scene_graph::GameObject* m_otherObject;
		};
	}
}

#endif // !_TRIGGER_INFO_H_
