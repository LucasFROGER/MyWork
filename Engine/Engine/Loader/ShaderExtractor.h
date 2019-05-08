#ifndef _LOADER__SHADER_EXTRACTOR_H_
#define _LOADER__SHADER_EXTRACTOR_H_

#include "Extractor.h"
#include "Importer.h"
#include "../Resource/ResourceMgr.h"
#include "../Resource/Folder.h"
#include "../RHI/Resources/ShaderEnum.h"

namespace engine
{
	namespace loader
	{
		class ShaderExtractor : public Extractor
		{
		public:
			ShaderExtractor(Importer* importer, resource::ResourceMgr* resourceMgr, engine::rhi::RHI* rhi);

			void ExtractFile(const std::string& filePath, resource::Folder* destination, const std::string& fileName);
		};
	}
}

#endif