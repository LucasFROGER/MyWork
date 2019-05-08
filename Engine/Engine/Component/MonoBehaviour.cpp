#include "MonoBehaviour.h"

void engine::component::MonoBehaviour::PreProcess()
{
	if (m_child != nullptr)
	{
		switch (m_state)
		{
		case BehaviourState::NONE:
			m_state = BehaviourState::START;
			m_child->Start();
			break;
		}
	}
}

void engine::component::MonoBehaviour::Process(float deltaTime)
{
	if (m_child != nullptr)
	{
		switch (m_state)
		{
		case BehaviourState::START:
			m_state = BehaviourState::UPDATE;
			m_child->Update(deltaTime);
			break;
		case BehaviourState::UPDATE:
			m_child->Update(deltaTime);
			break;
		}
	}
}

void engine::component::MonoBehaviour::FixedProcess(float deltaTime)
{
	if (m_child != nullptr)
	{
		switch (m_state)
		{
		case BehaviourState::START:
			m_state = BehaviourState::UPDATE;
			m_child->FixedUpdate(deltaTime);
			break;
		case BehaviourState::UPDATE:
			m_child->FixedUpdate(deltaTime);
			break;
		}
	}
}

void engine::component::MonoBehaviour::LateProcess(float deltaTime)
{
	if (m_child != nullptr)
	{
		if (m_state == BehaviourState::UPDATE)
			m_child->LateUpdate(deltaTime);
	}
}

void engine::component::MonoBehaviour::OnExit()
{
	if (m_child != nullptr)
	{
			Exit();
	}
}
