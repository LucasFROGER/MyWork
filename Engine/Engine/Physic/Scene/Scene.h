#ifndef _PHYSIC_SCENE_H_
#define _PHYSIC_SCENE_H_

#include <vector>

#include "../../Utils/IdAllocator.h"
#include "../Callbacks/SceneEventCallback.h"
#include "../Callbacks/CollisionModificationCallback.h"
#include "Collisions/CollisionMgr.h"

namespace engine
{
	namespace physic
	{
		class PhysicMgr;

		class Scene
		{
		public:
			Scene(PhysicMgr* physicMgr);
			~Scene();

			void Start();

			void Update(float deltaTime);
			void FixedUpdate(float deltaTime);
			void LateUpdate(float deltaTime);

			void Exit();

			Object* CreateObject(Transform* transform, bool isStatic, scene_graph::GameObject* gameObject);
			void DeleteObject(Object* object);

			void SetActive(bool active);
			void SetGravity(engine::core::maths::Vec3 gravity);

			physx::PxScene* GetPxScene() const;
			PhysicMgr* GetPhysicMgr() const;
			CollisionMgr* GetCollisionMgr() const;
			engine::core::maths::Vec3 GetGravity();

		private:
			PhysicMgr* m_physicMgr;
			physx::PxScene* m_scene;
			std::vector<Object*> m_objects;
			utils::IdAllocator m_idAllocator;
			SceneCallbackEvent* m_simuCallback;
			CollisionModificationCallback* m_colliModCallback;
			CollisionMgr* m_collisionMgr;

			engine::core::maths::Vec3 m_gravity;
			bool m_simulate;
		};
	}
}

#endif