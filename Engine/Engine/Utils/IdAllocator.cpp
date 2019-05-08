#include "IdAllocator.h"

engine::utils::IdAllocator::IdAllocator() : 
	m_currentId{ 0 }
{
}

engine::utils::IdAllocator::~IdAllocator()
{
	m_freeId.clear();
}

int engine::utils::IdAllocator::GetNewId()
{
	if (m_freeId.size() == 0)
		return m_currentId++;
	else
	{
		int id = m_freeId.back();
		m_freeId.pop_back();
		return id;
	}
}

bool engine::utils::IdAllocator::CheckExistingId(int id)
{
	for (int i{ 0 }; i < m_freeId.size(); i++)
	{
		if (m_freeId[i] == id)
			return false;
	}
	return id < m_currentId;
}

bool engine::utils::IdAllocator::CheckFreeId(int id)
{
	for (int i{ 0 }; i < m_freeId.size(); i++)
	{
		if (m_freeId[i] == id)
			return true;
	}
	return false;
}

bool engine::utils::IdAllocator::ReleaseId(int id)
{
	for (int i{ 0 }; i < m_freeId.size(); i++)
	{
		if (m_freeId[i] == id)
			return false;
	}
	if (id < m_currentId)
	{
		m_freeId.push_back(id);
		return true;
	}
	return false;
}
