#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include "Shader.h"

namespace resource
{
	class ShaderProgram
	{
		std::string m_name;
		uint32_t m_program;

		uint32_t m_vertexShader;
		uint32_t m_geometryShader;
		uint32_t m_fragmentShader;
		uint32_t m_computeShader;
		uint32_t m_controlShader;
		uint32_t m_evaluationShader;

		void AttachShaders();

	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram& other);
		ShaderProgram(ShaderProgram&& other);
		~ShaderProgram();

		std::string GetName();

		bool AddShader(const Shader* shader);
		bool RemoveShader(EShaderType shader);
		void ClearShadersList();

		bool CreateProgram();
		void DestroyProgram();
		void Bind();
		void Unbind();

		uint32_t GetProgram() const;
	};
}

#endif