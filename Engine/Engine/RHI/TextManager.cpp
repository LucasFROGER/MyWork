#include "TextManager.h"

engine::rhi::TextManager::TextManager(ID3D12Device* device, int frameBufferSize) :
	m_device{ device },
	m_frameBufferSize{ frameBufferSize }
{}

engine::rhi::TextManager::~TextManager()
{
	SAFE_DELETE_VECTOR(m_TextTab);
}

engine::rhi::resources::Text* engine::rhi::TextManager::FindText(std::wstring text, engine::rhi::resources::FontInfo* font, resources::PSO* pso, std::vector<resources::ConstantBuffer*> cbs,
	engine::core::maths::Vec2 pos, engine::core::maths::Vec2 scale, engine::core::maths::Vec2 padding, engine::core::maths::Vec4 color)
{
	resources::Text* newText = new resources::Text(m_device, m_frameBufferSize, text, font, pso, cbs, pos, scale, padding, color, m_TextTab.size());

	m_TextTab.push_back(newText);
	return newText;
}

engine::rhi::resources::Text* engine::rhi::TextManager::GetTextByIndex(int index) const
{
	if (index < m_TextTab.size() && index >= 0)
		return m_TextTab[index];
	else
		return nullptr;
}

unsigned int engine::rhi::TextManager::GetTextNb() const
{
	return m_TextTab.size();
}
