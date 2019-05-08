#ifndef _FONT_EXTRACTOR_H_
#define _FONT_EXTRACTOR_H_

#include "Extractor.h"
#include "Importer.h"
#include "../Resource/ResourceMgr.h"
#include "../Resource/Folder.h"

namespace engine
{
	namespace loader
	{
		class FontExtractor : public Extractor
		{
		public:
			FontExtractor(Importer* importer, resource::ResourceMgr* resourceMgr, engine::rhi::RHI* rhi);

			void ExtractFile(const std::string& filePath, resource::Folder* destination, const std::string& fileName);
		};
	}
}




#endif