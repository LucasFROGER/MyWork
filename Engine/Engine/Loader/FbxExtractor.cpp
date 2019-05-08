#include "FbxExtractor.h"

#include "../Resource/Mesh.h"
#include "../Resource/Material.h"

using namespace engine::loader;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine;

engine::loader::FbxExtractor::FbxExtractor(Importer* importer, ResourceMgr* resourceMgr, rhi::RHI* rhi) :
	Extractor(importer, resourceMgr, rhi)
{}

void engine::loader::FbxExtractor::ExtractFile(const std::string& filePath, Folder* destination, const std::string& fileName) const
{
	FbxManager* fbxMgr{ FbxManager::Create() };
	fbxMgr->SetIOSettings(FbxIOSettings::Create(fbxMgr, IOSROOT));

	FbxScene* scene{ FbxScene::Create(fbxMgr, "") };

	FbxImporter* fbxImporter{ FbxImporter::Create(fbxMgr, "") };
	FbxIOSettings* ioSettings{ fbxMgr->GetIOSettings() };
	fbxImporter->Initialize(filePath.c_str(), -1, ioSettings);
	fbxImporter->Import(scene);
	fbxImporter->Destroy();

	FbxGeometryConverter geometryConverter(fbxMgr);
	geometryConverter.Triangulate(scene, true);

	FbxNode* rootNode{ scene->GetRootNode() };
	int childCount{ rootNode->GetChildCount() };

	for (int index{ 0 }; index < childCount; ++index)
	{
		ProcessNode(rootNode->GetChild(index), destination, fileName);
	}
}

void engine::loader::FbxExtractor::ProcessNode(FbxNode* node, Folder* destination, const std::string& fileName) const
{
	if (node == nullptr || destination == nullptr || m_resourceMgr == nullptr)
		return;

	destination = destination->NewFolder(node->GetName());
	if (destination == nullptr)
		return;

	ExtractMaterial(node, destination, fileName);

	switch (GetNodeAttribute(node))
	{
	case FbxNodeAttribute::EType::eUnknown:
		break;
	case FbxNodeAttribute::EType::eNull:
		break;
	case FbxNodeAttribute::EType::eMarker:
		break;
	case FbxNodeAttribute::EType::eSkeleton:
		break;
	case FbxNodeAttribute::EType::eMesh:
		ExtractMesh(node, destination, fileName);
		break;
	case FbxNodeAttribute::EType::eNurbs:
		break;
	case FbxNodeAttribute::EType::ePatch:
		break;
	case FbxNodeAttribute::EType::eCamera:
		break;
	case FbxNodeAttribute::EType::eCameraStereo:
		break;
	case FbxNodeAttribute::EType::eCameraSwitcher:
		break;
	case FbxNodeAttribute::EType::eLight:
		break;
	case FbxNodeAttribute::EType::eOpticalReference:
		break;
	case FbxNodeAttribute::EType::eOpticalMarker:
		break;
	case FbxNodeAttribute::EType::eNurbsCurve:
		break;
	case FbxNodeAttribute::EType::eTrimNurbsSurface:
		break;
	case FbxNodeAttribute::EType::eBoundary:
		break;
	case FbxNodeAttribute::EType::eNurbsSurface:
		break;
	case FbxNodeAttribute::EType::eShape:
		break;
	case FbxNodeAttribute::EType::eLODGroup:
		break;
	case FbxNodeAttribute::EType::eSubDiv:
		break;
	case FbxNodeAttribute::EType::eCachedEffect:
		break;
	case FbxNodeAttribute::EType::eLine:
		break;
	default:
		break;
	}

	int childCount{ node->GetChildCount() };
	for (int index{ 0 }; index < childCount; ++index)
	{
		ProcessNode(node->GetChild(index), destination, fileName);
	}
}

