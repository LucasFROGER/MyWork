#include "ShaderProgram.h"

engine::resource::ShaderProgram::ShaderProgram(const std::string& name) :
	m_name{ name },
	m_shaders((int)rhi::resources::EShaderEnum::COUNT, -1)
{}

bool engine::resource::ShaderProgram::AddShader(Shader* shader)
{
	if (shader == nullptr)
		return false;

	int index{ (int)shader->GetType() };

	if (index < 0 || index >= m_shaders.size())
		return false;
	
	m_shaders[index] = shader->GetID();
	GenProgram();

	return true;
}

bool engine::resource::ShaderProgram::RemoveShader(engine::rhi::resources::EShaderEnum type)
{
	int index{ (int)type };

	if (index < 0 || index >= m_shaders.size())
		return false;

	m_shaders[index] = -1;
	GetProgram();
	return true;
}

void engine::resource::ShaderProgram::ClearShadersList()
{
	for (int& id : m_shaders)
		id = -1;

	m_program.clear();
}

std::string engine::resource::ShaderProgram::GetName() const
{
	return m_name;
}

std::vector<int> engine::resource::ShaderProgram::GetProgram() const
{
	return m_program;
}

int* engine::resource::ShaderProgram::GetProgramAddress()
{
	return m_program.data();
}

size_t engine::resource::ShaderProgram::GetProgramSize() const
{
	return m_program.size();
}

void engine::resource::ShaderProgram::GenProgram()
{
	m_program.clear();
	for (size_t index{ 0 }; index < m_shaders.size(); ++index)
	{
		if (m_shaders[index] != -1)
			m_program.emplace_back(m_shaders[index]);
	}
}
