#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "PxPhysicsAPI.h"
#include "../../Core/Maths/Vector/Vec3.h"
#include "../Transform/Transform.h"
#include "../../Core/Maths/Quaternion.h"

namespace engine
{
	namespace physic
	{
		namespace component
		{
			class Rigidbody
			{
			public:
				Rigidbody() = delete;
				Rigidbody(physx::PxRigidDynamic* rigidbody, engine::physic::Transform* transform);
				~Rigidbody();

				void Move(float deltaTime);
				void Result();
				void Exit();

				void SetUseGravity(bool useGravity);
				void SetPositionConstraint(bool x, bool y, bool z);
				void SetRotationConstraint(bool x, bool y, bool z);

				bool IsUsingGravity() const;
			private:
				bool m_useGravity;
				engine::core::maths::Vec3 m_position;
				engine::core::maths::Vec3 m_rotation;

				engine::core::maths::Vec3 m_positionConstraints;
				engine::core::maths::Vec3 m_rotationConstraints;

				engine::physic::Transform* m_transform;
				physx::PxRigidDynamic* m_rigidbody;
			
				void UpdateLockFlag();
			};
		}
	}
}

#endif