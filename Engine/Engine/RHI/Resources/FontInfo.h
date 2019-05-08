#ifndef _FONT_INFO_H_
#define _FONT_INFO_H_

#include "../../../stdafx.h"
#include "FontChar.h"
#include "FontKerning.h"
#include "Texture.h"

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class FontInfo
			{
			public:

				std::wstring m_name; // name of the font
				std::wstring m_fontImage;
				int m_size; // size of font, lineheight and baseheight will be based on this as if this is a single unit (1.0)
				int m_id = -1;
				float m_lineHeight; // how far to move down to next line, will be normalized
				float m_baseHeight; // height of all characters, will be normalized
				int m_textureWidth; // width of the font texture
				int m_textureHeight; // height of the font texture
				int m_numCharacters; // number of characters in the font
				FontChar* m_CharList = nullptr; // list of characters
				int m_numKernings; // the number of kernings
				FontKerning* m_KerningsList = nullptr; // list to hold kerning values

				// these are how much the character is padded in the texture. We
				// add padding to give sampling a little space so it does not accidentally
				// padd the surrounding characters. We will need to subtract these paddings
				// from the actual spacing between characters to remove the gaps you would otherwise see
				float m_leftpadding;
				float m_toppadding;
				float m_rightpadding;
				float m_bottompadding;

				Texture* m_fontTexture;

				// this will return the amount of kerning we need to use for two characters
				float GetKerning(wchar_t first, wchar_t second)
				{
					for (int i = 0; i < m_numKernings; ++i)
					{
						if ((wchar_t)m_KerningsList[i].firstid == first && (wchar_t)m_KerningsList[i].secondid == second)
							return m_KerningsList[i].amount;
					}
					return 0.0f;
				}

				// this will return a FontChar given a wide character
				FontChar* GetChar(wchar_t c)
				{
					for (int i = 0; i < m_numCharacters; ++i)
					{
						if (c == (wchar_t)m_CharList[i].id)
							return &m_CharList[i];
					}
					return nullptr;
				}

				bool operator==(const FontInfo& other) const
				{
					if (m_name == other.m_name)
						return true;
					else
						return false;
				}
			};
		}
	}
}

#endif