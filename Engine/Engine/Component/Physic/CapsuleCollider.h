#ifndef _COMPONENT_CAPSULECOLLIDER_H_
#define _COMPONENT_CAPSULECOLLIDER_H_

#include "../../Engine.h"
#include "../Component.h"
#include "../../Physic/Object/Object.h"
#include "../../Resource/Mesh.h"
#include "../../Resource/Material.h"
#include "../../LowRenderer/Vertex.h"
#include "../../RHI/RHI.h"

namespace engine
{
	namespace component
	{
		namespace physic
		{
			class CapsuleCollider final : public Component
			{
			public:
				CapsuleCollider(scene_graph::GameObject* gameObject, engine::Engine* engine);

				engine::Engine* m_engine;

				virtual void Init() override;
				void Awake() override {}
				void PreProcess() override {}
				void Process(float deltaTime) override {}
				void ContinuousProcess(float deltaTime) override;
				void LateProcess(float deltaTime) override {}
				void Render() override;
				void OnExit() override {}
				void OnDestroy() override;

				void OnActivation() override;
				void OnDeactivation() override;

				void SetTrigger(bool trigger);
				void SetDimensions(float height, float radius);

			private:
				engine::physic::Object** m_physObject;
				engine::physic::component::CapsuleCollider* m_collider;
				bool m_trigger;
				int m_id;
				
				float m_height;
				float m_radius;

				engine::rhi::RHI* m_rhi;
				std::vector<int> m_windowIDs;
				resource::Mesh* m_upMesh;
				resource::Mesh* m_corpMesh;
				resource::Mesh* m_botMesh;
				resource::Material* m_material;

				low_renderer::ConstantBufferPerObject m_upTransformBuffer;
				int m_upTransformBufferID;
				low_renderer::ConstantBufferPerObject m_corpTransformBuffer;
				int m_corpTransformBufferID;
				low_renderer::ConstantBufferPerObject m_botTransformBuffer;
				int m_botTransformBufferID;

				engine::core::maths::Vec3 m_cylinderScale;
				engine::core::maths::Vec3 m_sphereScale;
				engine::core::maths::Vec3 m_sphereTranslate;



				int m_renderUpID;
				int m_renderCorpID;
				int m_renderBotID;

				void InitRenderObjectTop();
				void InitRenderObjectCorp();
				void InitRenderObjectBot();
			};
		}
	}
}

#endif // !_COLLIDER_H_
