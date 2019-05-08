#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../Physic/Scene/Collisions/TriggerInfo.h"
#include "../Physic/Scene/Collisions/CollisionInfo.h"

#include <string>
#include <iostream>

namespace engine
{
	namespace scene_graph { class GameObject; }
	namespace physic { class Transform; }
	class Engine;

	namespace component
	{
		class Component
		{
		public:
			Component(bool mustBeUnique, const std::string& type, scene_graph::GameObject* gameObject, engine::Engine* engine);
			virtual ~Component() {}

			virtual void Init() {}
			virtual void Awake() {}
			virtual void PreProcess() {}
			virtual void ContinuousProcess(float deltaTime) {}
			virtual void Process(float deltaTime) {}
			virtual void FixedProcess(float deltaTime) {}
			virtual void LateProcess(float deltaTime) {}
			virtual void Render() {}
			virtual void OnExit() {}
			virtual void OnDestroy() {}

			virtual void OnActivation() {}
			virtual void OnDeactivation() {}

			virtual void OnCollisionEnter(engine::physic::CollisionInfo info) {}
			virtual void OnCollisionStay(engine::physic::CollisionInfo info) {}
			virtual void OnCollisionExit(engine::physic::CollisionInfo info) {}

			virtual void OnTriggerEnter(engine::physic::TriggerInfo info) {}
			virtual void OnTriggerStay(engine::physic::TriggerInfo info) {}
			virtual void OnTriggerExit(engine::physic::TriggerInfo info) {}

			bool GetMustBeUnique() const;
			const std::string& GetType() const;
			engine::scene_graph::GameObject* GetGameObject() const;
			engine::physic::Transform* GetTransform() const;
			bool GetIsEnable() const;

			void SetIsEnable(bool isEnable);

		protected:
			const bool m_mustBeUnique;
			std::string m_type;
			engine::scene_graph::GameObject* m_gameObject;
			engine::physic::Transform* m_transform;
			engine::Engine* m_engine;
			bool m_isEnable;
		};
	}
}
#endif