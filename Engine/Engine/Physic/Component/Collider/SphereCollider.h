#ifndef _SPHERE_COLLIDER_H_
#define _SPHERE_COLLIDER_H_

#include "Collider.h"

namespace engine
{
	namespace physic
	{
		namespace component
		{
			class SphereCollider final : public ACollider
			{
			public:
				SphereCollider() = delete;
				SphereCollider(physx::PxRigidActor* actor, PhysicMgr* physicMgr, bool trigger,
					Transform* objectTransform, physx::PxMaterial& mat);
				~SphereCollider();

				void Update();
				void SetRadius(float radius);
				float GetRadius() const;

			private:
				float m_radius;


				void BuildShape();
			};
		}
	}
}


#endif // !_SPHERE_COLLIDER_H_