bool engine::loader::FbxExtractor::ExtractMesh(FbxNode* node, Folder* destination, const std::string& fileName) const
{
	if (node == nullptr || destination == nullptr || m_resourceMgr == nullptr)
		return false;

	FbxMesh* fbxMesh{ node->GetMesh() };
	if (fbxMesh == nullptr)
		return false;

	std::string name;
	FindValidMeshName(name, destination, fileName, node->GetName());

	Mesh mesh(name);
	Mesh* meshPtr{ m_resourceMgr->Add<Mesh>(mesh) };

	FbxVector4 position;
	FbxVector4 normal;
	FbxVector2 uv;
	int polyCount = fbxMesh->GetPolygonCount();
	int polySize = fbxMesh->GetPolygonSize(0);
	int indicesNb = polyCount * polySize;

	meshPtr->SetIBOCapacity(indicesNb);
	meshPtr->SetVBOCapacity(indicesNb);

	for (int i{ 0 }; i < indicesNb; ++i)
		meshPtr->AddIndex(i);

	// /!\ Underutilized property
	FbxStringList nameListUV;
	fbxMesh->GetUVSetNames(nameListUV);
	int totalUVChannels = nameListUV.GetCount();

	for (int polyID{ 0 }; polyID < polyCount; ++polyID)
	{
		for (int vertexID{ 0 }; vertexID < polySize; ++vertexID)
		{
			position = fbxMesh->GetControlPointAt(fbxMesh->GetPolygonVertex(polyID, vertexID));
			fbxMesh->GetPolygonVertexNormal(polyID, vertexID, normal);

			// /!\ Underutilized property
			for (int uvChannel{ 0 }; uvChannel < totalUVChannels; ++uvChannel)
			{
				const char* nameUV = nameListUV.GetStringAt(uvChannel);
				bool isUnMapped;
				fbxMesh->GetPolygonVertexUV(polyID, vertexID, nameUV, uv, isUnMapped);
			}

			meshPtr->AddVertex(Vertex(
				Vec3((float)position.mData[0], (float)position.mData[1], (float)position.mData[2]),
				Vec3((float)normal.mData[0], (float)normal.mData[1], (float)normal.mData[2]),
				Vec2((float)uv.mData[0], (float)uv.mData[1])
			));
		}
	}

	destination->Add(meshPtr);

	return true;
}

void engine::loader::FbxExtractor::ExtractMaterial(FbxNode* node, Folder* destination, const std::string& fileName) const
{
	if (node == nullptr || destination == nullptr || m_resourceMgr == nullptr)
		return;

	int materialCount = node->GetMaterialCount();

	for (int materialID{ 0 }; materialID < materialCount; ++materialID)
	{
		FbxSurfaceMaterial* fbxMaterial = node->GetMaterial(materialID);

		std::string name;
		FindValidMaterialName(name, destination, fileName, fbxMaterial->GetNameOnly().Buffer());

		Material material(name);
		Material* materialPtr{ m_resourceMgr->Add<Material>(material) };

		ExtractTextures(destination, fbxMaterial, FbxSurfaceMaterial::sAmbient);
		ExtractTextures(destination, fbxMaterial, FbxSurfaceMaterial::sDiffuse);
		ExtractTextures(destination, fbxMaterial, FbxSurfaceMaterial::sSpecular);

		materialPtr->Insert(0, GetTextures(destination, fbxMaterial, FbxSurfaceMaterial::sAmbient));
		materialPtr->Insert(1, GetTextures(destination, fbxMaterial, FbxSurfaceMaterial::sDiffuse));
		materialPtr->Insert(2, GetTextures(destination, fbxMaterial, FbxSurfaceMaterial::sSpecular));

		materialPtr->Insert(0, GetColor(fbxMaterial, FbxSurfaceMaterial::sAmbient));
		materialPtr->Insert(1, GetColor(fbxMaterial, FbxSurfaceMaterial::sDiffuse));
		materialPtr->Insert(2, GetColor(fbxMaterial, FbxSurfaceMaterial::sSpecular));

		materialPtr->Insert(0, GetFactor(fbxMaterial, FbxSurfaceMaterial::sAmbientFactor));
		materialPtr->Insert(1, GetFactor(fbxMaterial, FbxSurfaceMaterial::sDiffuseFactor));
		materialPtr->Insert(2, GetFactor(fbxMaterial, FbxSurfaceMaterial::sSpecularFactor));
		materialPtr->Insert(3, GetFactor(fbxMaterial, FbxSurfaceMaterial::sShininess));

		destination->Add(materialPtr);
	}
}

