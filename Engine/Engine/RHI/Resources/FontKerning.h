#ifndef _FONT_KERNING_H_
#define _FONT_KERNING_H_

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			struct FontKerning
			{
				int firstid; // the first character
				int secondid; // the second character
				float amount; // the amount to add/subtract to second characters x

				bool operator==(const FontKerning& other) const
				{
					if (firstid == other.firstid && secondid == other.secondid && amount == other.amount)
						return true;
					else
						return false;
				}
			};
		}
	}
}

#endif
