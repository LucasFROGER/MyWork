#include "EShaderType.h"

#include <GL/glew.h>

using namespace resource;

EShaderType resource::GetShaderType(uint32_t glShaderType)
{
	switch (glShaderType)
	{
	case GL_VERTEX_SHADER:
		return EShaderType::VERTEX_SHADER;
	case GL_GEOMETRY_SHADER:
		return EShaderType::GEOMETRY_SHADER;
	case GL_FRAGMENT_SHADER:
		return EShaderType::FRAGMENT_SHADER;
	case GL_COMPUTE_SHADER:
		return EShaderType::COMPUTE_SHADER;
	case GL_TESS_CONTROL_SHADER:
		return EShaderType::TESS_CONTROL_SHADER;
	case GL_TESS_EVALUATION_SHADER:
		return EShaderType::TESS_EVALUATION_SHADER;
	default:
		return EShaderType::UNKNOWN;
	}
}

std::string resource::ToString(const EShaderType& shaderType)
{
	switch (shaderType)
	{
	case EShaderType::UNKNOWN:
		return "unknown";
	case EShaderType::VERTEX_SHADER:
		return "vertex shader";
	case EShaderType::GEOMETRY_SHADER:
		return "geometry shader";
	case EShaderType::FRAGMENT_SHADER:
		return "fragment shader";
	case EShaderType::COMPUTE_SHADER:
		return "compute shader";
	case EShaderType::TESS_CONTROL_SHADER:
		return "tesselation control shader";
	case EShaderType::TESS_EVALUATION_SHADER:
		return "tesselation evaluation shader";
	default:
		return std::string();
	}
}

uint32_t resource::ToGLShaderType(const EShaderType& shaderType)
{
	switch (shaderType)
	{
	case EShaderType::UNKNOWN:
		return 0;
	case EShaderType::VERTEX_SHADER:
		return GL_VERTEX_SHADER;
	case EShaderType::GEOMETRY_SHADER:
		return GL_GEOMETRY_SHADER;
	case EShaderType::FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
	case EShaderType::COMPUTE_SHADER:
		return GL_COMPUTE_SHADER;
	case EShaderType::TESS_CONTROL_SHADER:
		return GL_TESS_CONTROL_SHADER;
	case EShaderType::TESS_EVALUATION_SHADER:
		return GL_TESS_EVALUATION_SHADER;
	default:
		return 0;
	}
}