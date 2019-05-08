#include "TextureManager.h"

engine::rhi::TextureManager::TextureManager(ID3D12Device* device) : m_device{ device }
{}

engine::rhi::TextureManager::~TextureManager()
{
	SAFE_DELETE_VECTOR(m_textureTab);
}

engine::rhi::resources::Texture* engine::rhi::TextureManager::FindTexture(const wchar_t* path)
{
	for (unsigned int i{ 0 }; i < m_textureTab.size(); ++i)
		if (m_textureTab[i]->GetPath() == path)
			return m_textureTab[i];

	resources::Texture* newTexture = new resources::Texture(m_device, path, m_textureTab.size());

	m_textureTab.push_back(newTexture);
	return newTexture;
}

engine::rhi::resources::Texture* engine::rhi::TextureManager::GetTextureByIndex(int index) const
{
	if (index < m_textureTab.size() && index >= 0)
		return m_textureTab[index];
	else
		return nullptr;
}