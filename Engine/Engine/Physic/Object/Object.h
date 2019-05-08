#ifndef _PHYSIC_OBJECT_H_
#define _PHYSIC_OBJECT_H_

#include <vector>

#include "../Component/Collider/CapsuleCollider.h"
#include "../Component/Collider/CubeCollider.h"
#include "../Component/Collider/SphereCollider.h"
#include "../Component/Rigidbody.h"
#include "../Transform/Transform.h"
#include "../../Utils/IdAllocator.h"
#include "../Scene/Collisions/CollisionInfo.h"
#include "../Scene/Collisions/TriggerInfo.h"

namespace engine
{
	namespace scene_graph
	{
		class GameObject;
	}

	namespace physic
	{
		class Scene;	
		class Object
		{
		public:
			Object(int id, bool isStatic, Transform* transform, Scene* scene, scene_graph::GameObject* gameObject);
			~Object();
			
			void Move(float deltaTime);
			void Result();

			void SetActive(bool active);

			int AddCollider(component::ECollType collType, bool trigger);
			component::ACollider* GetCollider(int id);
			void RemoveCollider(int id);

			component::Rigidbody* AddRigidbody();
			void RemoveRigidbody();

			void Stop();

			void SetIsStatic(bool isStatic);
			void SetIsLanding(bool isLanding);

			int GetId() const;
			Scene* GetScene();
			bool IsStatic() const;
			bool IsLanding() const;
			bool HasRigidbody() const;

			void OnCollisionEnter(CollisionInfo info);
			void OnCollisionStay(CollisionInfo info);
			void OnCollisionExit(CollisionInfo info);

			void OnTriggerEnter(TriggerInfo info);
			void OnTriggerStay(TriggerInfo info);
			void OnTriggerExit(TriggerInfo info);

			engine::scene_graph::GameObject* GetGameObject() const;
		private:
		
			Scene* m_scene;
			Transform* m_transform;

			const int m_id;
			bool m_isStatic;
			bool m_active;
			bool m_simulate;
			bool m_landing;

			std::vector<component::ACollider*> m_colliders;
			engine::utils::IdAllocator m_colliderId;
			component::Rigidbody* m_rigidbody;

			physx::PxMaterial* m_material;
			physx::PxRigidDynamic* m_actor;

			//physx::PxRigidStatic* m_statActor;
			//physx::PxRigidDynamic* m_dynaActor;
			engine::scene_graph::GameObject* m_gameObject;


			void ClearObject();
			void ClearActor();
		};
	}
}


#endif // !_PHYSIC_OBJECT_H_