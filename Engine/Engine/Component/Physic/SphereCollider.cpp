#include "SphereCollider.h"
#include "../../SceneGraph/GameObject.h"
#include "../../Engine.h"

engine::component::physic::SphereCollider::SphereCollider(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(false, typeid(SphereCollider).name(), gameObject, engine),
	m_physObject{ gameObject->GetPhysObject() },
	m_id{ -1 },
	m_trigger{ false },
	m_windowIDs{},
	m_mesh{ nullptr },
	m_material{ nullptr },
	m_renderID{ -1 },
	m_radius{ 1.f },
	m_collider{ nullptr }

{
	m_rhi = m_engine->GetRHI();
}

void engine::component::physic::SphereCollider::Init()
{
	if (*m_physObject != nullptr)
	{
		m_id = (*m_physObject)->AddCollider(engine::physic::component::ECollType::SPHERE, m_trigger);
		m_collider = static_cast<engine::physic::component::SphereCollider*>((*m_physObject)->GetCollider(m_id));

		m_mesh = (*m_physObject)->GetScene()->GetPhysicMgr()->GetSphereMesh();
		m_material = (*m_physObject)->GetScene()->GetPhysicMgr()->GetPhysMaterial();
		InitRenderObject();
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, true, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::SphereCollider::ContinuousProcess(float deltaTime)
{
	engine::core::maths::Vec3 scale = m_transform->GetScale();

	float radX = scale.m_x;
	float radY = scale.m_y;
	float radZ = scale.m_z;

	float radMax = radX > radY ? radX : radY;
	radMax = radMax > radZ ? radMax : radZ;
	radMax += m_radius - 1.f;
	m_scale = { radMax, radMax, radMax };
	m_collider->SetRadius(radMax / 2);

}

void engine::component::physic::SphereCollider::Render()
{
	if (m_mesh == nullptr || m_material == nullptr)
		return;

	engine::physic::Transform trans = *m_transform;
	trans.SetScale(m_scale);

	m_transformBuffer.wMat = trans.GetLocalToWorldMatrix();
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
	m_transformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();
	m_rhi->UpdateConstantBuffer(m_transformBufferID, &m_transformBuffer, sizeof(m_transformBuffer));
}

void engine::component::physic::SphereCollider::OnDestroy()
{
	(*m_physObject)->RemoveCollider(m_id);
	m_id = -1;
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::SphereCollider::OnActivation()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, true, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::SphereCollider::OnDeactivation()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::SphereCollider::SetTrigger(bool trigger)
{
	m_trigger = trigger;
	if (m_collider != nullptr)
		m_collider->SetTrigger(trigger);
}

void engine::component::physic::SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
	if (m_collider != nullptr)
		m_collider->SetRadius(radius);
}

void engine::component::physic::SphereCollider::InitRenderObject()
{
	if (m_mesh == nullptr)
		return;
	if (m_material == nullptr)
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

		m_renderID = m_rhi->GenRenderObject(
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_transformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size(),
			engine::rhi::EDrawingType::DLINE,
			m_mesh->GetVBOAddress(), sizeof(resource::Vertex), m_mesh->GetSizeOfVBO(),
			m_mesh->GetIBOAddress(), m_mesh->GetSizeOfIBO(),
			true
		);
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