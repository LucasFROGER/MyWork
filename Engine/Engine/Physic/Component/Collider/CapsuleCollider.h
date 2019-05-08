#ifndef _CAPSULE_COLLIDER_H_
#define _CAPSULE_COLLIDER_H_

#include "Collider.h"

namespace engine
{
	namespace physic
	{
		namespace component
		{
			class CapsuleCollider final : public ACollider
			{
			public:
				CapsuleCollider() = delete;
				CapsuleCollider(physx::PxRigidActor* actor, PhysicMgr* physicMgr, bool trigger,
					Transform* objectTransform, physx::PxMaterial& mat);
				~CapsuleCollider();

				void Update();
				void SetDimensions(float halfRadius, float radius);

				float GetHalfRadius() const;
				float GetRadius() const;

			private:
				float m_halfRadius;
				float m_radius;


				void BuildShape();
			};
		}
	}
}

#endif // !_CAPSULE_COLLIDER_H_

