#ifndef _LOADER__EXTRACTOR_H_
#define _LOADER__EXTRACTOR_H_

#include "Importer.h"
#include "../Resource/ResourceMgr.h"
#include "../Resource/Folder.h"
#include "../RHI/Resources/ShaderEnum.h"

namespace engine
{
	namespace loader
	{
		class Extractor
		{
		public:
			static bool FindValidFolderName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidMeshName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidTextureName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidFontName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidMaterialName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidShaderName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidShaderProgramName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

			static bool FindValidSceneName(std::string& out, resource::Folder* destination,
				const std::string& fileName = "",
				const std::string& alternativeName = "");

		protected:
			Importer * m_importer;
			resource::ResourceMgr* m_resourceMgr;
			engine::rhi::RHI* m_rhi;

			Extractor(Importer* importer, resource::ResourceMgr* resourceMgr, engine::rhi::RHI* rhi);

		private:
			static bool FindValidResourceName(std::string& out, resource::Folder* destination,
				const std::string& fileName, const std::string& alternativeName, const std::string& defaultName);
		};
	}
}
#endif