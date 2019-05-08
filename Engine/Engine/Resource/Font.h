#ifndef _RESOURCE__FONT_H_
#define _RESOURCE__FONT_H_

#include <string>

namespace engine
{
	namespace resource
	{
		class Font
		{
		public:
			Font(const Font& other) = default;
			Font(Font&& other) = default;
			Font(const std::string& name, int id, int sampler);
			~Font() = default;

			const std::string& GetName() const;
			int GetID() const;
			int* GetSampler();
			int GetSamplerNum() const;

			Font& operator=(const Font& other) = default;
			Font& operator=(Font&& other) = default;

		private:
			std::string m_name;
			int m_id;
			int m_sampler;
		};
	}
}
#endif