#ifndef _RESOURCE__SHADER_H_
#define _RESOURCE__SHADER_H_

#include <string>

#include "../RHI/Resources/ShaderEnum.h"

namespace engine
{
	namespace resource
	{
		class Shader
		{
		public:
			Shader(const Shader& other) = default;
			Shader(Shader&& other) = default;
			//Shader(const std::string& name);
			Shader(const std::string& name, int id, engine::rhi::resources::EShaderEnum type);
			~Shader() = default;

			//void SetID(int id);
			//void SetType(engine::rhi::resource::EShaderEnum type);

			const std::string& GetName() const;
			int GetID() const;
			engine::rhi::resources::EShaderEnum GetType() const;

			Shader& operator=(const Shader& other) = default;
			Shader& operator=(Shader&& other) = default;

		private:
			std::string m_name;
			int m_id;
			engine::rhi::resources::EShaderEnum m_type;
		};
	}
}
#endif