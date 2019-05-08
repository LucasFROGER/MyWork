#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Core/Maths/Matrix/Mat4.h"
#include "../Core/Maths/Vector/Vec4.h"
#include "../Core/Maths/Vector/Vec3.h"
#include "../Core/Maths/Vector/Vec2.h"

namespace engine
{
	namespace camera
	{
		enum class EProjectType
		{
			PERSPECTIVE,
			ORTHOGRAPHIC
		};

		class Camera
		{
		public:
			Camera(EProjectType type, float width, float height, float _near, float _far, float fov, engine::core::maths::Vec3 pos, engine::core::maths::Vec3 target);
			~Camera();

			EProjectType GetType() const;
			engine::core::maths::Mat4 GetViewMat() const;
			engine::core::maths::Mat4 GetProjectMat() const;
			engine::core::maths::Vec3 GetTarget() const;
			engine::core::maths::Vec3 GetPosition() const;
			engine::core::maths::Vec3 GetForward() const;
			engine::core::maths::Vec3 GetRight() const;
			engine::core::maths::Vec3 GetUp() const;

			void SetType(EProjectType type);
			void SetFov(float fov);
			void SetViewSize(float width, float height, float _near, float _far);
			void SetPosition(engine::core::maths::Vec3 position);
			void SetTarget(engine::core::maths::Vec3 target);

			void Check(); // breakpoint debug camera
		protected:
			EProjectType m_type;

			float m_viewWidth;
			float m_viewHeight;
			float m_fov;
			float m_near;
			float m_far;

			engine::core::maths::Vec3 m_position;
			engine::core::maths::Vec3 m_target;

			engine::core::maths::Vec3 m_right;
			engine::core::maths::Vec3 m_up;
			engine::core::maths::Vec3 m_forward;

			engine::core::maths::Mat4 m_viewMat;
			engine::core::maths::Mat4 m_projectMat;

			void InitProjectionMat();
			void LookAt();
		};
	}
}
#endif