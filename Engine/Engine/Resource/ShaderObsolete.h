#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <cstdint>
#include "EShaderType.h"

namespace resource
{
	struct Shader
	{
		std::string m_name;
		uint32_t m_id;
		EShaderType m_type;

		Shader() = default;
		Shader(const Shader& other) = default;
		Shader(Shader&& other) = default;
		Shader(uint32_t id, resource::EShaderType type);
		~Shader() = default;

		Shader& operator=(const Shader& other) = default;
		Shader& operator=(Shader&& other) = default;

		std::string GetName();
	};
}

#endif