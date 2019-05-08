#ifndef _RESOURCE__MATERIAL_H_
#define _RESOURCE__MATERIAL_H_

#include <string>
#include <vector>
#include "../Core/Maths/Vector/Vec4.h"
#include "ShaderProgram.h"
#include "Texture.h"

#define MAX_TEX_NB 32

namespace engine
{
	namespace resource
	{
		class Material
		{
		public:
			Material();
			Material(const Material& other) = default;
			Material(Material&& other) = default;
			Material(const std::string& name);
			~Material();

			bool Insert(size_t bufferID, Texture* texture);
			bool Insert(size_t bufferID, const engine::core::maths::Vec4& color);
			bool Insert(size_t bufferID, float factor);

			bool Insert(size_t bufferID, const std::vector<Texture*>& textures);

			const std::string& GetName() const;
			int* GetProgram() const;
			size_t GetProgramSize() const;
			// Returns a list of ids of the first texture of each buffer.
			std::vector<int> GetTextureIDs() const;
			// Returns a list of ids of each texture of the specified buffer.
			std::vector<int> GetTextureIDs(size_t bufferID) const;
			// Returns a list of samplers of the first texture of each buffer.
			std::vector<int> GetTextureSamplers() const;
			// Returns a list of samplers of each texture of the specified buffer.
			std::vector<int> GetTextureSamplers(size_t bufferID) const;

			void SetShaderProgram(ShaderProgram* shaderProgram);

		private:
			std::string		  m_name;
			ShaderProgram*	  m_shaderProgram;

			std::vector<std::vector<Texture*>>	  m_texturesBuffers;
			std::vector<engine::core::maths::Vec4>			  m_colorBuffer;
			std::vector<float>					  m_factorBuffer;
		};
	}
}
#endif