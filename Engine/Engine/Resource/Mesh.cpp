#include "Mesh.h"

using namespace engine::resource;

Mesh::Mesh(const std::string& name) : m_name{ name }
{}

Mesh::Mesh(const std::string& name, const std::vector<Vertex> vbo, std::vector<int> ibo) :
	m_name{ name },
	m_vbo{ vbo },
	m_ibo{ ibo }
{}

void Mesh::AddVertex(const Vertex& vertex)
{
	m_vbo.emplace_back(vertex);
}

void Mesh::AddIndex(int index)
{
	m_ibo.emplace_back(index);
}

const std::string& Mesh::GetName() const
{
	return m_name;
}

const std::vector<Vertex>& Mesh::GetVBO() const
{
	return m_vbo;
}

const std::vector<int>& Mesh::GetIBO() const
{
	return m_ibo;
}

float* Mesh::GetVBOAddress()
{
	return m_vbo.data()->GetAddress();
}

int* Mesh::GetIBOAddress()
{
	return m_ibo.data();
}

int Mesh::GetSizeOfVBO() const
{
	return sizeof(Vertex) * m_vbo.size();
}

int Mesh::GetSizeOfIBO() const
{
	return sizeof(int) * m_ibo.size();
}

void Mesh::SetVBO(const std::vector<Vertex>& vbo)
{
	m_vbo = vbo;
}

void Mesh::SetIBO(const std::vector<int>& ibo)
{
	m_ibo = ibo;
}

void Mesh::SetVBOCapacity(size_t capacity)
{
	m_vbo.reserve(capacity);
}

void Mesh::SetIBOCapacity(size_t capacity)
{
	m_ibo.reserve(capacity);
}
