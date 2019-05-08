#ifndef _DIRECTIONNAL_LIGHT_H_
#define _DIRECTIONNAL_LIGHT_H_

#include "Light.h"

namespace engine
{
	namespace light
	{
		class DirectionnalLight : public Light
		{
		public:
			DirectionnalLight(int id, engine::core::maths::Vec3 direction, engine::core::maths::Vec4 color, float intensity);
			DirectionnalLight(const DirectionnalLight& dirLight);
			~DirectionnalLight();

			engine::core::maths::Vec3 GetDirection() const;

			DirectionnalLight& operator=(const DirectionnalLight& other);

		private:

		};
	}
}

#endif