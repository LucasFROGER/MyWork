#include "GUIMgr.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

GUIMgr::GUIMgr(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_infoTextRenderer{ nullptr }
{

}

void GUIMgr::Init()
{

}

void GUIMgr::Awake()
{
	if (m_infoTextRenderer)
		m_infoTextRenderer->SetText("");
}

void GUIMgr::Start()
{

}

void GUIMgr::Update(float deltaTime)
{

}

void GUIMgr::LateUpdate(float deltaTime)
{

}

void GUIMgr::Exit()
{
	if (m_infoTextRenderer)
		m_infoTextRenderer->SetText("");
}

void GUIMgr::OnCollisionEnter(engine::physic::CollisionInfo info)
{ }

void GUIMgr::OnCollisionStay(engine::physic::CollisionInfo info)
{ }

void GUIMgr::OnCollisionExit(engine::physic::CollisionInfo info)
{ }

void GUIMgr::OnTriggerEnter(engine::physic::TriggerInfo info)
{ }

void GUIMgr::OnTriggerStay(engine::physic::TriggerInfo info)
{ }

void GUIMgr::OnTriggerExit(engine::physic::TriggerInfo info)
{ }

void GUIMgr::SetInfoTextRenderer(engine::component::TextRenderer* renderer)
{
	m_infoTextRenderer = renderer;
}

void GUIMgr::SetPauseMenu(Menu* menu)
{
	m_pauseMenu = menu;
}

void GUIMgr::SetInfoText(const char* str)
{
	if(m_infoTextRenderer)
		m_infoTextRenderer->SetText(str);
}

const char* GUIMgr::GetInfoText()
{
	if (m_infoTextRenderer)
		return m_infoTextRenderer->GetText();
	return "";
}

void GUIMgr::OpenPauseMenu()
{
	if (m_pauseMenu)
		m_pauseMenu->Open();
}

void GUIMgr::ClosePauseMenu()
{
	if (m_pauseMenu)
		m_pauseMenu->Close();
}
