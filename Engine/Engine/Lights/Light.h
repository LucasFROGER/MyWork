#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../Core/Maths/Vector/Vec4.h"
#include "../Core/Maths/Matrix/Mat4.h"

namespace engine
{
	namespace light
	{
		class Light
		{
		public:
			Light();
			Light(const Light& other);
			~Light();

			void SetColor(engine::core::maths::Vec4 color);
			void SetIntensity(float intensity);
			void SetUnused();

			const int GetId() const;
			engine::core::maths::Vec4 GetColor() const;
			float GetIntensity() const;
			bool IsUsed() const;
			void SetLight(engine::core::maths::Vec3 light);

			Light& operator=(const Light& other);

		protected:
			Light(int id, engine::core::maths::Vec4 light, engine::core::maths::Vec4 color, float intensity);

			engine::core::maths::Vec4 m_lightVec;
			engine::core::maths::Vec4 m_color;
			float m_intensity;
			bool m_used;
			bool padBool[3]; // align bool to shader's bool: 1b -> 4b 
			int m_id; //use as a pad
			float pad0;
			engine::core::maths::Mat4 m_view;
			engine::core::maths::Mat4 m_projection;

			void SetView();
			void SetProjection();

			engine::core::maths::Vec4 GetLightVec() const;
		};
	}
}

#endif