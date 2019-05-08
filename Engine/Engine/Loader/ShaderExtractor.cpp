#include "ShaderExtractor.h"

using namespace engine::loader;
using namespace engine::resource;
using namespace engine;

ShaderExtractor::ShaderExtractor(Importer* importer, resource::ResourceMgr* resourceMgr, rhi::RHI* rhi) :
	Extractor(importer, resourceMgr, rhi)
{}

void ShaderExtractor::ExtractFile(const std::string& filePath, Folder* destination, const std::string& fileName)
{
	if (destination == nullptr || m_resourceMgr == nullptr || m_rhi == nullptr)
		return;

	std::string name;
	FindValidShaderName(name, destination, fileName, GetFileName(filePath));

	rhi::resources::EShaderEnum type;

	switch(GetExtension(filePath))
	{
	case EExtension::VS:
		type = rhi::resources::EShaderEnum::VERTEX_SHADER;
		break;
	case EExtension::PS:
		type = rhi::resources::EShaderEnum::PIXEL_SHADER;
		break;
	case EExtension::GS:
		type = rhi::resources::EShaderEnum::GEOMETRY_SHADER;
		break;
	case EExtension::HS:
		type = rhi::resources::EShaderEnum::HULL_SHADER;
		break;
	case EExtension::DS:
		type = rhi::resources::EShaderEnum::DOMAIN_SHADER;
		break;
	default:
		return;
	}

	int id{ m_rhi->GenShader(filePath.data(), type) };

	Shader shader(name, id, type);
	Shader* shaderPtr{ m_resourceMgr->Add<Shader>(shader) };
	destination->Add(shaderPtr);
}