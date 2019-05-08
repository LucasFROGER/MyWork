#include "ResourcesBuffer.h"

using namespace resource;

ResourcesBuffer::~ResourcesBuffer()
{
	ClearAllVertices();
	ClearAllMeshes();
	ClearAllTextures();
	ClearAllMaterials();
	ClearAllShaders();
	ClearAllShaderPrograms();
}

void ResourcesBuffer::ClearAllVertices()
{
	for (auto& vertex : m_vertices)
		if (vertex.second != nullptr)
			delete vertex.second;
	m_vertices.clear();
}

void ResourcesBuffer::ClearAllMeshes()
{
	for (auto& mesh : m_meshes)
		if (mesh.second != nullptr)
			delete mesh.second;
	m_meshes.clear();
}

void ResourcesBuffer::ClearAllTextures()
{
	for (auto& texture : m_textures)
		if (texture.second != nullptr)
			delete texture.second;
	m_textures.clear();
}

void ResourcesBuffer::ClearAllMaterials()
{
	for (auto& material : m_materials)
		if (material.second != nullptr)
			delete material.second;
	m_materials.clear();
}

void ResourcesBuffer::ClearAllShaders()
{
	for (auto& shader : m_shaders)
		if (shader.second != nullptr)
			delete shader.second;
	m_shaders.clear();
}

void ResourcesBuffer::ClearAllShaderPrograms()
{
	for (auto& shaderProgram : m_shaderPrograms)
		if (shaderProgram.second != nullptr)
			delete shaderProgram.second;
	m_shaderPrograms.clear();
}

std::string ResourcesBuffer::Add(const std::string& vertexName, Vertex& vertex)
{
	if (vertexName == std::string())
	{
		// Invalid name.
		return vertexName;
	}

	std::string name{ vertexName };
	Vertex* vertexPtr{ nullptr };

	for (int i{ 1 }; Get(name, vertexPtr) == true; ++i)
	{
		// Name already registered. Generates a new name.
		name = vertexName + ' ' + std::to_string(i);
	}

	vertexPtr = new Vertex(vertex);
	m_vertices.emplace(name, vertexPtr);

	return name;
}

std::string ResourcesBuffer::Add(const std::string& meshName, Mesh& mesh)
{
	if (meshName == std::string())
	{
		// Invalid name.
		return meshName;
	}

	std::string name{ meshName };
	Mesh* meshPtr{ nullptr };

	for (int i{ 1 }; Get(name, meshPtr) == true; ++i)
	{
		// Name already registered. Generates a new name.
		name = meshName + ' ' + std::to_string(i);
	}

	meshPtr = new Mesh(mesh);
	m_meshes.emplace(name, meshPtr);

	return name;
}

std::string ResourcesBuffer::Add(const std::string& textureName, Texture& texture)
{
	if (textureName == std::string())
	{
		// Invalid name.
		return textureName;
	}

	std::string name{ textureName };
	Texture* texturePtr{ nullptr };

	for (int i{ 1 }; Get(name, texturePtr) == true; ++i)
	{
		// Name already registered. Generates a new name.
		name = textureName + ' ' + std::to_string(i);
	}

	texturePtr = new Texture(texture);
	m_textures.emplace(name, texturePtr);

	return name;
}

std::string ResourcesBuffer::Add(const std::string& materialName, Material& material)
{
	if (materialName == std::string())
	{
		// Invalid name.
		return materialName;
	}

	std::string name{ materialName };
	Material* materialPtr{ nullptr };

	for (int i{ 1 }; Get(name, materialPtr) == true; ++i)
	{
		// Name already registered. Generates a new name.
		name = materialName + ' ' + std::to_string(i);
	}

	materialPtr = new Material(material);
	m_materials.emplace(name, materialPtr);

	return name;
}

std::string ResourcesBuffer::Add(const std::string& shaderName, Shader& shader)
{
	if (shaderName == std::string())
	{
		// Invalid name.
		return shaderName;
	}

	std::string name{ shaderName };
	Shader* shaderPtr{ nullptr };

	for (int i{ 1 }; Get(name, shaderPtr) == true; ++i)
	{
		// Name already registered. Generates a new name.
		name = shaderName + ' ' + std::to_string(i);
	}

	shaderPtr = new Shader(shader);
	m_shaders.emplace(name, shaderPtr);

	return name;
}

std::string ResourcesBuffer::Add(const std::string& shaderProgramName, ShaderProgram& shaderProgram)
{
	if (shaderProgramName == std::string())
	{
		// Invalid name.
		return shaderProgramName;
	}

	std::string name{ shaderProgramName };
	ShaderProgram* shaderProgramPtr{ nullptr };

	for (int i{ 1 }; Get(name, shaderProgramPtr) == true; ++i)
	{
		// Name already registered. Generates a new name.
		name = shaderProgramName + ' ' + std::to_string(i);
	}

	shaderProgramPtr = new ShaderProgram(shaderProgram);
	m_shaderPrograms.emplace(name, shaderProgramPtr);

	return name;
}

