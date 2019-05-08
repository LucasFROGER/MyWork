#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "PxPhysicsAPI.h"
#include "../../Transform/Transform.h"
#include "ColliderType.h"

namespace engine
{
	namespace physic
	{
		class Scene;
		class PhysicMgr;
		namespace component
		{
			class ACollider
			{
			public:
				ACollider() = delete;
				virtual ~ACollider();

				virtual void Update() = 0;
				void SetTrigger(bool trigger);
				void SetRelativePos(engine::core::maths::Vec3 relativePos);
				void SetRelativeRot(engine::core::maths::Vec3 relativeRot);

				void ChangeActor(physx::PxRigidActor* actor);

				bool IsTrigger() const;
				ECollType GetType() const;
				engine::core::maths::Vec3 GetRelativePos() const;
				engine::core::maths::Quaternion GetRelativeRot() const;

			protected:
				ACollider(PhysicMgr* physicMgr, bool trigger,
					Transform* objectTransform, ECollType type, physx::PxMaterial& mat);
			
				engine::core::maths::Vec3 m_relativePos;
				engine::core::maths::Quaternion m_relativeRot;
				Transform* m_objectTransform;
				physx::PxRigidActor* m_actor;
				physx::PxMaterial& m_material;
				ECollType m_type;

				bool m_trigger;
				physx::PxShape* m_shape;
				
				void SetTriggerFlag();
			private:

			};
		}
	}
}

#endif