#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "ShaderLoader.h"

using namespace loader;

bool ShaderLoader::LoadShader(const std::string& filePath, resource::EShaderType shaderType, resource::Shader& out)
{
	uint32_t glShaderType{ resource::ToGLShaderType(shaderType) };
	uint32_t shaderID{ glCreateShader(glShaderType) };

	std::ifstream fileStream;
	fileStream.open(filePath, std::ios::binary);
	if (!fileStream.is_open())
		return false;
	auto begin = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	auto file_len = fileStream.tellg() - begin;
	char* buffer = new char[file_len + 1];
	fileStream.seekg(0, std::ios::beg);
	fileStream.read(buffer, file_len);
	fileStream.close();

	buffer[file_len] = '\0';
	glShaderSource(shaderID, 1, &buffer, nullptr);
	delete[] buffer;

	glCompileShader(shaderID);

	int compileSuccess = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
	if (!compileSuccess)
	{
		char errorBuffer[4096];
		int error_len;
		glGetShaderInfoLog(shaderID, 4096, &error_len, errorBuffer);

		std::cout << "error into " << resource::ToString(shaderType) << " shader: " << errorBuffer << std::endl;

		glDeleteShader(glShaderType);

		return false;
	}

	out.m_id = shaderID;
	out.m_type = shaderType;

	return true;
}