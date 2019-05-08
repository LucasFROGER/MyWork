#ifndef _FILE_PROPERTIES_H_
#define _FILE_PROPERTIES_H_

#include <string>
#include <vector>

namespace engine
{
	namespace loader
	{
		enum class EExtension
		{
			UNKNOWN = -1,
			// Scene
			FBX,
			// Mesh
			OBJ,
			// Texture
			JPG,
			PNG,
			// Shader
			VS,
			PS,
			GS,
			HS,
			DS,
			// Audio
			MP3,
			WAV,
			OGG,
			FLAC,
			// Font
			FNT,


			COUNT
		};

		EExtension GetExtension(const std::string& fileName);
		std::string GetFileName(const std::string& filePath);
		std::string ToString(const EExtension& extension);
		std::vector<wchar_t> ToWString(const std::string& str);
	}
}

#endif