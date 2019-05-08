#include "CapsuleCollider.h"
#include "../../SceneGraph/GameObject.h"
#include "..\..\Physic\Component\Collider\CapsuleCollider.h"

engine::component::physic::CapsuleCollider::CapsuleCollider(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(false, typeid(CapsuleCollider).name(), gameObject, engine),
	m_physObject{ gameObject->GetPhysObject() },
	m_id{ -1 },
	m_trigger{ false },
	m_windowIDs{ },
	m_upMesh{ nullptr },
	m_corpMesh{ nullptr },
	m_botMesh{ nullptr },
	m_material{ nullptr },
	m_renderUpID{ -1 },
	m_renderCorpID{ -1 },
	m_renderBotID{ -1 },
	m_height{ 2.0f },
	m_radius{ 0.5f },
	m_upTransformBufferID{ -1 },
	m_corpTransformBufferID{ -1 },
	m_botTransformBufferID{ -1 },
	m_collider{ nullptr }
{
	m_rhi = engine->GetRHI();
}

void engine::component::physic::CapsuleCollider::Init()
{
	if (*m_physObject != nullptr)
	{
		m_id = (*m_physObject)->AddCollider(engine::physic::component::ECollType::CAPSULE, m_trigger);
		m_collider = static_cast<engine::physic::component::CapsuleCollider*>((*m_physObject)->GetCollider(m_id));

		m_upMesh = (*m_physObject)->GetScene()->GetPhysicMgr()->GetCapsuleUpMesh();
		m_corpMesh = (*m_physObject)->GetScene()->GetPhysicMgr()->GetCapsuleCorpMesh();
		m_botMesh = (*m_physObject)->GetScene()->GetPhysicMgr()->GetCapsuleBotMesh();
		m_material = (*m_physObject)->GetScene()->GetPhysicMgr()->GetPhysMaterial();

		InitRenderObjectTop();
		InitRenderObjectCorp();
		InitRenderObjectBot();

		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderUpID, true, m_windowIDs[i]);
			m_rhi->SetActive(m_renderCorpID, true, m_windowIDs[i]);
			m_rhi->SetActive(m_renderBotID, true, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::CapsuleCollider::ContinuousProcess(float deltaTime)
{
	engine::core::maths::Vec3 scale = m_transform->GetScale();
	float scaleX = scale.m_x < 0 ? scale.m_x * -1.f : scale.m_x;
	float scaleY = scale.m_y < 0 ? scale.m_y * -1.f : scale.m_y;
	float scaleZ = scale.m_z < 0 ? scale.m_z * -1.f : scale.m_z;
	
	float scaleMax = /*scaleX > scaleY ? (*/scaleX > scaleZ ? scaleX : scaleZ/*) : (scaleY > scaleZ ? scaleY : scaleZ)*/;
	float scaleH = (scaleY * m_height) - (m_radius * (scaleX > scaleZ ? scaleX : scaleZ));


	m_sphereScale = engine::core::maths::Vec3{ scaleMax, scaleMax, scaleMax };
	m_sphereTranslate = engine::core::maths::Vec3{ 0.f, 0.25f, 0.f } *  scaleY;

	m_cylinderScale = engine::core::maths::Vec3{ scaleMax, scaleY, scaleMax };

	if (m_collider != nullptr)
		m_collider->SetDimensions(scaleMax, scaleMax);
}

void engine::component::physic::CapsuleCollider::Render()
{
	if (m_upMesh == nullptr || m_corpMesh == nullptr || m_botMesh == nullptr || m_material == nullptr)
		return;
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();

	engine::physic::Transform trans1 = m_transform;
	trans1.Translate(m_sphereTranslate);
	trans1.SetScale(m_sphereScale);


	m_upTransformBuffer.wMat = trans1.GetLocalToWorldMatrix();
	m_upTransformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();
	m_rhi->UpdateConstantBuffer(m_upTransformBufferID, &m_upTransformBuffer, sizeof(m_upTransformBuffer));

	engine::physic::Transform trans2 = m_transform;
	trans2.SetScale(m_cylinderScale);

	m_corpTransformBuffer.wMat = trans2.GetLocalToWorldMatrix();
	m_corpTransformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();
	m_rhi->UpdateConstantBuffer(m_corpTransformBufferID, &m_corpTransformBuffer, sizeof(m_corpTransformBuffer));

	engine::physic::Transform trans3 = m_transform;
	trans3.Translate(-m_sphereTranslate);
	trans3.SetScale(m_sphereScale);

	m_botTransformBuffer.wMat = trans3.GetLocalToWorldMatrix();
	m_botTransformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();
	m_rhi->UpdateConstantBuffer(m_botTransformBufferID, &m_botTransformBuffer, sizeof(m_botTransformBuffer));
}

void engine::component::physic::CapsuleCollider::OnDestroy()
{
	(*m_physObject)->RemoveCollider(m_id);
	m_id = -1;
	if (m_renderUpID != -1 && m_renderCorpID != -1 && m_renderBotID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderUpID, false, m_windowIDs[i]);
			m_rhi->SetActive(m_renderCorpID, false, m_windowIDs[i]);
			m_rhi->SetActive(m_renderBotID, false, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::CapsuleCollider::OnActivation()
{
	if (m_renderUpID != -1 && m_renderCorpID != -1 && m_renderBotID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderUpID, true, m_windowIDs[i]);
			m_rhi->SetActive(m_renderCorpID, true, m_windowIDs[i]);
			m_rhi->SetActive(m_renderBotID, true, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::CapsuleCollider::OnDeactivation()
{
	if (m_renderUpID != -1 && m_renderCorpID != -1 && m_renderBotID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderUpID, false, m_windowIDs[i]);
			m_rhi->SetActive(m_renderCorpID, false, m_windowIDs[i]);
			m_rhi->SetActive(m_renderBotID, false, m_windowIDs[i]);
		}
	}
}

void engine::component::physic::CapsuleCollider::SetTrigger(bool trigger)
{
	m_trigger = trigger;
	if (m_collider != nullptr)
		m_collider->SetTrigger(trigger);
}

void engine::component::physic::CapsuleCollider::SetDimensions(float height, float radius)
{
	m_height = height;
	m_radius = radius;
}

void engine::component::physic::CapsuleCollider::InitRenderObjectTop()
{
	if (m_upMesh == nullptr || m_corpMesh == nullptr || m_botMesh == nullptr || m_material == nullptr)
		return;

	m_upTransformBuffer.wMat = m_transform->GetLocalToWorldMatrix();
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
	m_upTransformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();

	m_upTransformBufferID = m_rhi->GenConstantBuffer(&m_upTransformBuffer, sizeof(m_upTransformBuffer), 0);

	m_windowIDs = m_gameObject->GetScene()->GetTargetWinIds();


	std::vector<int> textureIDs = m_material->GetTextureIDs();
	std::vector<int> samplerID = m_material->GetTextureSamplers();

	if (m_renderUpID == -1)
	{
		m_renderUpID = m_rhi->GenRenderObject(
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_upTransformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size(),
			engine::rhi::EDrawingType::DLINE,
			m_upMesh->GetVBOAddress(), sizeof(resource::Vertex), m_upMesh->GetSizeOfVBO(),
			m_upMesh->GetIBOAddress(), m_upMesh->GetSizeOfIBO(),
			true
		);
	}
	else
	{
		m_rhi->SetShadersConstantBuffersTexturesSamplers(
			m_renderUpID,
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_upTransformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size()
		);
	}
}

void engine::component::physic::CapsuleCollider::InitRenderObjectCorp()
{
	if (m_upMesh == nullptr || m_corpMesh == nullptr || m_botMesh == nullptr || m_material == nullptr)
		return;

	m_corpTransformBuffer.wMat = m_transform->GetLocalToWorldMatrix();
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
	m_corpTransformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();

	m_corpTransformBufferID = m_rhi->GenConstantBuffer(&m_corpTransformBuffer, sizeof(m_corpTransformBuffer), 0);


	m_windowIDs = m_gameObject->GetScene()->GetTargetWinIds();

	std::vector<int> textureIDs = m_material->GetTextureIDs();
	std::vector<int> samplerID = m_material->GetTextureSamplers();

	if (m_renderCorpID == -1)
	{
		m_renderCorpID = m_rhi->GenRenderObject(
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_corpTransformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size(),
			engine::rhi::EDrawingType::DLINE,
			m_corpMesh->GetVBOAddress(), sizeof(resource::Vertex), m_corpMesh->GetSizeOfVBO(),
			m_corpMesh->GetIBOAddress(), m_corpMesh->GetSizeOfIBO(),
			true
		);
	}
	else
	{
		m_rhi->SetShadersConstantBuffersTexturesSamplers(
			m_renderCorpID,
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_corpTransformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size()
		);
	}

}

void engine::component::physic::CapsuleCollider::InitRenderObjectBot()
{
	if (m_upMesh == nullptr || m_corpMesh == nullptr || m_botMesh == nullptr || m_material == nullptr)
		return;

	m_botTransformBuffer.wMat = m_transform->GetLocalToWorldMatrix();
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
	m_botTransformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();

	m_botTransformBufferID = m_rhi->GenConstantBuffer(&m_botTransformBuffer, sizeof(m_botTransformBuffer), 0);

	m_windowIDs = m_gameObject->GetScene()->GetTargetWinIds();


	std::vector<int> textureIDs = m_material->GetTextureIDs();
	std::vector<int> samplerID = m_material->GetTextureSamplers();

	if (m_renderBotID == -1)
	{
		m_renderBotID = m_rhi->GenRenderObject(
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_botTransformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size(),
			engine::rhi::EDrawingType::DLINE,
			m_botMesh->GetVBOAddress(), sizeof(resource::Vertex), m_botMesh->GetSizeOfVBO(),
			m_botMesh->GetIBOAddress(), m_botMesh->GetSizeOfIBO(),
			true
		);
	}
	else
	{
		m_rhi->SetShadersConstantBuffersTexturesSamplers(
			m_renderBotID,
			m_material->GetProgram(), m_material->GetProgramSize(),
			&m_botTransformBufferID, 1,
			m_material->GetTextureIDs().data(), m_material->GetTextureIDs().size(),
			m_material->GetTextureSamplers().data(), m_material->GetTextureSamplers().size()
		);
	}
}