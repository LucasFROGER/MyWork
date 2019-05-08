#include "CollisionMgr.h"

engine::physic::CollisionMgr::CollisionMgr()
{

}

void engine::physic::CollisionMgr::Update()
{

}

void engine::physic::CollisionMgr::FixedUpdate()
{
	for (int i{ 0 }; i < m_triggers.size(); ++i)
	{
		m_triggers[i].Update();
	}


	for (int i{ 0 }; i < m_triggers.size(); ++i)
	{
		if (m_triggers[i].Exit())
			m_triggers.erase(m_triggers.begin() + i);
	}

	for (int i{ 0 }; i < m_collisions.size(); ++i)
	{
		m_collisions[i].Update();
	}
	for (int i{ 0 }; i < m_collisions.size(); ++i)
	{
		if (m_collisions[i].Exit())
			m_collisions.erase(m_collisions.begin() + i);
	}
}

void engine::physic::CollisionMgr::ObjectsTrigger(Object* trigger, Object* other)
{
	for (int i{ 0 }; i < m_triggers.size(); ++i)
	{
		if(m_triggers[i].Check(trigger, other))
		{
			m_triggers[i].Call();
			return;
		}
	}
	m_triggers.push_back(Trigger(trigger, other));
}

void engine::physic::CollisionMgr::ObjectsCollision(Object* collision, Object* other)
{
	for (int i{ 0 }; i < m_collisions.size(); ++i)
	{
		if (m_collisions[i].Check(collision, other))
		{
			m_collisions[i].Call();
			return;
		}
	}
	m_collisions.push_back(Collision(collision, other));
}

void engine::physic::CollisionMgr::RemoveObject(Object* obj)
{
	for (int i{ 0 }; i < m_triggers.size(); ++i)
	{
		if (m_triggers[i].Contain(obj))
			m_triggers.erase(m_triggers.begin() + i);
	}

	for (int i{ 0 }; i < m_collisions.size(); ++i)
	{
		if (m_collisions[i].Contain(obj))
			m_collisions.erase(m_collisions.begin() + i);
	}
}
