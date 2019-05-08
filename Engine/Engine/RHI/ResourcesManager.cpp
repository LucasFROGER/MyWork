#include "ResourcesManager.h"

engine::rhi::ResourcesManager::ResourcesManager(ID3D12Device* device, int frameBufferSize) :
	m_device{ device },
	m_frameBufferSize{ frameBufferSize },
	m_renderObjectManager{ new RenderObjectManager(m_device) },
	m_rootSignatureManager{ new RootSignatureManager(m_device) },
	m_shaderManager{ new ShaderManager(m_device) },
	m_psoManager{ new PsoManager(m_device) },
	m_cbManager{ new ConstantBufferManager(m_device) },
	m_textureManager{ new TextureManager(m_device) },
	m_samplerManager{ new SamplerManager(m_device) },
	m_fontManager{ new FontManager(m_device) },
	m_textManager{ new TextManager(m_device, m_frameBufferSize)}
{}

engine::rhi::ResourcesManager::~ResourcesManager()
{
	SAFE_DELETE(m_renderObjectManager);
	SAFE_DELETE(m_rootSignatureManager);
	SAFE_DELETE(m_shaderManager);
	SAFE_DELETE(m_psoManager);
	SAFE_DELETE(m_cbManager);
	SAFE_DELETE(m_textureManager);
	SAFE_DELETE(m_samplerManager);
	SAFE_DELETE(m_fontManager);
	SAFE_DELETE(m_textManager);
}

ID3D12Device* engine::rhi::ResourcesManager::GetDevice() const
{
	return m_device;
}

engine::rhi::RenderObjectManager* engine::rhi::ResourcesManager::GetRenderObjectManager() const
{
	return m_renderObjectManager;
}

engine::rhi::RootSignatureManager* engine::rhi::ResourcesManager::GetRootSignatureManager() const
{
	return m_rootSignatureManager;
}

engine::rhi::ShaderManager* engine::rhi::ResourcesManager::GetShaderManager() const
{
	return m_shaderManager;
}

engine::rhi::PsoManager* engine::rhi::ResourcesManager::GetPsoManager() const
{
	return m_psoManager;
}

engine::rhi::ConstantBufferManager* engine::rhi::ResourcesManager::GetConstantBufferManager() const
{
	return m_cbManager;
}

engine::rhi::TextureManager* engine::rhi::ResourcesManager::GetTextureManager() const
{
	return m_textureManager;
}

engine::rhi::SamplerManager* engine::rhi::ResourcesManager::GetSamplerManager() const
{
	return m_samplerManager;
}

engine::rhi::FontManager* engine::rhi::ResourcesManager::GetFontManager() const
{
	return m_fontManager;
}

engine::rhi::TextManager* engine::rhi::ResourcesManager::GetTextManager() const
{
	return m_textManager;
}
