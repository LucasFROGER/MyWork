#include "ObjExtractor.h"

using namespace engine::loader;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine;

ObjExtractor::ObjExtractor(Importer* importer, ResourceMgr* resourceMgr, rhi::RHI* rhi) :
	Extractor(importer, resourceMgr, rhi)
{}

void ObjExtractor::ExtractFile(const std::string& filePath, Folder* destination, const std::string& fileName) const
{
	ExtractMesh(filePath.c_str(), destination, fileName);
}

bool ObjExtractor::ExtractMesh(const char* filePath, Folder* destination, const std::string& fileName) const
{
	if (destination == nullptr || m_resourceMgr == nullptr)
		return false;

	FILE* fp;
	char chBuffer[256];

	Vec3 v;
	Vec2 vt;
	Vec3 vn;

	size_t vIndices[3]{ 0 };
	size_t vtIndices[3]{ 0 };
	size_t vnIndices[3]{ 0 };

	std::vector<Vec3> positions;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;

	std::vector<size_t> pIndices;
	std::vector<size_t> uvIndices;
	std::vector<size_t> nIndices;

	if (fopen_s(&fp, filePath, "r") != 0)
		return false;

	std::string name;
	FindValidMeshName(name, destination, fileName, GetFileName(filePath));

	Mesh mesh(name);
	Mesh* meshPtr{ m_resourceMgr->Add<Mesh>(mesh) };

	while (!feof(fp))
	{
		fscanf_s(fp, "%s", chBuffer, sizeof(chBuffer));

		if (!strcmp(chBuffer, "v"))
		{
			fscanf_s(fp, "%f %f %f\n", &v.m_x, &v.m_y, &v.m_z);
			positions.emplace_back(v);
		}

		else if (!strcmp(chBuffer, "vt"))
		{
			fscanf_s(fp, "%f %f\n", &vt.m_x, &vt.m_y);
			uvs.emplace_back(vt);
		}

		else if (!strcmp(chBuffer, "vn"))
		{
			fscanf_s(fp, "%f %f %f\n", &vn.m_x, &vn.m_y, &vn.m_z);
			normals.emplace_back(vn);
		}

		else if (!strcmp(chBuffer, "f"))
		{
			if (9 == fscanf_s(fp, "%u/%u/%u %u/%u/%u %u/%u/%u\n",
				&vIndices[0], &vtIndices[0], &vnIndices[0],
				&vIndices[1], &vtIndices[1], &vnIndices[1],
				&vIndices[2], &vtIndices[2], &vnIndices[2]))
			{
				pIndices.emplace_back(--vIndices[0]); uvIndices.emplace_back(--vtIndices[0]); nIndices.emplace_back(--vnIndices[0]);
				pIndices.emplace_back(--vIndices[1]); uvIndices.emplace_back(--vtIndices[1]); nIndices.emplace_back(--vnIndices[1]);
				pIndices.emplace_back(--vIndices[2]); uvIndices.emplace_back(--vtIndices[2]); nIndices.emplace_back(--vnIndices[2]);
			}

			else if (6 == fscanf_s(fp, "%u/%u %u/%u %u/%u\n",
				&vIndices[0], &vtIndices[0],
				&vIndices[1], &vtIndices[1],
				&vIndices[2], &vtIndices[2]))
			{
				pIndices.emplace_back(--vIndices[0]); uvIndices.emplace_back(--vtIndices[0]);
				pIndices.emplace_back(--vIndices[1]); uvIndices.emplace_back(--vtIndices[1]);
				pIndices.emplace_back(--vIndices[2]); uvIndices.emplace_back(--vtIndices[2]);
			}

			else if (6 == fscanf_s(fp, "%u//%u %u//%u %u//%u\n",
				&vIndices[0], &vnIndices[0],
				&vIndices[1], &vnIndices[1],
				&vIndices[2], &vnIndices[2]))
			{
				pIndices.emplace_back(--vIndices[0]); nIndices.emplace_back(--vnIndices[0]);
				pIndices.emplace_back(--vIndices[1]); nIndices.emplace_back(--vnIndices[1]);
				pIndices.emplace_back(--vIndices[2]); nIndices.emplace_back(--vnIndices[2]);
			}

			else if (3 == fscanf_s(fp, "%u %u %u \n",
				&vIndices[0], &vIndices[1], &vIndices[2]))
			{
				pIndices.emplace_back(--vIndices[0]);
				pIndices.emplace_back(--vIndices[1]);
				pIndices.emplace_back(--vIndices[2]);
			}
		}
	}

	fclose(fp);

	if (nIndices.size() == 0)
	{
		for (size_t index{ 0 }; index < pIndices.size(); index += 3)
		{
			normals.emplace_back(GenNormal(positions[pIndices[index]], positions[pIndices[index + 1]], positions[pIndices[index + 2]]));
			nIndices.emplace_back(index / 3);
			nIndices.emplace_back(index / 3);
			nIndices.emplace_back(index / 3);
		}
	}

	if (uvIndices.size() == 0)
	{
		for (size_t index{ 0 }; index < pIndices.size(); ++index)
		{
			meshPtr->AddIndex(index);
			meshPtr->AddVertex(Vertex(
				positions[pIndices[index]],
				normals[nIndices[index]],
				Vec2::Zero()
			));
		}
	}

	else
	{
		for (size_t index{ 0 }; index < pIndices.size(); ++index)
		{
			meshPtr->AddIndex(index);
			meshPtr->AddVertex(Vertex(
				positions[pIndices[index]],
				normals[nIndices[index]],
				uvs[uvIndices[index]]
			));
		}
	}

	destination->Add(meshPtr);

	return true;
}

Vec3 ObjExtractor::GenNormal(const Vec3& p1, const Vec3& p2, const Vec3& p3) const
{
	return (p2 - p1).CrossProduct(p3 - p1).GetNormalized();
}
