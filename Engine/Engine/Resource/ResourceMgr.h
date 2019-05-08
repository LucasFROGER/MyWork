#ifndef _RESOURCE_MGR_H_
#define _RESOURCE_MGR_H_

#include <unordered_map>

namespace engine
{
	namespace resource
	{
		class ResourceMgr
		{
		public:
			ResourceMgr() = default;
			~ResourceMgr();

			template<typename T, typename... Args>
			T*				  Add(Args&&... args);

			template<typename T>
			bool Remove(T* resource);

			template<typename T>
			void ClearAllResourcesOfType(bool shrinkToFit = false);
			void ClearAllResources(bool shrinkToFit = false);

		private:
			std::unordered_map<std::string, std::vector<void*>> m_warehouse;

			template<typename T>
			void StoreResource(T* resource);

		};
	}

	template<typename T, typename... Args>
	T* resource::ResourceMgr::Add(Args&&... args)
	{
		T* resource{ new T(std::forward<Args>(args)...) };
		StoreResource(resource);
		return resource;
	}

	template<typename T>
	bool resource::ResourceMgr::Remove(T* resource)
	{
		if (resource == nullptr)
			return false;

		std::string typeOfResource{ typeid(toy).name() };

		auto aisle{ m_warehouse.find(typeOfResource) };
		if (aisle != m_warehouse.end())
		{
			auto resourceToRemove{ std::find(aisle->second.begin(), aisle->second.end(), resource) };
			if (resourceToRemove != aisle->second.end())
			{
				aisle->second.erase(resourceToRemove);
				return true;
			}
		}

		return false;
	}

	template<typename T>
	void resource::ResourceMgr::ClearAllResourcesOfType(bool shrinkToFit)
	{
		std::string typeOfResource{ typeid(T*).name() };

		auto aisle{ m_warehouse.find(typeOfResource) };
		if (aisle != m_warehouse.end())
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

			if (shrinkToFit)
				m_warehouse.erase(aisle);
		}
	}

	template<typename T>
	void resource::ResourceMgr::StoreResource(T* resource)
	{
		if (resource == nullptr)
			return;

		std::string typeOfResource(typeid(resource).name());

		auto aisle{ m_warehouse.find(typeOfResource) };

		if (aisle != m_warehouse.end())
			aisle->second.emplace_back(resource);
		else
			m_warehouse.emplace(typeOfResource, std::vector<void*>{ resource });
	}
}
#endif