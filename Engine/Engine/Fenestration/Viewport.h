#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "../Core/Maths/Vector/Vec2.h"

namespace engine
{
	namespace fenestration
	{
		struct Viewport
		{
			engine::core::maths::Vec2 m_leftCorner;
			int m_height, m_width;
			float m_minDepth, m_maxDepth;
			Viewport(engine::core::maths::Vec2 leftCorner, int height, int width, float minDepth, float maxDepth) :
				m_leftCorner{ leftCorner },
				m_height{ height }, m_width{ width },
				m_minDepth{ minDepth }, m_maxDepth{maxDepth}
			{	}
		};
	}
}



#endif