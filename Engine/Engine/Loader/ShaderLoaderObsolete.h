#ifndef _SHADERS_LOADER_H_
#define _SHADERS_LOADER_H_

#include <string>
#include "../Resource/EShaderType.h"
#include "../Resource/Shader.h"

namespace loader
{
	class ShaderLoader
	{
	public:
		static bool LoadShader(const std::string& filePath, resource::EShaderType shaderType, resource::Shader& out);
	};
}

#endif