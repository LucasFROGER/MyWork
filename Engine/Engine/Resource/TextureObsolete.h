#ifndef _RESOURCE__TEXTURE_H_
#define _RESOURCE__TEXTURE_H_

#include <string>

namespace resource
{
	class Texture
	{
	public:
		Texture(const std::string& filePath, const std::string& name);
		~Texture() = default;

		const std::string&	  GetFilePath() const;
		const std::string&	  GetName() const;
		size_t				  GetID() const;
		int					  GetWidth() const;
		int					  GetHeight() const;
		int					  GetNbChannels() const;

		void SetFilePath(const std::string& filePath);
		void SetName(const std::string& name);
		void SetID(size_t id);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetNbChannels(int nbChannels);

	private:
		std::string m_filePath;
		std::string m_name;
		size_t m_id;
		int m_width;
		int m_height;
		int m_nbChannels;
	};
}

#endif