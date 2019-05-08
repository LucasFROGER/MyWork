#include "Font.h"

using namespace engine::resource;

Font::Font(const std::string& name, int id, int sampler) :
	m_name{ name },
	m_id{ id },
	m_sampler{ sampler }
{}

const std::string& Font::GetName() const
{
	return m_name;
}

int Font::GetID() const
{
	return m_id;
}

int* Font::GetSampler()
{
	if (m_sampler == -1)
		return nullptr;
	return &m_sampler;
}

int engine::resource::Font::GetSamplerNum() const
{
	if (m_sampler == -1)
		return 0;
	return 1;
}
