#ifndef _OBJ_EXTRACTOR_H_
#define _OBJ_EXTRACTOR_H_

#include "Extractor.h"
#include "Importer.h"
#include "../Resource/ResourceMgr.h"
#include "../Resource/Folder.h"

namespace engine
{
	namespace loader
	{
		class ObjExtractor : public Extractor
		{
		public:
			ObjExtractor(Importer* importer, resource::ResourceMgr* resourceMgr, engine::rhi::RHI* rhi);

			void ExtractFile(const std::string& filePath, resource::Folder* destination, const std::string& fileName) const;

		private:
			bool ExtractMesh(const char* filePath, resource::Folder* destination, const std::string& fileName) const;

			engine::core::maths::Vec3 GenNormal(const engine::core::maths::Vec3& p1, const engine::core::maths::Vec3& p2, const engine::core::maths::Vec3& p3) const;
		};
	}
}

#endif