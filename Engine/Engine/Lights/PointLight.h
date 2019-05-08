#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Light.h"
namespace engine
{
	namespace light
	{
		class PointLight : public Light
		{
		public:
			PointLight(int id, engine::core::maths::Vec3 position, engine::core::maths::Vec4 color, float intensity);
			PointLight(const PointLight& pointLight);
			~PointLight();

			engine::core::maths::Vec3 GetPosition() const;

			PointLight& operator=(const PointLight& other);
		private:

		};
	}
}


#endif // !_POINT_LIGHT_H_