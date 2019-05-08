#include "Shader.h"

engine::rhi::resources::Shader::Shader(std::wstring shaderPath, EShaderEnum type, const int id) : m_id{ id }
{
	HRESULT hr;

	switch (type)
	{
		case EShaderEnum::VERTEX_SHADER:
		{
			hr = D3DCompileFromFile(shaderPath.c_str(),
				nullptr,
				nullptr,
				"main",
				"vs_5_0",
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0,
				&m_shaderByteCodePointer,
				&m_errorBuff);
			break;
		}
		case EShaderEnum::PIXEL_SHADER:
		{
			hr = D3DCompileFromFile(shaderPath.c_str(),
				nullptr,
				nullptr,
				"main",
				"ps_5_0",
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0,
				&m_shaderByteCodePointer,
				&m_errorBuff);
			break;
		}
		case EShaderEnum::GEOMETRY_SHADER:
		{
			hr = D3DCompileFromFile(shaderPath.c_str(),
				nullptr,
				nullptr,
				"main",
				"gs_5_0",
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0,
				&m_shaderByteCodePointer,
				&m_errorBuff);
			break;
		}
		case EShaderEnum::HULL_SHADER:
		{
			hr = D3DCompileFromFile(shaderPath.c_str(),
				nullptr,
				nullptr,
				"main",
				"hs_5_0",
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0,
				&m_shaderByteCodePointer,
				&m_errorBuff);
			break;
		}
		case EShaderEnum::DOMAIN_SHADER:
		{
			hr = D3DCompileFromFile(shaderPath.c_str(),
				nullptr,
				nullptr,
				"main",
				"ds_5_0",
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0,
				&m_shaderByteCodePointer,
				&m_errorBuff);
			break;
		}
		default:
		{
			MessageBox(0, L"Unknown shader type - Failed", L"Error", MB_OK);
			break;
		}
	}

	if (FAILED(hr))
		MessageBox(0, L"Shader creation failed", L"Error", MB_OK);

	else
	{
		m_path = shaderPath;
		m_type = type;
		m_shaderByteCodeStruct.BytecodeLength = m_shaderByteCodePointer->GetBufferSize();
		m_shaderByteCodeStruct.pShaderBytecode = m_shaderByteCodePointer->GetBufferPointer();
	}

}

engine::rhi::resources::Shader::~Shader()
{

}

std::wstring engine::rhi::resources::Shader::GetShaderPath() const
{
	return m_path;
}

engine::rhi::resources::EShaderEnum engine::rhi::resources::Shader::GetShaderType() const
{
	return m_type;
}

D3D12_SHADER_BYTECODE engine::rhi::resources::Shader::GetShaderByteCode() const
{
	return m_shaderByteCodeStruct;
}

ID3DBlob* engine::rhi::resources::Shader::GetShaderErrorBuffer() const
{
	return m_errorBuff;
}

const int engine::rhi::resources::Shader::GetId() const
{
	return m_id;
}

bool engine::rhi::resources::Shader::operator==(const Shader& other) const
{
	if (m_path == other.m_path &&
		m_type == other.m_type &&
		m_shaderByteCodeStruct.BytecodeLength == m_shaderByteCodeStruct.BytecodeLength &&
		m_shaderByteCodeStruct.pShaderBytecode == m_shaderByteCodeStruct.pShaderBytecode)
		return true;
	return false;
}

bool engine::rhi::resources::Shader::operator!=(const Shader& other) const
{
	if (m_path == other.m_path &&
		m_type == other.m_type &&
		m_shaderByteCodeStruct.BytecodeLength == m_shaderByteCodeStruct.BytecodeLength &&
		m_shaderByteCodeStruct.pShaderBytecode == m_shaderByteCodeStruct.pShaderBytecode)
		return false;
	return true;
}