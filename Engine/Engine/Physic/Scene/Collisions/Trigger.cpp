#include "Trigger.h"

engine::physic::Trigger::Trigger(Object* trigger, Object* other) :
	m_trigger{ trigger },
	m_other{ other },
	m_isEntered{ false },
	m_isExited{ false },
	m_isCalled{ true }
{

}

engine::physic::Trigger::~Trigger()
{

}

void engine::physic::Trigger::Update()
{
	if (m_isCalled && !m_isExited)
	{
		if (m_isEntered == false)
		{
			m_trigger->OnTriggerEnter(TriggerInfo(m_other));
			m_isEntered = true;
			return;
		}
		m_trigger->OnTriggerStay(TriggerInfo(m_other));
		m_isCalled = false;
	}
	else if(!m_isExited)
	{
		m_isExited = true;
		if(m_trigger && m_other)
			m_trigger->OnTriggerExit(TriggerInfo(m_other));
	}
}

bool engine::physic::Trigger::Contain(Object* obj)
{
	return obj == m_trigger || obj == m_other;
}

bool engine::physic::Trigger::Check(Object* trigger, Object* other)
{
	return trigger == m_trigger && other == m_other;
}

void engine::physic::Trigger::Call()
{
	m_isCalled = true;
}

bool engine::physic::Trigger::Exit()
{
	
	return m_isExited;
}


