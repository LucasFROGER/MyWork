#include "Vertex.h"

using namespace engine::resource;
using namespace engine::core::maths;

Vertex::Vertex(Vec3 position, Vec3 normal, Vec2 uv) :
	m_position{ position },
	m_normal{ normal },
	m_uv{ uv },
	m_tangent{ Vec3::Zero() }
{}

float* Vertex::GetAddress()
{
	return &m_position.m_x;
}

bool Vertex::operator==(const Vertex& other)
{
	return (m_position == other.m_position) && (m_normal == other.m_normal) && (m_uv == other.m_uv);
}

bool Vertex::operator!=(const Vertex& other)
{
	return (m_position != other.m_position) || (m_normal != other.m_normal) || (m_uv != other.m_uv);
}