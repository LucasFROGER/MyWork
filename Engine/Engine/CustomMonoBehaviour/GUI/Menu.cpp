#include "Menu.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;
using namespace engine::component;

Menu::Menu(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_selected{ -1 },
	m_open{ false }
{ }

void Menu::Init()
{ }

void Menu::Awake()
{ 
	m_textRenderer = m_gameObject->GetComponent<TextRenderer>();
}

void Menu::Start()
{ }

void Menu::Update(float deltaTime)
{ 
	if (m_open)
	{
		if (m_selected == -1)
			return;

		m_textRenderer->SetText("Menu");

		if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_ENTER) && !m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_W) 
			&& !m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_S))
		{
			m_buttons[m_selected]->Execute();
		}
		if (m_buttons.size() < 2)
			return;
		if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_W))
		{
			if (m_selected == 0)
			{
				m_buttons[m_selected]->Select(false);
				m_selected = m_buttons.size() - 1;
				m_buttons[m_selected]->Select(true);
			}
			else
			{
				m_buttons[m_selected]->Select(false);
				--m_selected;
				m_buttons[m_selected]->Select(true);
			}
		}
		if (m_engine->GetWindowsWrapper()->IsKeyDown(EKeyCode::INPUT_KEY_S))
		{
			if (m_selected == m_buttons.size() - 1)
			{
				m_buttons[m_selected]->Select(false);
				m_selected = 0;
				m_buttons[m_selected]->Select(true);
			}
			else
			{
				m_buttons[m_selected]->Select(false);
				++m_selected;
				m_buttons[m_selected]->Select(true);
			}
		}

	}
	else
		m_textRenderer->SetText("");


}

void Menu::LateUpdate(float deltaTime)
{ }

void Menu::Exit()
{ 
	Close();
}

void Menu::OnCollisionEnter(engine::physic::CollisionInfo info)
{ }

void Menu::OnCollisionStay(engine::physic::CollisionInfo info)
{ }

void Menu::OnCollisionExit(engine::physic::CollisionInfo info)
{ }

void Menu::OnTriggerEnter(engine::physic::TriggerInfo info)
{ }

void Menu::OnTriggerStay(engine::physic::TriggerInfo info)
{ }

void Menu::OnTriggerExit(engine::physic::TriggerInfo info)
{ }

void Menu::AddButton(Button* button)
{
	m_buttons.push_back(button);
}

void Menu::Open()
{
	if (m_open == false)
	{
		m_open = true;
		for (int i{ 0 }; i < m_buttons.size(); ++i)
		{
			m_buttons[i]->Displayed(true);
		}
		if (m_buttons.size() > 0)
		{
			m_selected = 0;
			m_buttons[m_selected]->Select(true);
		}
	}
}

void Menu::Close()
{
	if (m_open == true)
	{
		m_open = false;
		for (int i{ 0 }; i < m_buttons.size(); ++i)
		{
			m_buttons[i]->Displayed(false);
		}
		if (m_selected != -1)
		{
			m_buttons[m_selected]->Select(false);
			m_selected = -1;
		}
	}
}
