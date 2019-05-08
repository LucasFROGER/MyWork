#include "Model.h"

using namespace engine::low_renderer;

Model::Model(const char* path, std::vector<Vertex> vertices, std::vector<int> indices) : 
	m_path{ path }, 
	m_vertexData{ CreateVerticesData(vertices) }, 
	m_indicesData{ CreateIndicesData(indices) }
{

}

Model::~Model()
{
	delete m_vertexData;
	delete m_indicesData;
}

float* Model::CreateVerticesData(std::vector<Vertex> vertices)
{
	m_verticesSize = (int)(vertices.size() * (sizeof(Vertex) / sizeof(float)));
	float* data = new float[m_verticesSize]();
	int index{ 0 };
	for (size_t i{ 0 }; i < vertices.size(); i++)
	{
		// POSITION
		data[index] = vertices[i].m_position.m_x;
		++index;
		data[index] = vertices[i].m_position.m_x;
		++index;
		data[index] = vertices[i].m_position.m_x;
		++index;
		// NORMAL
		data[index] = vertices[i].m_normal.m_x;
		++index;
		data[index] = vertices[i].m_normal.m_x;
		++index;
		data[index] = vertices[i].m_normal.m_x;
		++index;
		// UV
		data[index] = vertices[i].m_texCoord.m_x;
		++index;
		data[index] = vertices[i].m_texCoord.m_x;
		++index;
		// TANGENT
		data[index] = vertices[i].m_tangent.m_x;
		++index;
		data[index] = vertices[i].m_tangent.m_x;
		++index;
		data[index] = vertices[i].m_tangent.m_x;
		++index;
	}
	return data;
}

int* Model::CreateIndicesData(std::vector<int> indices)
{
	m_indicesSize = (int)indices.size();
	int* data = new int[m_indicesSize]();
	int index{ 0 };
	for (size_t i{ 0 }; i < indices.size(); i++)
	{
		data[index] = indices[i];
		++index;
	}
	return data;
}

const char* Model::GetPath()
{
	return m_path;
}

float* Model::GetVertices()
{
	return m_vertexData;
}

int* Model::GetIndices()
{
	return m_indicesData;
}

int Model::GetVerticesSize() const
{
	return m_verticesSize;
}

int Model::GetIndicesSize() const
{
	return m_indicesSize;
}