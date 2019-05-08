#include "Trap.h"

#include "../../Fenestration/Inputs/KeyCode.h"
#include "../../SceneGraph/GameObject.h"
#include "../Old/MovableObject.h"
#include "../../Component/MeshRenderer.h"
#include "Reseter.h"
#include "Pickable.h"
#include "../Managers/GUIMgr.h"

using namespace engine::scene_graph;
using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component;
using namespace engine::component::physic;

Trap::Trap(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_meshRenderer{ nullptr },
	m_material{ nullptr },
	m_completed{ false },
	m_completeMaterial{ nullptr }
{ }

void Trap::Init()
{ }

void Trap::Awake()
{ 
	m_meshRenderer = m_gameObject->GetComponent<engine::component::MeshRenderer>();
	m_material = m_meshRenderer->GetMaterial();
}

void Trap::Start()
{ }

void Trap::Update(float deltaTime)
{ }

void Trap::LateUpdate(float deltaTime)
{ }

void Trap::Exit()
{ }

void Trap::OnCollisionEnter(engine::physic::CollisionInfo info)
{ 
	Pickable* pickable = info.m_otherObject->GetComponent<Pickable>();
	if (pickable != nullptr)
	{
		m_completed = true;
		if (m_completeMaterial != nullptr && m_meshRenderer != nullptr)
		{
			m_meshRenderer->SetMaterial(m_completeMaterial);
			m_gameObject->GetScene()->Remove(info.m_otherObject);
			m_gameObject->GetScene()->FindObjectOfType<GUIMgr>()->SetInfoText("");
		}
	}
}

void Trap::OnCollisionStay(engine::physic::CollisionInfo info)
{ 

}

void Trap::OnCollisionExit(engine::physic::CollisionInfo info)
{ 

}

void Trap::OnTriggerEnter(engine::physic::TriggerInfo info)
{ }

void Trap::OnTriggerStay(engine::physic::TriggerInfo info)
{ }

void Trap::OnTriggerExit(engine::physic::TriggerInfo info)
{ }

void Trap::SetCompletedMaterial(engine::resource::Material* mat)
{
	m_completeMaterial = mat;
}

void Trap::Reset()
{

}

