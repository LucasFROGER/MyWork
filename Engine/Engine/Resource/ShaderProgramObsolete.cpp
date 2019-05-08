#include "ShaderProgram.h"

#include <iostream>
#include <fstream>

#include "GL/glew.h"

using namespace resource;

ShaderProgram::ShaderProgram() :
	m_program{ 0 },
	m_vertexShader{ 0 },
	m_geometryShader{ 0 },
	m_fragmentShader{ 0 },
	m_computeShader{ 0 },
	m_controlShader{ 0 },
	m_evaluationShader{ 0 }
{}

ShaderProgram::ShaderProgram(const ShaderProgram& other) :
	m_program{ 0 },
	m_vertexShader{ other.m_vertexShader },
	m_geometryShader{ other.m_geometryShader },
	m_fragmentShader{ other.m_fragmentShader },
	m_computeShader{ other.m_computeShader },
	m_controlShader{ other.m_controlShader },
	m_evaluationShader{ other.m_evaluationShader }
{
	if (other.m_program != 0)
		CreateProgram();
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) :
	m_program{ other.m_program },
	m_vertexShader{ other.m_vertexShader },
	m_geometryShader{ other.m_geometryShader },
	m_fragmentShader{ other.m_fragmentShader },
	m_computeShader{ other.m_computeShader },
	m_controlShader{ other.m_controlShader },
	m_evaluationShader{ other.m_evaluationShader }
{
	if (other.m_program != 0)
		other.m_program = 0;
}

ShaderProgram::~ShaderProgram()
{
	if (m_program != 0)
		DestroyProgram();
}

void ShaderProgram::AttachShaders()
{
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_geometryShader);
	glAttachShader(m_program, m_fragmentShader);
	glAttachShader(m_program, m_computeShader);
	glAttachShader(m_program, m_controlShader);
	glAttachShader(m_program, m_evaluationShader);
}

std::string ShaderProgram::GetName()
{
	return m_name;
}

bool ShaderProgram::AddShader(const Shader* shader)
{
	if (shader == nullptr)
		return false;

	uint32_t shaderID{ shader->m_id };

	switch (shader->m_type)
	{
	case EShaderType::VERTEX_SHADER:
		m_vertexShader = shaderID;
		break;
	case EShaderType::GEOMETRY_SHADER:
		m_geometryShader = shaderID;
		break;
	case EShaderType::FRAGMENT_SHADER:
		m_fragmentShader = shaderID;
		break;
	case EShaderType::COMPUTE_SHADER:
		m_computeShader = shaderID;
		break;
	case EShaderType::TESS_CONTROL_SHADER:
		m_controlShader = shaderID;
		break;
	case EShaderType::TESS_EVALUATION_SHADER:
		m_evaluationShader = shaderID;
		break;
	default:
		return false;
	}

	return true;
}

bool ShaderProgram::RemoveShader(EShaderType shaderType)
{
	switch (shaderType)
	{
	case EShaderType::VERTEX_SHADER:
		m_vertexShader = 0;
		break;
	case EShaderType::GEOMETRY_SHADER:
		m_geometryShader = 0;
		break;
	case EShaderType::FRAGMENT_SHADER:
		m_fragmentShader = 0;
		break;
	case EShaderType::COMPUTE_SHADER:
		m_computeShader = 0;
		break;
	case EShaderType::TESS_CONTROL_SHADER:
		m_controlShader = 0;
		break;
	case EShaderType::TESS_EVALUATION_SHADER:
		m_evaluationShader = 0;
		break;
	default:
		return false;
	}

	return true;
}

void ShaderProgram::ClearShadersList()
{
	m_vertexShader = 0;
	m_geometryShader = 0;
	m_fragmentShader = 0;
	m_computeShader = 0;
	m_controlShader = 0;
	m_evaluationShader = 0;
}

bool ShaderProgram::CreateProgram()
{
	if (m_program != 0)
		return true; // ShaderProgram already created

	m_program = glCreateProgram();

	if (m_program == 0)
		return false; // glCreateProgram() failed
	
	AttachShaders();

	glLinkProgram(m_program);

	int linkSuccess{ 0 };
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess)
	{
		char errorBuffer[4096];
		int error_len;
		glGetProgramInfoLog(m_program, 4096, &error_len, errorBuffer);
		std::cout << "link error: "	<< errorBuffer << std::endl;

		glDeleteProgram(m_program);

		return false;
	}

	return true;
}

void ShaderProgram::DestroyProgram()
{
	glDeleteProgram(m_program);
	m_program = 0;
}

void ShaderProgram::Bind() 
{
	glUseProgram(m_program);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0); 
}

uint32_t ShaderProgram::GetProgram() const
{
	return m_program;
}