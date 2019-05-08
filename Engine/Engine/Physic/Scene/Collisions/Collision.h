#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "../../Object/Object.h"


namespace engine
{
	namespace physic
	{
		class Collision
		{
		public:
			Collision(Object* Collision, Object* other);
			~Collision();

			void Update();
			bool Contain(Object* obj);
			bool Check(Object* Collision, Object* other);
			void Call();
			bool Exit();
		private:
			bool m_isEntered;
			bool m_isExited;
			bool m_isCalled;
			Object* m_collision;
			Object* m_other;
		};
	}
}

#endif // !_Collision_H_

