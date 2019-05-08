#include "Shader.h"

using namespace resource;

Shader::Shader(uint32_t id, EShaderType type) :
	m_id{ id },
	m_type{ type }
{}

std::string Shader::GetName()
{
	return m_name;
}