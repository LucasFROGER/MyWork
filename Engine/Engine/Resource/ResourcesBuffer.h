#ifndef _RESOURCES_BUFFER_H_
#define _RESOURCES_BUFFER_H_

#include <string>
#include <unordered_map>

#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "EResourceType.h"

namespace resource
{
	class ResourcesBuffer
	{
		std::string m_name;

		std::unordered_map<std::string, Vertex*>		   m_vertices;
		std::unordered_map<std::string, Mesh*>			   m_meshes;
		std::unordered_map<std::string, Texture*>		   m_textures;
		std::unordered_map<std::string, Material*>		   m_materials;
		std::unordered_map<std::string, Shader*>		   m_shaders;
		std::unordered_map<std::string, ShaderProgram*>	   m_shaderPrograms;

		bool RemoveVertex(const std::string& name);
		bool RemoveMesh(const std::string& name);
		bool RemoveTexture(const std::string& name);
		bool RemoveMaterial(const std::string& name);
		bool RemoveShader(const std::string& name);
		bool RemoveShaderProgram(const std::string& name);

		void ClearAllVertices();
		void ClearAllMeshes();
		void ClearAllTextures();
		void ClearAllMaterials();
		void ClearAllShaders();
		void ClearAllShaderPrograms();

	public:
		ResourcesBuffer() = default;
		ResourcesBuffer(const ResourcesBuffer& other) = default;
		ResourcesBuffer(ResourcesBuffer&& other) = default;
		~ResourcesBuffer();

		ResourcesBuffer& operator=(const ResourcesBuffer& other) = default;
		ResourcesBuffer& operator=(ResourcesBuffer&& other) = default;

		std::string Add(const std::string& vertexName, Vertex& vertex);
		std::string Add(const std::string& name, Mesh& mesh);
		std::string Add(const std::string& name, Texture& texture);
		std::string Add(const std::string& name, Material& material);
		std::string Add(const std::string& name, Shader& shader);
		std::string Add(const std::string& name, ShaderProgram& shaderProgram);

		bool Get(const std::string& name, Vertex* out) const;
		bool Get(const std::string& name, Mesh* out) const;
		bool Get(const std::string& name, Texture* out) const;
		bool Get(const std::string& name, Material* out) const;
		bool Get(const std::string& name, Shader* out) const;
		bool Get(const std::string& name, ShaderProgram* out) const;

		void* Get(const std::string& name, EResourceType type);

		bool Remove(const std::string& name, EResourceType type);
	};
}

#endif