void engine::loader::FbxExtractor::ExtractTextures(Folder* destination,
	const FbxSurfaceMaterial* fbxMaterial, const char* materialType) const
{
	if (destination == nullptr || fbxMaterial == nullptr || m_importer == nullptr)
		return;

	const FbxProperty materialProperty = fbxMaterial->FindProperty(materialType);
	if (!materialProperty.IsValid())
		return;

	const int textureCount = materialProperty.GetSrcObjectCount<FbxFileTexture>();

	for (int textureID{ 0 }; textureID < textureCount; ++textureID)
	{
		const FbxFileTexture* fbxTexture = materialProperty.GetSrcObject<FbxFileTexture>(textureID);
		if (fbxTexture)
			m_importer->Import(fbxTexture->GetFileName(), destination, fbxTexture->GetName());
	}
}

std::vector<Texture*> engine::loader::FbxExtractor::GetTextures(Folder* destination,
	const FbxSurfaceMaterial* fbxMaterial, const char* materialType) const
{
	if (destination == nullptr || fbxMaterial == nullptr)
		return std::vector<Texture*>();

	const FbxProperty materialProperty = fbxMaterial->FindProperty(materialType);
	if (!materialProperty.IsValid())
		return std::vector<Texture*>();

	const int textureCount = materialProperty.GetSrcObjectCount<FbxFileTexture>();
	if (textureCount <= 0)
		return std::vector<Texture*>();

	std::vector<Texture*> textures;

	for (int textureID{ 0 }; textureID < textureCount; ++textureID)
	{
		const FbxFileTexture* fbxTexture = materialProperty.GetSrcObject<FbxFileTexture>(textureID);
		if (fbxTexture)
		{
			std::string name{ fbxTexture->GetName() };

			textures.emplace_back(destination->GetTexture(name));
		}
	}

	return textures;
}

Vec4 engine::loader::FbxExtractor::GetColor(const FbxSurfaceMaterial* fbxMaterial, const char* materialType) const
{
	if (fbxMaterial == nullptr)
		return Vec4::Zero();

	const FbxProperty materialProperty = fbxMaterial->FindProperty(materialType);
	if (!materialProperty.IsValid())
		return Vec4::Zero();

	FbxDouble4 fbxColor = materialProperty.Get<FbxDouble4>();
	return Vec4((float)fbxColor.mData[0], (float)fbxColor.mData[1], (float)fbxColor.mData[2], (float)fbxColor.mData[3]);
}

float engine::loader::FbxExtractor::GetFactor(const FbxSurfaceMaterial* fbxMaterial, const char* factorType) const
{
	if (fbxMaterial == nullptr)
		return 0.f;

	const FbxProperty factorProperty = fbxMaterial->FindProperty(factorType);
	if (!factorProperty.IsValid())
		return 0.f;

	return (float)factorProperty.Get<FbxFloat>();
}

FbxNodeAttribute::EType engine::loader::FbxExtractor::GetNodeAttribute(FbxNode* node) const
{
	if (node)
	{
		FbxNodeAttribute* nodeAttribute{ node->GetNodeAttribute() };

		if (nodeAttribute)
			return nodeAttribute->GetAttributeType();
	}

	return FbxNodeAttribute::EType::eNull;
}
