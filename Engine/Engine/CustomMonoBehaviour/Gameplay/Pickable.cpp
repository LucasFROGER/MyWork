#include "Pickable.h"

#include "../../Fenestration/Inputs/KeyCode.h"
#include "Player.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

Pickable::Pickable(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_picked{ false },
	m_useGravity{ false },
	m_paused{ false },
	m_triggered{ false },
	m_player{ false },
	m_velocity{ Vec3::Zero() }
{}

void Pickable::Init()
{

}

void Pickable::Awake()
{
	m_rigidbody = m_gameObject->GetComponent<engine::component::physic::Rigidbody>();
	m_rigidbody->UseGravity(false);

	m_guiMgr = m_gameObject->GetScene()->FindObjectOfType<GUIMgr>();
	m_parent = m_gameObject->GetScene()->GetRoot()->GetTransform();
	m_physObject = m_gameObject->GetPhysObject();
	
}

void Pickable::Start()
{

}

void Pickable::Update(float deltaTime)
{
	if (m_paused)
		return;

	if (!m_picked || m_useGravity)
	{
		if ((*m_physObject)->IsLanding() == false)
			m_velocity.m_y += m_gameObject->GetScene()->GetPhysScene()->GetGravity().m_y * deltaTime;
		else if (m_velocity.m_y < 0.0f)
			m_velocity.m_y = 0.0f;

		m_transform->Translate(m_velocity, engine::physic::ESpace::LOCAL);
	}
}

void Pickable::LateUpdate(float deltaTime)
{

}

void Pickable::Exit()
{
	if (m_player != nullptr)
	{
		m_player->ReleasePickable();
		m_player = nullptr;
	}
	m_velocity = Vec3::Zero();
}

void Pickable::OnCollisionEnter(engine::physic::CollisionInfo info)
{

}

void Pickable::OnCollisionStay(engine::physic::CollisionInfo info)
{

}

void Pickable::OnCollisionExit(engine::physic::CollisionInfo info)
{

}

void Pickable::OnTriggerEnter(engine::physic::TriggerInfo info)
{
	m_triggered = true;
	m_guiMgr->SetInfoText("Press E to pick up the cube");
}

void Pickable::OnTriggerStay(engine::physic::TriggerInfo info)
{
	if (m_paused)
		return;
	Player* player = info.m_otherObject->GetComponent<Player>();

	if (player != nullptr)
	{
		if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_E))
		{
			if (m_picked == false)
			{
				if (player->GotPickable())
					return;

				m_player = player;
 				player->Pick(this);
			}
			else if (m_picked == true)
			{
				if (!player->CheckPickable(this))
					return;
				player->ReleasePickable();
			}
		}
	}
}

void Pickable::OnTriggerExit(engine::physic::TriggerInfo info)
{
	m_triggered = false;
	m_guiMgr->SetInfoText("");
}

void Pickable::UseGravityWhenPicked(bool useGravity)
{
	m_useGravity = useGravity;
}

bool Pickable::IsUsingGravityWhenPicked() const
{
	return m_useGravity;
}

void Pickable::Pick(engine::physic::Transform* transform)
{
	m_transform->SetParent(transform);
	m_guiMgr->SetInfoText("");
	m_picked = true;
}

void Pickable::Release()
{
	m_transform->SetParent(m_parent);
	m_player = nullptr;
	m_guiMgr->SetInfoText("Press E to pick up the cube");
	m_picked = false;
}

void Pickable::Pause(bool pause)
{
	m_paused = pause;
	if (m_paused)
	{
		m_guiMgr->SetInfoText("");
	}
	else
	{ 
		m_guiMgr->SetInfoText(m_triggered ? (m_picked ? "" : "Press E to pick up the cube") : "");
	}
}
