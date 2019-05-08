#ifndef _COMPONENT_RIGIDBODY_H_
#define _COMPONENT_RIGIDBODY_H_

#include "../Component.h"
#include "../../Physic/Object/Object.h"

namespace engine
{
	namespace component
	{
		namespace physic
		{
			class Rigidbody final : public Component
			{
			public:
				Rigidbody(scene_graph::GameObject* gameObject, engine::Engine* engine);

				virtual void Init() override;
				void Awake() override {}
				void PreProcess() override {}
				void Process(float deltaTime) override {}
				void LateProcess(float deltaTime) override {}
				void Render() override {}
				void OnExit() override {}
				void OnDestroy() override;

				void OnActivation() override {}
				void OnDeactivation() override {}

				void UseGravity(bool useGravity);
				bool IsUsingGravity();

				void SetPositionConstraint(bool x, bool y, bool z);
				void SetRotationConstraint(bool x, bool y, bool z);

				bool GetPosXConstraint() const;
				bool GetPosYConstraint() const;
				bool GetPosZConstraint() const;
				
				bool GetRotXConstraint() const;
				bool GetRotYConstraint() const;
				bool GetRotZConstraint() const;

			private:
				engine::physic::Object** m_physObject;
				engine::physic::component::Rigidbody* m_rigidbody;

				bool m_useGravity;
				engine::core::maths::Vec3 m_posConst;
				engine::core::maths::Vec3 m_rotConst;
			};
		}
	}
}



#endif // !_COLLIDER_H_
