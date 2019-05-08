#include "FontManager.h"

engine::rhi::FontManager::FontManager(ID3D12Device* device) : m_device{ device }
{}

engine::rhi::FontManager::~FontManager()
{
	SAFE_DELETE_VECTOR(m_fontTab);
}

void engine::rhi::FontManager::ClearFonts()
{
	SAFE_DELETE_VECTOR(m_fontTab);
}

engine::rhi::resources::FontInfo* engine::rhi::FontManager::FindFont(resources::FontInfo* info)
{
	for (unsigned int i{ 0 }; i < m_fontTab.size(); ++i)
	{
		if (*m_fontTab[i] == *info)
		{
			return m_fontTab[i];
		}
	}

	resources::FontInfo* newFont = new resources::FontInfo(*info);
	newFont->m_id = m_fontTab.size();

	m_fontTab.push_back(newFont);
	return newFont;
}

engine::rhi::resources::FontInfo* engine::rhi::FontManager::GetFontByIndex(int index) const
{
	if (index < m_fontTab.size() && index >= 0)
		return m_fontTab[index];
	else
		return nullptr;
}

unsigned int engine::rhi::FontManager::GetFontNb() const
{
	return m_fontTab.size();
}
