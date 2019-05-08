#include "ObjectMover.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration::input::keys;

ObjectMover::ObjectMover(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_speed{ 5.f },
	m_engine{ nullptr },
	m_currentObject{ nullptr },
	m_choose{ 0 }
{}

void ObjectMover::Awake()
{

}

void ObjectMover::Start()
{
	if (m_movableObjects.size() > 0)
	{
		m_choose = 0;
		m_currentObject = m_movableObjects[m_choose];
		m_currentObject->Select(true);
	}
}

void ObjectMover::Update(float deltaTime)
{
	if (m_currentObject != nullptr && m_engine != nullptr)
	{
		if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_K))
		{
			m_choose = m_choose == 0 ? m_movableObjects.size() - 1 : --m_choose;

			m_currentObject->Select(false);
			m_currentObject = m_movableObjects[m_choose];
			m_currentObject->Select(true);
		}
		if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_L))
		{
			m_choose = m_choose == m_movableObjects.size() - 1 ? 0 : ++m_choose;

			m_currentObject->Select(false);
			m_currentObject = m_movableObjects[m_choose];
			m_currentObject->Select(true);
		}
		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_UP_ARROW))
			m_currentObject->GetGameObject()->GetTransform()->Translate(engine::core::maths::Vec3::Forward() * deltaTime * m_speed, engine::physic::ESpace::WORLD);

		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_DOWN_ARROW))
			m_currentObject->GetGameObject()->GetTransform()->Translate(engine::core::maths::Vec3::Back() * deltaTime * m_speed, engine::physic::ESpace::WORLD);
		

		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_LEFT_ARROW))
			m_currentObject->GetGameObject()->GetTransform()->Translate(engine::core::maths::Vec3::Left() * deltaTime * m_speed, engine::physic::ESpace::WORLD);
		

		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_RIGHT_ARROW))
			m_currentObject->GetGameObject()->GetTransform()->Translate(engine::core::maths::Vec3::Right() * deltaTime * m_speed, engine::physic::ESpace::WORLD);

		engine::core::maths::Vec3 scale = m_currentObject->GetGameObject()->GetTransform()->GetScale();

		float increment{ 0.001f };

		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_PAD_7))
			scale.m_x += increment;
		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_PAD_8))
			scale.m_y += increment;
		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_PAD_9))
			scale.m_z += increment;

		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_PAD_4))
			scale.m_x = scale.m_x > increment ? scale.m_x - increment : 0;
		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_PAD_5))
			scale.m_y = scale.m_y > increment ? scale.m_y - increment : 0;
		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_NUM_PAD_6))
			scale.m_z = scale.m_z > increment ? scale.m_z - increment : 0;

		if (m_engine->GetWindowsWrapper()->IsKey(EKeyCode::INPUT_KEY_P))
			scale = { 1.f,1.f,1.f };

		
		engine::physic::Object** object = m_currentObject->GetGameObject()->GetPhysObject();

		m_currentObject->GetGameObject()->GetTransform()->SetScale(scale);
	}
}

void ObjectMover::LateUpdate(float deltaTime)
{

}

void ObjectMover::Exit()
{
	if (m_movableObjects.size() > 0)
	{
		m_currentObject->Select(false);
	}
}