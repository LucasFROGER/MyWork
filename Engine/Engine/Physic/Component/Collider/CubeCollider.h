#ifndef _CUBE_COLLIDER_H_
#define _CUBE_COLLIDER_H_

#include "Collider.h"

namespace engine
{
	namespace physic
	{
		namespace component
		{
			class CubeCollider final : public ACollider
			{
			public:
				CubeCollider() = delete;
				CubeCollider(physx::PxRigidActor* actor, PhysicMgr* physicMgr, bool trigger,
					Transform* objectTransform, physx::PxMaterial& mat);
				~CubeCollider();

				void Update();
				void SetDimensions(engine::core::maths::Vec3);

				engine::core::maths::Vec3 GetDimensions() const;

			private:
				engine::core::maths::Vec3 m_dimensions;
				void BuildShape();
			};
		}
	}
}

#endif // !_CUBE_COLLIDER_H_
