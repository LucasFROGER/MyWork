#include "ShaderManager.h"

engine::rhi::ShaderManager::ShaderManager(ID3D12Device* device) : m_device{ device }
{}

engine::rhi::ShaderManager::~ShaderManager()
{
	SAFE_DELETE_VECTOR(m_shaderTab);
}

engine::rhi::resources::Shader* engine::rhi::ShaderManager::FindShader(std::wstring path, engine::rhi::resources::EShaderEnum type)
{
	for (unsigned int i{ 0 }; i < m_shaderTab.size(); ++i)
	{
		if (m_shaderTab[i]->GetShaderPath() == path && m_shaderTab[i]->GetShaderType() == type)
		{
			return m_shaderTab[i];
		}
	}

	engine::rhi::resources::Shader* newShader = new engine::rhi::resources::Shader(path, type, (int)m_shaderTab.size());

	m_shaderTab.push_back(newShader);
	return newShader;
}

engine::rhi::resources::Shader* engine::rhi::ShaderManager::GetShaderByIndex(int index) const
{
	if (index < m_shaderTab.size())
		return m_shaderTab[index];
	return nullptr;
}