#ifndef _E_SHADER_TYPE_H_
#define _E_SHADER_TYPE_H_

#include <string>

namespace resource
{
	enum class EShaderType
	{
		UNKNOWN = -1,
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		COUNT
	};

	EShaderType GetShaderType(uint32_t glShaderType);
	std::string ToString(const EShaderType& shaderType);
	uint32_t ToGLShaderType(const EShaderType& shaderType);
}

#endif