#include "Extractor.h"

#define DEFAULT_FOLDER_NAME				"New Folder"
#define DEFAULT_MESH_NAME				"New Mesh"
#define DEFAULT_TEXTURE_NAME			"New Texture"
#define DEFAULT_FONT_NAME				"New Font"
#define DEFAULT_MATERIAL_NAME			"New Material"
#define DEFAULT_SHADER_NAME				"New Program"
#define DEFAULT_SHADER_PROGRAM_NAME		"New ShaderProgram"
#define DEFAULT_SCENE_NAME				"New Scene"

using namespace engine::resource;

engine::loader::Extractor::Extractor(Importer* importer, ResourceMgr* resourceMgr, rhi::RHI* rhi) :
	m_importer{ importer },
	m_resourceMgr{ resourceMgr },
	m_rhi{ rhi }
{}

bool engine::loader::Extractor::FindValidFolderName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_FOLDER_NAME);
}

bool engine::loader::Extractor::FindValidMeshName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_MESH_NAME);
}

bool engine::loader::Extractor::FindValidTextureName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_TEXTURE_NAME);
}

bool engine::loader::Extractor::FindValidFontName(std::string & out, resource::Folder * destination, const std::string & fileName, const std::string & alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_FONT_NAME);
}

bool engine::loader::Extractor::FindValidMaterialName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_MATERIAL_NAME);
}

bool engine::loader::Extractor::FindValidShaderName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_SHADER_NAME);
}

bool engine::loader::Extractor::FindValidShaderProgramName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_SHADER_PROGRAM_NAME);
}

bool engine::loader::Extractor::FindValidSceneName(std::string& out, Folder* destination,
	const std::string& fileName, const std::string& alternativeName)
{
	return FindValidResourceName(out, destination, fileName, alternativeName, DEFAULT_SCENE_NAME);
}

bool engine::loader::Extractor::FindValidResourceName(std::string& out, resource::Folder* destination,
	const std::string& fileName, const std::string& alternativeName, const std::string& defaultName)
{
	if (destination == nullptr)
		return false;

	std::string name;

	if (fileName != std::string())
		name = destination->GetAvailableName(fileName);
	else if (alternativeName != std::string())
		name = destination->GetAvailableName(alternativeName);
	else
		name = destination->GetAvailableName(defaultName);

	out = name;
	return true;
}

#undef DEFAULT_SCENE_NAME
#undef DEFAULT_SHADER_PROGRAM_NAME
#undef DEFAULT_SHADER_NAME
#undef DEFAULT_MATERIAL_NAME
#undef DEFAULT_TEXTURE_NAME
#undef DEFAULT_MESH_NAME
