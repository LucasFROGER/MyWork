#ifndef _IMPORTER_H_
#define _IMPORTER_H_

#include "../Loader/FileProperties.h"
#include "../Resource/ResourceMgr.h"
#include "../Resource/Folder.h"
#include "../RHI/RHI.h"

namespace engine
{
	namespace loader
	{
		class Importer
		{
		public:
			Importer(resource::ResourceMgr* resourceMgr, engine::rhi::RHI* rhi);

			void Import(const std::string& filePath, resource::Folder* destination, const std::string& fileName = std::string());

		private:
			resource::ResourceMgr* m_resourceMgr;
			engine::rhi::RHI* m_rhi;
		};
	}
}
#endif