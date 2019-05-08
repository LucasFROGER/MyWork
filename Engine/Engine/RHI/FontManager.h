#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include "Resources/FontInfo.h"

namespace engine
{
	namespace rhi
	{
		class FontManager
		{

		public:

			FontManager(ID3D12Device* device);
			~FontManager();

			void ClearFonts();

			resources::FontInfo* FindFont(resources::FontInfo* info);
			resources::FontInfo* GetFontByIndex(int index)const;
			unsigned int GetFontNb() const;

		private:

			ID3D12Device * m_device;
			std::vector<resources::FontInfo*> m_fontTab;


		};
	}
}

#endif
