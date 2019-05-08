#include "ResourceMgr.h"

using namespace engine::resource;

ResourceMgr::~ResourceMgr()
{
	ClearAllResources();
}

void ResourceMgr::ClearAllResources(bool shrinkToFit)
{
	auto aisle{ m_warehouse.begin() };
	auto end{ m_warehouse.end() };

	for (; aisle != end; ++aisle)
	{
		for (void*& resource : aisle->second)
		{
			if (resource != nullptr)
			{
				delete resource;
				resource = nullptr;
			}
		}

		aisle->second.clear();
	}

	if (shrinkToFit)
		m_warehouse.clear();
}
