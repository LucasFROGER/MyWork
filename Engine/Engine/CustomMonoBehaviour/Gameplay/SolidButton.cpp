#include "SolidButton.h"

#include "../../Fenestration/Inputs/KeyCode.h"
#include "../../SceneGraph/GameObject.h"
#include "../Old/MovableObject.h"
#include "../../Component/MeshRenderer.h"
#include "Reseter.h"
#include "Pickable.h"

using namespace engine::scene_graph;
using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component;
using namespace engine::component::physic;

SolidButton::SolidButton(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_meshRenderer{ nullptr },
	m_material{ nullptr },
	m_completed{ false },
	m_completeMaterial{ nullptr }
{ }

void SolidButton::Init()
{ }

void SolidButton::Awake()
{
	m_meshRenderer = m_gameObject->GetComponent<engine::component::MeshRenderer>();
	m_material = m_meshRenderer->GetMaterial();
}

void SolidButton::Start()
{ }

void SolidButton::Update(float deltaTime)
{ }

void SolidButton::LateUpdate(float deltaTime)
{ }

void SolidButton::Exit()
{ }

void SolidButton::OnCollisionEnter(engine::physic::CollisionInfo info)
{

}

void SolidButton::OnCollisionStay(engine::physic::CollisionInfo info)
{

}

void SolidButton::OnCollisionExit(engine::physic::CollisionInfo info)
{

}

void SolidButton::OnTriggerEnter(engine::physic::TriggerInfo info)
{ 
	

}

void SolidButton::OnTriggerStay(engine::physic::TriggerInfo info)
{
	if (m_completed == true)
		return;
	if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_E))
	{
		m_completed = true;
		GameObject* obj = m_gameObject->GetScene()->NewGameObject("Pickable");;
		MeshRenderer* meshRenderer = obj->NewComponent<MeshRenderer>();

		Mesh* cube = m_engine->GetExplorer()->GetMainFolder()->GetMesh("chara");
		Material* mat = m_engine->GetExplorer()->GetMainFolder()->GetMaterial("charaMaterial");

		if (cube)
			meshRenderer->SetMesh(cube);
		if (mat)
			meshRenderer->SetMaterial(mat);

		obj->GetTransform()->SetPosition(Vec3{ 10.f,1.f,20.f });
		obj->GetTransform()->SetRotation(Quaternion::Euler(Vec3{ 0.f,0.f,0.f }));
		obj->GetTransform()->SetScale(Vec3{ 1.f,1.f,1.f });
	}

}

void SolidButton::OnTriggerExit(engine::physic::TriggerInfo info)
{ }

void SolidButton::SetCompletedMaterial(engine::resource::Material* mat)
{
	m_completeMaterial = mat;
}

void SolidButton::Reset()
{

}

