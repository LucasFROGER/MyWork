#include "MovableObject.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;

MovableObject::MovableObject(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine , this),
	m_engine{ nullptr },
	m_meshRenderer{ nullptr },
	m_basicMaterial{ nullptr },
	m_selectedMaterial{ nullptr },
	m_selected{ false },
	m_triggered{ false },
	m_collsioned{ false }
{}

void MovableObject::Awake()
{
	m_meshRenderer = m_gameObject->GetComponent<engine::component::MeshRenderer>();
}

void MovableObject::Start()
{
	if (m_collsioned)
	{
		m_meshRenderer->SetMaterial(m_collisionMaterial);
	}
	else if (m_triggered)
	{
		m_meshRenderer->SetMaterial(m_triggerMaterial);
	}
	else
	{
		m_meshRenderer->SetMaterial(m_selected? m_selectedMaterial : m_basicMaterial);
	}
}

void MovableObject::Update(float deltaTime)
{

}

void MovableObject::LateUpdate(float deltaTime)
{

}

void MovableObject::Exit()
{

}

void MovableObject::SetTransform(Vec3 pos, Vec3 rot, Vec3 scale)
{
	m_transform->SetPosition(pos, engine::physic::ESpace::WORLD);
	m_transform->SetRotation(Quaternion::Euler(rot), engine::physic::ESpace::WORLD);
	m_transform->SetScale(scale);
}

void MovableObject::Select(bool selected)
{
	m_selected = selected;
	if (m_meshRenderer != nullptr)
	{
		if (!m_triggered && !m_collsioned)
		{
			if (selected)
				m_meshRenderer->SetMaterial(m_selectedMaterial);
			else
				m_meshRenderer->SetMaterial(m_basicMaterial);
		}
	}
}

void MovableObject::SetBasicMaterial(Material* basicMaterial)
{
	m_basicMaterial = basicMaterial;
}

void MovableObject::SetSelectedMaterial(Material* selectedMaterial)
{
	m_selectedMaterial = selectedMaterial;
}

void MovableObject::SetTriggerMaterial(engine::resource::Material* selectedMaterial)
{
	m_triggerMaterial = selectedMaterial;
}

void MovableObject::SetCollisionMaterial(engine::resource::Material* selectedMaterial)
{
	m_collisionMaterial = selectedMaterial;
}

void MovableObject::OnCollisionEnter(engine::physic::CollisionInfo info)
{
	//m_collsioned = true;
	//m_meshRenderer->SetMaterial(m_collisionMaterial);
	//info.m_otherObject->SetParent(m_gameObject);
}

void MovableObject::OnCollisionStay(engine::physic::CollisionInfo info)
{

}

void MovableObject::OnCollisionExit(engine::physic::CollisionInfo info)
{
	//m_collsioned = false;
	//Select(m_selected);
}

void MovableObject::OnTriggerEnter(engine::physic::TriggerInfo info)
{
	//m_triggered = true;
	//m_meshRenderer->SetMaterial(m_triggerMaterial);
}

void MovableObject::OnTriggerStay(engine::physic::TriggerInfo info)
{

}

void MovableObject::OnTriggerExit(engine::physic::TriggerInfo info)
{
	//m_triggered = false;
	//Select(m_selected);
}
