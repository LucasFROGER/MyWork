#include "Button.h"

#include "../../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

Button::Button(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this),
	m_str{ "" },
	m_function{ nullptr },
	m_displayed{ false },
	m_selected{ false },
	m_textRenderer{ nullptr }
{ }

void Button::Init()
{ }

void Button::Awake()
{ 
	m_textRenderer = m_gameObject->GetComponent<engine::component::TextRenderer>();
	if (m_textRenderer)
		m_textRenderer->SetText("");
	if (m_textRenderer)
		m_textRenderer->SetPosition(m_pos);
}

void Button::Start()
{ 
	
}

void Button::Update(float deltaTime)
{ 
	if (m_displayed)
	{
		if (m_selected)
		{
			if (m_textRenderer)
				m_textRenderer->SetText((" > " + m_str).c_str());
		}
		else
		{
			if (m_textRenderer)
				m_textRenderer->SetText(("   " + m_str).c_str());
		}
	}
	else
		if (m_textRenderer)
			m_textRenderer->SetText("");
}

void Button::LateUpdate(float deltaTime)
{ }

void Button::Exit()
{ 
	if (m_textRenderer)
		m_textRenderer->SetText("");
}

void Button::OnCollisionEnter(engine::physic::CollisionInfo info)
{ }

void Button::OnCollisionStay(engine::physic::CollisionInfo info)
{ }

void Button::OnCollisionExit(engine::physic::CollisionInfo info)
{ }

void Button::OnTriggerEnter(engine::physic::TriggerInfo info)
{ }

void Button::OnTriggerStay(engine::physic::TriggerInfo info)
{ }

void Button::OnTriggerExit(engine::physic::TriggerInfo info)
{ }

void Button::SetTextRenderer(engine::component::TextRenderer* textRenderer)
{
	m_textRenderer = textRenderer;
}

void Button::SetPosition(engine::core::maths::Vec2 pos)
{
	m_pos = pos;
	if (m_textRenderer)
	{
		m_textRenderer->SetPosition(pos);
	}
}

void Button::SetText(const char* text)
{
	m_str = text;
}

void Button::SetFunction(std::function<void(void)> function)
{
	m_function = function;
}

void Button::Select(bool selected)
{
	m_selected = selected;
}

void Button::Displayed(bool displayed)
{
	m_displayed = displayed;
}

void Button::Execute()
{
	if (m_function)
		m_function();
}
