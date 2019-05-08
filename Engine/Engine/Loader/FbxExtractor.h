#ifndef _FBX_EXTRACTOR_H_
#define _FBX_EXTRACTOR_H_

#include "fbxsdk.h"
#ifdef FBXSDK_SHARED
#pragma comment(lib, "libfbxsdk.lib")
#else
#pragma comment(lib, "libfbxsdk-md.lib")
#endif

#include "Extractor.h"
#include "Importer.h"
#include "../Resource/ResourceMgr.h"
#include "../Resource/Folder.h"
#include "../Resource/Texture.h"

namespace engine
{
	namespace loader
	{
		class FbxExtractor : public Extractor
		{
		public:
			FbxExtractor(Importer* importer, resource::ResourceMgr* resourceMgr, engine::rhi::RHI* rhi);

			void ExtractFile(const std::string& filePath, resource::Folder* destination, const std::string& fileName) const;

		private:
			void ProcessNode(FbxNode* node, resource::Folder* destination, const std::string& fileName) const;

			bool ExtractMesh(FbxNode* node, resource::Folder* destination, const std::string& fileName) const;

			void ExtractMaterial(FbxNode* node, resource::Folder* destination, const std::string& fileName) const;

			void ExtractTextures(resource::Folder* destination,
				const FbxSurfaceMaterial* fbxMaterial, const char* materialType) const;

			std::vector<resource::Texture*> GetTextures(resource::Folder* destination,
				const FbxSurfaceMaterial* fbxMaterial, const char* materialType) const;

			engine::core::maths::Vec4 GetColor(const FbxSurfaceMaterial* fbxMaterial, const char* materialType) const;

			float GetFactor(const FbxSurfaceMaterial* fbxMaterial, const char* factorType) const;

			FbxNodeAttribute::EType GetNodeAttribute(FbxNode* node) const;
		};
	}
}
#endif