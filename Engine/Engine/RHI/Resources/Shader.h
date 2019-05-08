#ifndef _SHADER_H_
#define _SHADER_H_

#include "../../../stdafx.h"
#include "ShaderEnum.h"

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class Shader
			{
			public:

				Shader(std::wstring shaderPath, EShaderEnum type, const int id);
				~Shader();

				std::wstring GetShaderPath() const;
				EShaderEnum GetShaderType() const;
				D3D12_SHADER_BYTECODE GetShaderByteCode() const;
				ID3DBlob* GetShaderErrorBuffer() const;
				const int GetId() const;

				bool operator==(const Shader& other) const;
				bool operator!=(const Shader& other) const;


			private:

				std::wstring m_path;
				EShaderEnum m_type;
				ID3DBlob* m_shaderByteCodePointer;
				ID3DBlob* m_errorBuff;
				D3D12_SHADER_BYTECODE m_shaderByteCodeStruct;
				const int m_id;

			};
		}
	}
}

#endif