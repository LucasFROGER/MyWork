#include "Reseter.h"

#include "../../Fenestration/Inputs/KeyCode.h"
#include "Player.h"
#include "Trap.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

Reseter::Reseter(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_player{ nullptr },
	m_pickable{ nullptr }
{ }

void Reseter::Init()
{ }

void Reseter::Awake()
{
	m_save = *m_transform;
	m_player = m_gameObject->GetComponent<Player>();
	m_pickable = m_gameObject->GetComponent<Pickable>();
	m_trap = m_gameObject->GetComponent<Trap>();
}

void Reseter::Start()
{ }

void Reseter::Update(float deltaTime)
{ 
	if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_R))
		Reset();
}

void Reseter::LateUpdate(float deltaTime)
{ }

void Reseter::Exit()
{ 
	Reset();
}

void Reseter::Reset()
{
}
