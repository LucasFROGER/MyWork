#include "Shader.h"

using namespace engine::resource;
using namespace engine::rhi::resources;

//Shader::Shader(const std::string& name) :
//	m_name{ name },
//	m_id{ -1 }
//{}

engine::resource::Shader::Shader(const std::string& name, int id, EShaderEnum type) :
	m_name{ name },
	m_id{ id },
	m_type{ type }
{}

//void Shader::SetID(int id)
//{
//	m_id = id;
//}
//
//void Shader::SetType(EShaderEnum type)
//{
//	m_type = type;
//}

const std::string& engine::resource::Shader::GetName() const
{
	return m_name;
}

int engine::resource::Shader::GetID() const
{
	return m_id;
}

EShaderEnum engine::resource::Shader::GetType() const
{
	return m_type;
}