bool ResourcesBuffer::Get(const std::string& name, Vertex* out) const
{
	auto it{ m_vertices.find(name) };
	if (it != m_vertices.end())
	{
		out = it->second;
		return true;
	}

	return false;
}

bool ResourcesBuffer::Get(const std::string& name, Mesh* out) const
{
	auto it{ m_meshes.find(name) };
	if (it != m_meshes.end())
	{
		out = it->second;
		return true;
	}

	return false;
}

bool ResourcesBuffer::Get(const std::string& name, Texture* out) const
{
	auto it{ m_textures.find(name) };
	if (it != m_textures.end())
	{
		out = it->second;
		return true;
	}

	return false;
}

bool ResourcesBuffer::Get(const std::string& name, Material* out) const
{
	auto it{ m_materials.find(name) };
	if (it != m_materials.end())
	{
		out = it->second;
		return true;
	}

	return false;
}

bool ResourcesBuffer::Get(const std::string& name, Shader* out) const
{
	auto it{ m_shaders.find(name) };
	if (it != m_shaders.end())
	{
		out = it->second;
		return true;
	}

	return false;
}

bool ResourcesBuffer::Get(const std::string& name, ShaderProgram* out) const
{
	auto it{ m_shaderPrograms.find(name) };
	if (it != m_shaderPrograms.end())
	{
		out = it->second;
		return true;
	}

	return false;
}

void* ResourcesBuffer::Get(const std::string& name, EResourceType type)
{
	switch (type)
	{
	case EResourceType::VERTEX:
		return m_vertices[name];
	case EResourceType::MESH:
		return m_meshes[name];
	case EResourceType::TEXTURE:
		return m_textures[name];
	case EResourceType::MATERIAL:
		return m_materials[name];
	case EResourceType::SHADER:
		return m_shaders[name];
	case EResourceType::SHADER_PROGRAM:
		return m_shaderPrograms[name];
	default:
		return nullptr;
	}
}

bool ResourcesBuffer::RemoveVertex(const std::string& name)
{
	Vertex* vertexPtr{ nullptr };
	if (Get(name, vertexPtr))
	{
		if (vertexPtr != nullptr)
			delete vertexPtr;

		m_vertices.erase(name);
		return true;
	}

	return false;
}

bool ResourcesBuffer::RemoveMesh(const std::string& name)
{
	Mesh* meshPtr{ nullptr };
	if (Get(name, meshPtr))
	{
		if (meshPtr != nullptr)
			delete meshPtr;

		m_meshes.erase(name);
		return true;
	}

	return false;
}

bool ResourcesBuffer::RemoveTexture(const std::string& name)
{
	Texture* texturePtr{ nullptr };
	if (Get(name, texturePtr))
	{
		if (texturePtr != nullptr)
			delete texturePtr;

		m_textures.erase(name);
		return true;
	}

	return false;
}

bool ResourcesBuffer::RemoveMaterial(const std::string& name)
{
	Material* materialPtr{ nullptr };
	if (Get(name, materialPtr))
	{
		if (materialPtr != nullptr)
			delete materialPtr;

		m_materials.erase(name);
		return true;
	}

	return false;
}

bool ResourcesBuffer::RemoveShader(const std::string& name)
{
	Shader* shaderPtr{ nullptr };
	if (Get(name, shaderPtr))
	{
		if (shaderPtr != nullptr)
			delete shaderPtr;

		m_shaders.erase(name);
		return true;
	}

	return false;
}

bool ResourcesBuffer::RemoveShaderProgram(const std::string& name)
{
	ShaderProgram* shaderProgramPtr{ nullptr };
	if (Get(name, shaderProgramPtr))
	{
		if (shaderProgramPtr != nullptr)
			delete shaderProgramPtr;

		m_shaderPrograms.erase(name);
		return true;
	}

	return false;
}

bool ResourcesBuffer::Remove(const std::string& name, EResourceType type)
{
	switch (type)
	{
	case EResourceType::VERTEX:
		return RemoveVertex(name);
	case EResourceType::MESH:
		return RemoveMesh(name);
	case EResourceType::TEXTURE:
		return RemoveTexture(name);
	case EResourceType::MATERIAL:
		return RemoveMaterial(name);
	case EResourceType::SHADER:
		return RemoveShader(name);
	case EResourceType::SHADER_PROGRAM:
		return RemoveShaderProgram(name);
	default:
		return false;
	}
}
