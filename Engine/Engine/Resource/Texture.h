#ifndef _RESOURCE__TEXTURE_H_
#define _RESOURCE__TEXTURE_H_

#include <string>

namespace engine
{
	namespace resource
	{
		class Texture
		{
		public:
			Texture(const Texture& other) = default;
			Texture(Texture&& other) = default;
			Texture(const std::string& name, int id, int sampler);
			~Texture() = default;

			const std::string& GetName() const;
			int GetID() const;
			int GetSampler() const;

			Texture& operator=(const Texture& other) = default;
			Texture& operator=(Texture&& other) = default;

		private:
			std::string m_name;
			int m_id;
			int m_sampler;
		};
	}
}
#endif