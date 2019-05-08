#include "Texture.h"

using namespace engine::resource;

Texture::Texture(const std::string& name, int id, int sampler) :
	m_name{ name },
	m_id{ id },
	m_sampler{ sampler }
{}

const std::string& Texture::GetName() const
{
	return m_name;
}

int Texture::GetID() const
{
	return m_id;
}

int Texture::GetSampler() const
{
	return m_sampler;
}
