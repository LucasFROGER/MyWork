#include "Collision.h"

engine::physic::Collision::Collision(Object* Collision, Object* other) :
	m_collision{ Collision },
	m_other{ other },
	m_isEntered{ false },
	m_isExited{ false },
	m_isCalled{ true }
{

}

engine::physic::Collision::~Collision()
{

}

void engine::physic::Collision::Update()
{
	if (m_isCalled && !m_isExited)
	{
		if (m_isEntered == false)
		{
			m_collision->OnCollisionEnter(CollisionInfo(m_other));
			m_isEntered = true;
			return;
		}
		m_collision->OnCollisionStay(CollisionInfo(m_other));
		m_isCalled = false;
	}
	else
	{
		m_isExited = true;
		m_collision->OnCollisionExit(CollisionInfo(m_other));
	}
}

bool engine::physic::Collision::Contain(Object* obj)
{
	return obj == m_collision || obj == m_other;
}

bool engine::physic::Collision::Check(Object* collision, Object* other)
{
	return collision == m_collision && other == m_other;
}

void engine::physic::Collision::Call()
{
	m_isCalled = true;
}

bool engine::physic::Collision::Exit()
{
	return m_isExited;
}


