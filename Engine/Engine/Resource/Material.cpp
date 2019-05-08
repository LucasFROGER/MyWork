#include "Material.h"

using namespace engine::core::maths;

engine::resource::Material::Material() :
	m_name{ "" },
	m_shaderProgram{ nullptr },
	m_texturesBuffers(MAX_TEX_NB),
	m_colorBuffer(MAX_TEX_NB, Vec4::Zero()),
	m_factorBuffer(MAX_TEX_NB, 0.0f)
{}

engine::resource::Material::Material(const std::string& name) :
	m_name{ name },
	m_shaderProgram{ nullptr },
	m_texturesBuffers(MAX_TEX_NB),
	m_colorBuffer(MAX_TEX_NB, Vec4::Zero()),
	m_factorBuffer(MAX_TEX_NB, 0.0f)
{}

engine::resource::Material::~Material()
{
	//m_shaderProgram.Destroy();
}

bool engine::resource::Material::Insert(size_t bufferID, Texture* texture)
{
	// TODO: if (texture == nullptr) { texture = Texture::Default() }

	if (bufferID >= MAX_TEX_NB)
		return false;

	auto textureBufferPtr{ m_texturesBuffers.data() + bufferID };
	textureBufferPtr->clear();
	textureBufferPtr->emplace_back(texture);

	return true;
}

bool engine::resource::Material::Insert(size_t bufferID, const Vec4& color)
{
	if (bufferID >= MAX_TEX_NB)
		return false;

	*(m_colorBuffer.data() + bufferID) = color;

	return true;
}

bool engine::resource::Material::Insert(size_t bufferID, float factor)
{
	if (bufferID >= MAX_TEX_NB)
		return false;

	*(m_factorBuffer.data() + bufferID) = factor;

	return true;
}

bool engine::resource::Material::Insert(size_t bufferID, const std::vector<Texture*>& textures)
{
	// TODO: if (textures[i] == nullptr) { textures[i] = Texture::Default() }

	if (bufferID >= MAX_TEX_NB)
		return false;

	auto textureBufferPtr{ m_texturesBuffers.data() + bufferID };
	textureBufferPtr->clear();

	if (textures.size() <= MAX_TEX_NB)
		*textureBufferPtr = textures;
	else
		textureBufferPtr->assign(textures.begin(), textures.begin() + MAX_TEX_NB);

	return true;
}

const std::string& engine::resource::Material::GetName() const
{
	return m_name;
}

int* engine::resource::Material::GetProgram() const
{
	if (m_shaderProgram != nullptr)
		return m_shaderProgram->GetProgramAddress();

	return nullptr;
}

size_t engine::resource::Material::GetProgramSize() const
{
	if (m_shaderProgram != nullptr)
		return m_shaderProgram->GetProgramSize();

	return 0;
}

std::vector<int> engine::resource::Material::GetTextureIDs() const
{
	std::vector<int> textureIDs;
	const std::vector<Texture*>* texturesBufferPtr{ nullptr };

	for (size_t index{ 0 }; index < MAX_TEX_NB; ++index)
	{
		texturesBufferPtr = (m_texturesBuffers.data() + index);
		if (texturesBufferPtr->size() > 0)
			textureIDs.push_back((*texturesBufferPtr)[0]->GetID());
	}

	return textureIDs;
}

std::vector<int> engine::resource::Material::GetTextureIDs(size_t bufferID) const
{
	std::vector<int> textureIDs;

	if (bufferID >= MAX_TEX_NB)
		return textureIDs;

	auto textureBufferPtr{ m_texturesBuffers.data() + bufferID };
	for (size_t index{ 0 }; index < textureBufferPtr->size(); ++index)
		textureIDs.emplace_back((*textureBufferPtr)[index]->GetID());

	return textureIDs;
}

std::vector<int> engine::resource::Material::GetTextureSamplers() const
{
	std::vector<int> textureIDs;
	const std::vector<Texture*>* texturesBufferPtr{ nullptr };

	for (size_t index{ 0 }; index < MAX_TEX_NB; ++index)
	{
		texturesBufferPtr = (m_texturesBuffers.data() + index);
		if (texturesBufferPtr->size() > 0)
			textureIDs.push_back((*texturesBufferPtr)[0]->GetSampler());
	}

	return textureIDs;
}

std::vector<int> engine::resource::Material::GetTextureSamplers(size_t bufferID) const
{
	std::vector<int> textureSamplers;

	if (bufferID >= MAX_TEX_NB)
		return textureSamplers;

	auto textureBufferPtr{ m_texturesBuffers.data() + bufferID };
	for (size_t index{ 0 }; index < textureBufferPtr->size(); ++index)
		textureSamplers.emplace_back((*textureBufferPtr)[index]->GetSampler());

	return textureSamplers;
}

void engine::resource::Material::SetShaderProgram(ShaderProgram* shaderProgram)
{
	m_shaderProgram = shaderProgram;
}
