#include "GameMgr.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

GameMgr::GameMgr(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_player{ nullptr },
	m_guiMgr{ nullptr },
	m_paused{ false }
{ }

void GameMgr::Init()
{ 

}

void GameMgr::Awake()
{ 
	m_paused = false;
	m_player = m_gameObject->GetScene()->FindObjectOfType<Player>();
	m_guiMgr = m_gameObject->GetScene()->FindObjectOfType<GUIMgr>();
	m_pickables = m_gameObject->GetScene()->FindAllObjectsOfType<Pickable>();
}

void GameMgr::Start()
{ }

void GameMgr::Update(float deltaTime)
{ 
	if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_ESCAPE))
		Pause();
}

void GameMgr::LateUpdate(float deltaTime)
{ }

void GameMgr::Exit()
{ 
	m_player = nullptr;
	m_pickables.clear();
}

void GameMgr::OnCollisionEnter(engine::physic::CollisionInfo info)
{ }

void GameMgr::OnCollisionStay(engine::physic::CollisionInfo info)
{ }

void GameMgr::OnCollisionExit(engine::physic::CollisionInfo info)
{ }

void GameMgr::OnTriggerEnter(engine::physic::TriggerInfo info)
{ }

void GameMgr::OnTriggerStay(engine::physic::TriggerInfo info)
{ }

void GameMgr::OnTriggerExit(engine::physic::TriggerInfo info)
{ }

void GameMgr::SetGuiMgr(GUIMgr* guiMgr)
{
	m_guiMgr = guiMgr;
}

void GameMgr::Pause()
{
	if (m_paused == false)
	{
		m_paused = true;
		m_player->Pause(m_paused);
		for (int i{ 0 }; i < m_pickables.size(); ++i)
		{
			m_pickables[i]->Pause(m_paused);
		}
		m_guiMgr->OpenPauseMenu();
	}
}

void GameMgr::Resume()
{
	if (m_paused == true)
	{
		m_paused = false;
		m_player->Pause(m_paused);
		for (int i{ 0 }; i < m_pickables.size(); ++i)
		{
			m_pickables[i]->Pause(m_paused);
		}
		m_guiMgr->ClosePauseMenu();
	}
}
