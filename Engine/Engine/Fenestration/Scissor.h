#ifndef _SCISSOR_H_
#define _SCISSOR_H_

#include "../Core/Maths/Vector/Vec2.h"


namespace engine
{
	namespace fenestration
	{
		struct Scissor
		{
			engine::core::maths::Vec2 m_leftCorner;
			int m_height, m_width;

			Scissor(engine::core::maths::Vec2 leftCorner, int height, int width) :
				m_leftCorner{ leftCorner },
				m_height{ height }, m_width{ width }
			{}
		};
	}
}

#endif