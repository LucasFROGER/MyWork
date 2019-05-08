#include "MeshRenderer.h"

#include "../Engine.h"
#include "../SceneGraph/GameObject.h"

using namespace engine::resource;

engine::component::MeshRenderer::MeshRenderer(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(true, typeid(MeshRenderer).name(), gameObject, engine),
	m_windowIDs{ },
	m_mesh{ nullptr },
	m_material{ nullptr },
	m_renderID{ -1 }
{
	m_rhi = engine->GetRHI();

}

void engine::component::MeshRenderer::Render()
{
	if (m_mesh == nullptr || m_material == nullptr)
		return;

	m_transformBuffer.wMat = m_transform->GetLocalToWorldMatrix();
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
	m_transformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();

	m_rhi->UpdateConstantBuffer(m_transformBufferID, &m_transformBuffer, sizeof(m_transformBuffer));
}

void engine::component::MeshRenderer::OnDestroy()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i]);
		}
	}
}

void engine::component::MeshRenderer::OnActivation()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, true, m_windowIDs[i]);
		}
	}
}

void engine::component::MeshRenderer::OnDeactivation()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i]);
		}
	}
}

engine::resource::Mesh* engine::component::MeshRenderer::GetMesh()
{
	return m_mesh;
}

engine::resource::Material* engine::component::MeshRenderer::GetMaterial()
{
	return m_material;
}

void engine::component::MeshRenderer::InitRenderObject()
{
	if (m_mesh == nullptr)
		return;
	if(m_material == nullptr)
		return;

	if (m_renderID == -1)
	{
		m_windowIDs = m_gameObject->GetScene()->GetTargetWinIds();

		m_transformBuffer.wMat = m_transform->GetLocalToWorldMatrix();
		camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
		m_transformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();

		m_transformBufferID = m_rhi->GenConstantBuffer(&m_transformBuffer, sizeof(m_transformBuffer), 0);

		std::vector<int> textureIDs = m_material->GetTextureIDs();
		std::vector<int> samplerID = m_material->GetTextureSamplers();

		int cbBuff[2]{ m_transformBufferID , m_engine->GetLightMgr()->GetLightBufferID() };

		m_renderID = m_rhi->GenRenderObject(
			m_material->GetProgram(), m_material->GetProgramSize(),
			&cbBuff[0], 2,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size(),
			engine::rhi::EDrawingType::DTRIANGLES,
			m_mesh->GetVBOAddress(), sizeof(resource::Vertex), m_mesh->GetSizeOfVBO(),
			m_mesh->GetIBOAddress(), m_mesh->GetSizeOfIBO(),
			true
		);

		if (m_gameObject->GetIsActive())
		{
			for (int i{ 0 }; i < m_windowIDs.size(); ++i)
			{
				m_rhi->SetActive(m_renderID, true, m_windowIDs[i]);
			}
		}
	}
	else
	{
		m_rhi->SetShadersConstantBuffersTexturesSamplers(
			m_renderID,
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_transformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size()
		);
	}
}


void engine::component::MeshRenderer::SetMesh(Mesh* mesh)
{
	m_mesh = mesh;
	
	for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		m_rhi->SetActive(m_renderID, false, m_windowIDs[i]);
	
	m_renderID = -1;
	InitRenderObject();
}

void engine::component::MeshRenderer::SetMaterial(Material* material)
{
	m_material = material;
	for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		m_rhi->SetActive(m_renderID, false, m_windowIDs[i]);

	m_renderID = -1;
	InitRenderObject();
}
