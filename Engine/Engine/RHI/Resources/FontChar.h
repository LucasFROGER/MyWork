#ifndef _FONT_CHAR_H_
#define _FONT_CHAR_H_

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			struct FontChar
			{
				// the unicode id
				int id;

				// these need to be converted to texture coordinates 
				// (where 0.0 is 0 and 1.0 is textureWidth of the font)
				float u; // u texture coordinate
				float v; // v texture coordinate
				float twidth; // width of character on texture
				float theight; // height of character on texture

				float width; // width of character in screen coords
				float height; // height of character in screen coords

							  // these need to be normalized based on size of font
				float xoffset; // offset from current cursor pos to left side of character
				float yoffset; // offset from top of line to top of character
				float xadvance; // how far to move to right for next character

				bool operator==(const FontChar& other) const
				{
					if (u == other.u && v == other.v && twidth == other.twidth && width == other.width && height == other.height &&
						xoffset == other.xoffset && yoffset == other.xoffset && xadvance == other.xadvance && id == other.id)
						return true;
					else
						return false;
				}
			};
		}
	}
}

#endif