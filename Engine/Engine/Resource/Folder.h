#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <unordered_map>

#include "Mesh.h"
#include "Texture.h"
#include "Font.h"
#include "Material.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "../SceneGraph/Scene.h"
#include "../SceneGraph/GameObject.h"

#pragma region Defines

#define DECLARE_PUBLIC_MEMBERS(type, VarName, varName, pl)	\
	bool Add(type* varName);								\
	bool Remove(type* varName);								\
	bool Remove##VarName(const std::string& name);			\
	type* Get##VarName(const std::string& name) const;

#define DECLARE_PRIVATE_MEMBERS(type, varName, pl)	\
	std::unordered_map<std::string, type*> m_##varName##pl;

#pragma endregion

namespace engine
{
	namespace resource_management { class Explorer; }

	namespace resource
	{
		class Folder
		{
		public:
			resource::Folder(resource_management::Explorer* explorer, const std::string& name);

			resource::Folder* NewFolder(const std::string& folderName);

			std::string GetAvailableName(const std::string& folderName) const;

			const std::string&		 GetName() const;

			DECLARE_PUBLIC_MEMBERS(Folder,					Folder,			folder,			s)
			DECLARE_PUBLIC_MEMBERS(Mesh,					Mesh,			mesh,			es)
			DECLARE_PUBLIC_MEMBERS(Texture,					Texture,		texture,		s)
			DECLARE_PUBLIC_MEMBERS(Font,					Font,			font,			s)
			DECLARE_PUBLIC_MEMBERS(Material,				Material,		material,		s)
			DECLARE_PUBLIC_MEMBERS(Shader,					Shader,			shader,			s)
			DECLARE_PUBLIC_MEMBERS(ShaderProgram,			ShaderProgram,	shaderProgram,	s)
			DECLARE_PUBLIC_MEMBERS(scene_graph::Scene,		Scene,			scene,			s)
			DECLARE_PUBLIC_MEMBERS(scene_graph::GameObject,	GameObject,		gameObject,		s)

		private:
			std::string m_name;
			resource_management::Explorer* m_explorer;

			DECLARE_PRIVATE_MEMBERS(Folder,						folder,			s)
			DECLARE_PRIVATE_MEMBERS(Mesh,						mesh,			es)
			DECLARE_PRIVATE_MEMBERS(Texture,					texture,		s)
			DECLARE_PRIVATE_MEMBERS(Font,						font,			s)
			DECLARE_PRIVATE_MEMBERS(Material,					material,		s)
			DECLARE_PRIVATE_MEMBERS(Shader,						shader,			s)
			DECLARE_PRIVATE_MEMBERS(ShaderProgram,				shaderProgram,	s)
			DECLARE_PRIVATE_MEMBERS(scene_graph::Scene,			scene,			s)
			DECLARE_PRIVATE_MEMBERS(scene_graph::GameObject,	gameObject,		s)

			template<typename ptrType, typename umapType>
			bool Add(ptrType ptr, umapType& unorderedMap);

			template<typename ptrType, typename umapType>
			bool Remove(ptrType ptr, umapType& unorderedMap);
			template<typename umapType>
			bool Remove(const std::string& name, umapType& unorderedMap);

			template<typename T, typename umapType>
			T* Get(const std::string& name, umapType& unorderedMap) const;
		};
	}

	template<typename ptrType, typename umapType>
	bool resource::Folder::Add(ptrType ptr, umapType& unorderedMap)
	{
		if (ptr == nullptr)
			return false;

		auto pair{ unorderedMap.emplace(ptr->GetName(), ptr) };
		return pair.second;
	}

	template<typename ptrType, typename umapType>
	bool resource::Folder::Remove(ptrType ptr, umapType& unorderedMap)
	{
		if (ptr == nullptr)
			return false;

		auto it{ unorderedMap.begin() };
		auto end{ unorderedMap.end() };

		for (; it != end; ++it)
		{
			if (it->second == ptr)
			{
				unorderedMap.erase(it);
				return true;
			}
		}

		return false;
	}

	template<typename umapType>
	bool resource::Folder::Remove(const std::string& name, umapType& unorderedMap)
	{
		auto it{ unorderedMap.find(name) };
		if (it != unorderedMap.end())
		{
			unorderedMap.erase(it);
			return true;
		}

		return false;
	}

	template<typename T, typename umapType>
	T* resource::Folder::Get(const std::string& name, umapType& unorderedMap) const
	{
		auto it{ unorderedMap.find(name) };
		if (it != unorderedMap.end())
			return it->second;

		return nullptr;
	}
}

#pragma region Undefs
#undef DECLARE_PRIVATE_MEMBERS
#undef DECLARE_PUBLIC_MEMBERS
#pragma endregion

#endif
