#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "Resources/Texture.h"

namespace engine
{
	namespace rhi
	{
		class TextureManager
		{

		public:

			TextureManager(ID3D12Device* device);
			~TextureManager();

			resources::Texture* FindTexture(const wchar_t* path);
			resources::Texture* GetTextureByIndex(int index) const;

		private:

			ID3D12Device* m_device;
			std::vector<resources::Texture*> m_textureTab;

		};
	}
}
#endif
