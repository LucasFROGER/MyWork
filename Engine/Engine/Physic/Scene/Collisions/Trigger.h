#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include "../../Object/Object.h"


namespace engine
{
	namespace physic
	{
		class Trigger
		{
		public:
			Trigger(Object* trigger, Object* other);
			~Trigger();

			void Update();
			bool Contain(Object* obj);
			bool Check(Object* trigger, Object* other);
			void Call();
			bool Exit();
		private:
			bool m_isEntered;
			bool m_isExited;
			bool m_isCalled;
			Object* m_trigger;
			Object* m_other;
		};
	}
}

#endif // !_TRIGGER_H_

