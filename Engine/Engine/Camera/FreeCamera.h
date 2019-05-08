#ifndef _FREE_CAMERA_H_
#define _FREE_CAMERA_H_

#include "Camera.h"

namespace engine
{
	namespace camera
	{
		class FreeCamera : public Camera
		{
		public:
			FreeCamera(float width, float height, float _near, float _far, float fov, engine::core::maths::Vec3 pos, engine::core::maths::Vec3 target, float speed, float sensitivity);
			~FreeCamera();

			void MoveForward(float deltaTime);
			void MoveBackward(float deltaTime);
			void MoveRight(float deltaTime);
			void MoveLeft(float deltaTime);
			void MoveUp(float deltaTime);
			void MoveDown(float deltaTime);

			void MoveTarget(engine::core::maths::Vec2 offset, float deltaTime);


		private:
			float m_speed;
			float m_sensitivity;
			float m_yaw;
			float m_pitch;

		};
	}
}

#endif // !_FREE_CAMERA_H_

