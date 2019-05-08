#ifndef _PHYSIX_ENGINE_CONVERTIONS_H_
#define _PHYSIX_ENGINE_CONVERTIONS_H_

#include "../../Core/Maths/Matrix/Mat4.h"
#include "../../Core/Maths/Vector/Vec4.h"
#include "../../Core/Maths/Vector/Vec3.h"
#include "../../Core/Maths/Vector/Vec2.h"
#include "../Transform/Transform.h"
#include "PxPhysicsAPI.h"

namespace engine
{
	namespace physic
	{
		struct ConvertionHandler
		{
			static physx::PxVec2 EngineToPhysx(engine::core::maths::Vec2 vec);
			static physx::PxVec3 EngineToPhysx(engine::core::maths::Vec3 vec);
			static physx::PxVec4 EngineToPhysx(engine::core::maths::Vec4 vec);
			static physx::PxMat44 EngineToPhysx(engine::core::maths::Mat4 mat);
			static physx::PxQuat EngineToPhysx(engine::core::maths::Quaternion quat);
			static physx::PxTransform EngineToPhysx(Transform trans);

			static engine::core::maths::Vec2 PhysxToEngine(physx::PxVec2 vec);
			static engine::core::maths::Vec3 PhysxToEngine(physx::PxVec3 vec);
			static engine::core::maths::Vec4 PhysxToEngine(physx::PxVec4 vec);
			static engine::core::maths::Mat4 PhysxToEngine(physx::PxMat44 mat);
			static engine::core::maths::Quaternion PhysxToEngine(physx::PxQuat quat);
			static Transform PhysxToEngine(physx::PxTransform trans);
		};
	}
}


#endif // !_PHYSIX_MATHS_CONVERTIONS_H_
