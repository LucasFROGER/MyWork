#ifndef _COMPONENT_SPHERECOLLIDER_H_
#define _COMPONENT_SPHERECOLLIDER_H_

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
			class SphereCollider final : public Component
			{
			public:
				SphereCollider(scene_graph::GameObject* gameObject, engine::Engine* engine);

				virtual void Init() override;
				void Awake() override {}
				void PreProcess() override {}
				void ContinuousProcess(float deltaTime) override;
				void Process(float deltaTime) override {}
				void LateProcess(float deltaTime) override {}
				void Render() override;
				void OnExit() override {}
				void OnDestroy() override;

				void OnActivation() override;
				void OnDeactivation() override;

				void SetTrigger(bool trigger);
				void SetRadius(float radius);

			private:
				engine::physic::Object** m_physObject;
				engine::physic::component::SphereCollider* m_collider;
				bool m_trigger;
				int m_id;

				float m_radius;
				engine::core::maths::Vec3 m_scale;

				engine::rhi::RHI* m_rhi;
				std::vector<int> m_windowIDs;
				resource::Mesh* m_mesh;
				resource::Material* m_material;
				low_renderer::ConstantBufferPerObject m_transformBuffer;
				int m_transformBufferID;
				int m_renderID;

				void InitRenderObject();
			};
		}
	}
}

#endif // !_COLLIDER_H_
