#include "FileProperties.h"

#include "../Core/Maths/Defines.h"

using namespace engine::loader;

EExtension engine::loader::GetExtension(const std::string& fileName)
{
	size_t it{ fileName.rfind('.') };
	if (it != std::string::npos)
	{
		std::string extension(fileName.substr(++it));
		if (extension == "fbx")
			return EExtension::FBX;
		else if (extension == "obj")
			return EExtension::OBJ;
		else if (extension == "jpg")
			return EExtension::JPG;
		else if (extension == "png")
			return EExtension::PNG;
		else if (extension == "vs")
			return EExtension::VS;
		else if (extension == "ps")
			return EExtension::PS;
		else if (extension == "gs")
			return EExtension::GS;
		else if (extension == "hs")
			return EExtension::HS;
		else if (extension == "ds")
			return EExtension::DS;
		else if (extension == "mp3")
			return EExtension::MP3;
		else if (extension == "wav")
			return EExtension::WAV;
		else if (extension == "ogg")
			return EExtension::OGG;
		else if (extension == "flac")
			return EExtension::FLAC;
		else if (extension == "fnt")
			return EExtension::FNT;
	}

	return EExtension::UNKNOWN;
}

std::string engine::loader::GetFileName(const std::string& filePath)
{
	size_t end{ filePath.rfind('.') };
	if (end == std::string::npos)
		end = filePath.length();

	size_t slash{ filePath.rfind('/') };
	size_t backslash{ filePath.rfind('\\') };

	size_t begin{ MAX(slash + 1, backslash + 1) };
	return filePath.substr(begin, end - begin);
}

std::string engine::loader::ToString(const EExtension& extension)
{
	switch (extension)
	{
	case EExtension::UNKNOWN:
		return "unknown";
	case EExtension::FBX:
		return "fbx";
	case EExtension::OBJ:
		return "obj";
	case EExtension::JPG:
		return "jpg";
	case EExtension::PNG:
		return "png";
	case EExtension::VS:
		return "vs";
	case EExtension::PS:
		return "ps";
	case EExtension::GS:
		return "gs";
	case EExtension::HS:
		return "hs";
	case EExtension::DS:
		return "ds";
	case EExtension::MP3:
		return "mp3";
	case EExtension::WAV:
		return "wav";
	case EExtension::OGG:
		return "ogg";
	case EExtension::FLAC:
		return "flac";
	default:
		return std::string();
	}
}

std::vector<wchar_t> engine::loader::ToWString(const std::string& str)
{
	const char* cPtr = str.c_str();
	std::vector<wchar_t> vec;
	size_t len = strlen(cPtr);
	vec.resize(len + 1);
	mbstowcs(vec.data(), cPtr, len);
	return vec;
}
