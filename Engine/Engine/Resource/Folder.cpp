#include "Folder.h"

#include "../ResourceManagement/Explorer.h"

#pragma region Defines

#define DEFINE_PUBLIC_MEMBERS(type, VarName, varName, pl)	\
bool Folder::Add(type* varName)								\
{															\
	return Add(varName, m_##varName##pl);					\
}															\
															\
bool Folder::Remove(type* varName)							\
{															\
	return Remove(varName, m_##varName##pl);				\
}															\
															\
bool Folder::Remove##VarName(const std::string& name)		\
{															\
	return Remove(name, m_##varName##pl);					\
}															\
															\
type* Folder::Get##VarName(const std::string& name) const	\
{															\
	return Get<type>(name, m_##varName##pl);				\
}

#pragma endregion

using namespace engine::resource_management;
using namespace engine::resource;
using namespace engine::scene_graph;

engine::resource::Folder::Folder(Explorer* explorer, const std::string& name) :
	m_explorer{ explorer },
	m_name{ name }
{}

engine::resource::Folder* engine::resource::Folder::NewFolder(const std::string& folderName)
{
	if (m_explorer == nullptr)
		return nullptr;

	return m_explorer->NewFolder(this, folderName);
}

std::string engine::resource::Folder::GetAvailableName(const std::string& folderName) const
{
	std::string name{ folderName };

	auto it{ m_folders.find(name) };
	auto end{ m_folders.end() };

	for (size_t id{ 1 }; it != end; ++id)
	{
		name = folderName + ' ' + std::to_string(id);
		it = m_folders.find(name);
	}

	return name;
}

const std::string& engine::resource::Folder::GetName() const
{
	return m_name;
}

DEFINE_PUBLIC_MEMBERS(Folder,			Folder,			folder,			s)
DEFINE_PUBLIC_MEMBERS(Mesh,				Mesh,			mesh,			es)
DEFINE_PUBLIC_MEMBERS(Texture,			Texture,		texture,		s)
DEFINE_PUBLIC_MEMBERS(Font,				Font,			font,			s)
DEFINE_PUBLIC_MEMBERS(Material,			Material,		material,		s)
DEFINE_PUBLIC_MEMBERS(Shader,			Shader,			shader,			s)
DEFINE_PUBLIC_MEMBERS(ShaderProgram,	ShaderProgram,	shaderProgram,	s)
DEFINE_PUBLIC_MEMBERS(Scene,			Scene,			scene,			s)
DEFINE_PUBLIC_MEMBERS(GameObject,		GameObject,		gameObject,		s)

#pragma region Undefs
#undef DEFINE_PUBLIC_MEMBERS
#pragma endregion
