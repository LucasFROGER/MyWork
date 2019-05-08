#include "Importer.h"

#include "ObjExtractor.h"
#include "FbxExtractor.h"
#include "ImageExtractor.h"
#include "FontExtractor.h"
#include "ShaderExtractor.h"

using namespace engine::loader;
using namespace engine::resource;
using namespace engine;

Importer::Importer(ResourceMgr* resourceMgr, rhi::RHI* rhi) :
	m_resourceMgr{ resourceMgr },
	m_rhi{ rhi }
{}

void Importer::Import(const std::string& filePath, Folder* destination, const std::string& fileName)
{
	switch (GetExtension(filePath))
	{
	case EExtension::FBX:
		FbxExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::OBJ:
		ObjExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::JPG:
		ImageExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::PNG:
		ImageExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::VS:
		ShaderExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::PS:
		ShaderExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::GS:
		ShaderExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::HS:
		ShaderExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::DS:
		ShaderExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	case EExtension::MP3:
		break;
	case EExtension::WAV:
		break;
	case EExtension::OGG:
		break;
	case EExtension::FLAC:
		break;
	
	case EExtension::FNT:
		FontExtractor(this, m_resourceMgr, m_rhi).ExtractFile(filePath, destination, fileName);
		break;
	}
}
