#ifndef _CONSTANT_BUFFER_MANAGER_H_
#define _CONSTANT_BUFFER_MANAGER_H_

#include "../../stdafx.h"
#include "Resources/ConstantBuffer.h"

namespace engine
{
	namespace rhi
	{
		class ConstantBufferManager
		{
		public:

			ConstantBufferManager(ID3D12Device* device);
			~ConstantBufferManager();

			template<typename T>
			int AddConstantBuffer(T* data, int sizeofData, int registerNb, int frameBufferCount, resources::EShaderEnum shaderVisibility = resources::EShaderEnum::COUNT)
			{
				resources::ConstantBuffer* cb = new resources::ConstantBuffer(m_device);
				cb->Initialize(data, sizeofData, registerNb, frameBufferCount, shaderVisibility);
				m_constantBuffers.push_back(cb);
				return (int)(m_constantBuffers.size() - 1);
			}
			resources::ConstantBuffer* GetConstantBufferByIndex(int index) const;

		private:

			ID3D12Device* m_device;
			std::vector<resources::ConstantBuffer*> m_constantBuffers;

		};
	}
}

#endif
