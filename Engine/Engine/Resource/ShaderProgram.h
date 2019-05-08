#ifndef _RESOURCE__SHADER_PROGRAM_H_
#define _RESOURCE__SHADER_PROGRAM_H_

#include <vector>

#include "Shader.h"

namespace engine
{
	namespace resource
	{
		class ShaderProgram
		{
		public:
			ShaderProgram(const std::string& name);
			ShaderProgram(const ShaderProgram& other) = default;
			ShaderProgram(ShaderProgram&& other) = default;
			~ShaderProgram() = default;

			bool AddShader(Shader* shader);
			bool RemoveShader(engine::rhi::resources::EShaderEnum type);
			void ClearShadersList();

			std::string GetName() const;
			std::vector<int> GetProgram() const;
			int* GetProgramAddress();
			size_t GetProgramSize() const;

			ShaderProgram& operator=(const ShaderProgram& other) = default;
			ShaderProgram& operator=(ShaderProgram&& other) = default;

		private:
			std::string m_name;

			std::vector<int> m_program;
			std::vector<int> m_shaders;

			void GenProgram();
		};
	}
}
#endif