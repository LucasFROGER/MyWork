#ifndef _MONO_BEHAVIOUR_H_
#define _MONO_BEHAVIOUR_H_

#include "../Core/Maths/Vector/Vec3.h"

#include "Component.h"
#include "../SceneGraph/GameObject.h"

namespace engine
{
	namespace component
	{
		enum class BehaviourState
		{
			NONE = 0,
			START,
			UPDATE,
			COUNT
		};

		class MonoBehaviour : public engine::component::Component
		{
		public:
			template<typename T>
			MonoBehaviour(scene_graph::GameObject* gameObject, engine::Engine* engine, T* child);

			virtual void PreProcess() override final;
			virtual void Process(float deltaTime) override final;
			virtual void FixedProcess(float deltaTime) override final;
			virtual void LateProcess(float deltaTime) override final;
			virtual void OnExit() override final;

			virtual void Start() {}
			virtual void Update(float deltaTime) {}
			virtual void FixedUpdate(float deltaTime) {}
			virtual void LateUpdate(float deltaTime) {}
			virtual void Exit() {}

			virtual void OnCollisionEnter(engine::physic::CollisionInfo info) {}
			virtual void OnCollisionStay(engine::physic::CollisionInfo info) {}
			virtual void OnCollisionExit(engine::physic::CollisionInfo info) {}

			virtual void OnTriggerEnter(engine::physic::TriggerInfo info) {}
			virtual void OnTriggerStay(engine::physic::TriggerInfo info) {}
			virtual void OnTriggerExit(engine::physic::TriggerInfo info) {}

		private:
			MonoBehaviour* m_child;

			BehaviourState m_state;
		};

		template<typename T>
		inline MonoBehaviour::MonoBehaviour(scene_graph::GameObject* gameObject, engine::Engine* engine, T* child) :
			Component(false, typeid(T).name(), gameObject, engine),
			m_child{ child },
			m_state{ BehaviourState::NONE }
		{}
	}
}
#endif