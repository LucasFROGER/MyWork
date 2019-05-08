#include "ImageExtractor.h"

#include "FileProperties.h"

using namespace engine::loader;
using namespace engine::resource;
using namespace engine;

ImageExtractor::ImageExtractor(Importer* importer, ResourceMgr* resourceMgr, rhi::RHI* rhi) :
	Extractor(importer, resourceMgr, rhi)
{}

void ImageExtractor::ExtractFile(const std::string& filePath, Folder* destination, const std::string& fileName)
{
	if (destination == nullptr || m_resourceMgr == nullptr || m_rhi == nullptr)
		return;

	std::string name;
	FindValidTextureName(name, destination, fileName, GetFileName(filePath));

	int id{ m_rhi->GenTexture(filePath.data()) };
	int sampler{ m_rhi->GenStaticSampler(D3D12_FILTER_MIN_MAG_MIP_POINT, 0, 0, 0.0f, D3D12_FLOAT32_MAX) };

	Texture texture(name, id, sampler);
	Texture* texturePtr{ m_resourceMgr->Add<Texture>(texture) };
	destination->Add(texturePtr);
}