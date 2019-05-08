#include "Texture.h"

using namespace resource;

Texture::Texture(const std::string& filePath, const std::string& name) :
	m_filePath{ filePath },
	m_name{ name },
	m_id{ 0 },
	m_width{ -1 },
	m_height{ -1 },
	m_nbChannels{ -1 }
{}

const std::string& Texture::GetFilePath() const
{
	return m_filePath;
}

const std::string& Texture::GetName() const
{
	return m_name;
}

size_t Texture::GetID() const
{
	return m_id;
}

int Texture::GetWidth() const
{
	return m_width;
}

int Texture::GetHeight() const
{
	return m_height;
}

int Texture::GetNbChannels() const
{
	return m_nbChannels;
}

void Texture::SetFilePath(const std::string& filePath)
{
	m_filePath = filePath;
}

void Texture::SetName(const std::string& name)
{
	m_name = name;
}

void Texture::SetID(size_t id)
{
	m_id = id;
}

void Texture::SetWidth(int width)
{
	m_width = width;
}

void Texture::SetHeight(int height)
{
	m_height = height;
}

void Texture::SetNbChannels(int nbComponents)
{
	m_nbChannels = nbComponents;
}
