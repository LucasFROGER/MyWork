#include "Player.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

Player::Player(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_meshRenderer{ nullptr },
	m_camera{ nullptr },
	m_speed{ 5.f },
	m_rotSpeed{ 5.f },
	m_jumpHeight{ 24.f },
	m_paused{ false },
	m_pickDistance{ 3.f },
	m_pickable{ nullptr }
{}

void Player::Init()
{

}

void Player::Awake()
{
	m_guiMgr = m_gameObject->GetScene()->FindObjectOfType<GUIMgr>();

	engine::fenestration::Window* win = m_engine->GetWindowsWrapper()->GetActiveWindow();
	m_engine->GetWindowsWrapper()->DisplayCursor(false);
	m_meshRenderer = m_gameObject->GetComponent<engine::component::MeshRenderer>();
	
	m_rigidbody = m_gameObject->GetComponent<engine::component::physic::Rigidbody>();
	m_rigidbody->UseGravity(false);

	m_camera = new engine::camera::FreeCamera(win->GetWidth(),
		win->GetHeight(), 0.1f, 1000.f, 60.f, m_transform->GetPosition() + m_transform->GetUp() * 10,
		m_transform->GetForward(), m_speed, m_rotSpeed);
	m_gameObject->GetScene()->SetCamera(m_camera);
	m_physObject = m_gameObject->GetPhysObject();

	m_head.SetParent(m_transform);
	m_head.SetPosition(m_camera->GetPosition() - m_transform->GetPosition(), engine::physic::ESpace::LOCAL);
}

void Player::Start()
{

}

void Player::Update(float deltaTime)
{
	engine::fenestration::Window* win = m_engine->GetWindowsWrapper()->GetActiveWindow();
	Vec2 mousePos = m_engine->GetWindowsWrapper()->GetMousePos(win);
	Vec2 center{ win->GetWidth() / 2.f , win->GetHeight() / 2.f };
	m_engine->GetWindowsWrapper()->SetMousePos(win, center);
	Vec2 mouseMove = mousePos - center;

	if (m_paused)
		return;

	
	
	m_camera->MoveTarget(mouseMove, deltaTime);

	engine::core::maths::Vec3 forward = m_camera->GetForward();
	forward.m_y = 0.0f;
	engine::core::maths::Vec3 transForward = m_transform->GetForward();
	transForward.m_y = 0.0f;
	engine::core::maths::Vec3 right = m_camera->GetRight();


	
	engine::core::maths::Vec3 up = m_camera->GetUp();
	engine::core::maths::Vec3 headUp = m_head.GetUp();

	

	float angle = engine::core::maths::Vec2::GetAngle({ forward.m_x, forward.m_z }, { transForward.m_x, transForward.m_z });
	float angleTrans = engine::core::maths::Vec2::GetAngle({ right.m_x, right.m_z }, { transForward.m_x, transForward.m_z });
	float angleCam = engine::core::maths::Vec2::GetAngle({ forward.m_x, forward.m_z }, { right.m_x, right.m_z });

	float Hangle = engine::core::maths::Vec3::GetAngle(up, headUp);
	float HangleTrans = engine::core::maths::Vec3::GetAngle(headUp, transForward);
	float HangleCam = engine::core::maths::Vec3::GetAngle(up, transForward);



	//float degree = (angle * 180.f / 3.14159265359f);

	//std::cout << "Angle{ rad: " << angle << ", deg: " << degree << "};" << std::endl;

	engine::core::maths::Vec3 translation = Vec3::Zero();
	
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_W))
	{
		translation += forward;
	}

	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_S))
	{
		translation -= forward;
		
	}
	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_A))
	{
		translation -= right;
	}

	if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_D))
	{
		translation += right;
	}

	if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_SPACE))
	{
		if ((*m_physObject)->IsLanding() == true)
			m_velocity.m_y += m_jumpHeight * deltaTime;
	}
	m_velocity.m_x = translation.GetNormalized().m_x * m_speed * deltaTime;
	m_velocity.m_z = translation.GetNormalized().m_z * m_speed * deltaTime;
	if ((*m_physObject)->IsLanding() == false)
		m_velocity.m_y += m_gameObject->GetScene()->GetPhysScene()->GetGravity().m_y * deltaTime;
	else if(m_velocity.m_y < 0.0f)
		m_velocity.m_y = 0.0f;

	m_transform->Translate(m_velocity, engine::physic::ESpace::LOCAL);
	m_transform->Rotate(Quaternion::Euler({ 0.0f, angleTrans > angleCam? angle : -angle , 0.0f }));
	m_head.Rotate(Quaternion::Euler({ HangleTrans > HangleCam ? Hangle : -Hangle, 0.0f , 0.0f }));
	m_camera->SetPosition(m_transform->GetPosition() + m_transform->GetUp());
	m_head.SetPosition(m_transform->GetPosition() + m_transform->GetUp());
}

void Player::LateUpdate(float deltaTime)
{

}

void Player::Exit()
{
	delete m_camera;
	m_camera = nullptr;
	m_engine->GetWindowsWrapper()->DisplayCursor(true);
	m_velocity = Vec3::Zero();
}

void Player::OnCollisionEnter(engine::physic::CollisionInfo info)
{

}

void Player::OnCollisionStay(engine::physic::CollisionInfo info)
{

}

void Player::OnCollisionExit(engine::physic::CollisionInfo info)
{

}

void Player::OnTriggerEnter(engine::physic::TriggerInfo info)
{
}

void Player::OnTriggerStay(engine::physic::TriggerInfo info)
{

}

void Player::OnTriggerExit(engine::physic::TriggerInfo info)
{

}

void Player::Pick(Pickable* pickable)
{
	if (m_pickable == nullptr)
	{
		pickable->Pick(m_transform);
		m_pickable = pickable;
	}
	else
	{
		ReleasePickable();
		Pick(pickable);
	}
}

void Player::ReleasePickable()
{
	if (m_pickable)
	{
		m_pickable->Release();
		m_pickable = nullptr;
	}
}

bool Player::GotPickable()
{
	return m_pickable != nullptr;
}

bool Player::CheckPickable(Pickable* pickable)
{
	return m_pickable == pickable;
}

void Player::SetSpeed(float speed)
{
	m_speed = speed;
}

void Player::Pause(bool pause)
{
	m_paused = pause;
}
