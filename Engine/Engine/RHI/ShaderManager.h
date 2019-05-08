#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "Resources/Shader.h"
namespace engine
{
	namespace rhi
	{
		class ShaderManager
		{
		public:

			ShaderManager(ID3D12Device* device);
			~ShaderManager();

			resources::Shader* FindShader(std::wstring path, resources::EShaderEnum type);
			resources::Shader* GetShaderByIndex(int index) const;

		private:

			ID3D12Device* m_device;
			std::vector<resources::Shader*> m_shaderTab;


		};
	}
}

#endif
