#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include "Component.h"
#include "../Resource/Mesh.h"
#include "../Resource/Material.h"
#include "../LowRenderer/Vertex.h"
#include "../RHI/RHI.h"

#include "../Physic/Transform/Transform.h"

namespace engine
{
	namespace component
	{
		class MeshRenderer final : public Component
		{
		public:
			MeshRenderer(scene_graph::GameObject* gameObject, engine::Engine* engine);

			void Init() override {}
			void Awake() override {}
			void PreProcess() override {}
			void ContinuousProcess(float deltaTime) {}
			void Process(float deltaTime) override {}
			void LateProcess(float deltaTime) override {}
			void Render() override;
			void OnExit() override {}
			void OnDestroy() override;

			void OnActivation() override;
			void OnDeactivation() override;
			
			resource::Mesh* GetMesh();
			resource::Material* GetMaterial();


			void SetMesh(resource::Mesh* mesh);
			void SetMaterial(resource::Material* material);

		private:
			engine::rhi::RHI* m_rhi;
			std::vector<int> m_windowIDs;
			resource::Mesh* m_mesh;
			resource::Material* m_material;
			low_renderer::ConstantBufferPerObject m_transformBuffer;
			int m_transformBufferID;
			int m_lightBufferID;
			int m_renderID;
			
			void InitRenderObject();
		};
	}
}

#endif