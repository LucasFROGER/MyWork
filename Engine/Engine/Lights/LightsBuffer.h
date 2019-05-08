#ifndef _LIGHTS_BUFFER_H_
#define _LIGHTS_BUFFER_H_

#define MAX_LIGHT_COUNT 5

#include "Light.h"
#include "../Core/Maths/Vector/Vec4.h"

namespace engine
{
	namespace light
	{
		struct LightsBuffer
		{
			engine::light::Light m_lights[MAX_LIGHT_COUNT];
			engine::core::maths::Vec4 m_ambientColor;
			bool m_sampleShadowMap;
			bool pad0[3];

			LightsBuffer(engine::core::maths::Vec4 ambient = { 1.f, 1.f, 1.f, 1.f }, bool sampleShadow = false) :
				m_ambientColor{ ambient },
				m_sampleShadowMap{ sampleShadow }
			{

			}

		};
	}
}

#endif // !_LIGHTS_BUFFER_H_

