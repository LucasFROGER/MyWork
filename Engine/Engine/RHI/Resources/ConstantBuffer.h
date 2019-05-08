#ifndef _CONSTANT_BUFFER_H_
#define _CONSTANT_BUFFER_H_

#include "../../../stdafx.h"
#include "ShaderEnum.h"

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class ConstantBuffer
			{
			public:

				ConstantBuffer(ID3D12Device* device);
				~ConstantBuffer();

				template<typename T>
				void Initialize(T* data, int sizeofData, int registerNb, int frameBufferSize, EShaderEnum shaderVisibility = EShaderEnum::COUNT)
				{
					if (!data)
						return;

					m_frameBufferSize = frameBufferSize;
					m_rootParameters = new D3D12_ROOT_PARAMETER;
					m_shaderVisibility = shaderVisibility;
					m_registerNb = registerNb;
					m_cbUploadHeap = new ID3D12Resource*[frameBufferSize];
					m_cbGPUAddress = new UINT8*[frameBufferSize];

					HRESULT hr;

					for (int i{ 0 }; i < frameBufferSize; ++i)
					{
						hr = m_device->CreateCommittedResource(
							&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // this heap will be used to upload the constant buffer data
							D3D12_HEAP_FLAG_NONE, // no flags
							&CD3DX12_RESOURCE_DESC::Buffer(1024 * 64), // size of the resource heap. Must be a multiple of 64KB for single-textures and constant buffers
							D3D12_RESOURCE_STATE_GENERIC_READ, // will be data that is read from so we keep it in the generic read state
							nullptr, // we do not have use an optimized clear value for constant buffers
							IID_PPV_ARGS(&m_cbUploadHeap[i]));
						m_cbUploadHeap[i]->SetName(L"Constant Buffer Upload Resource Heap");

						CD3DX12_RANGE readRange(0, 0);
						hr = m_cbUploadHeap[i]->Map(0, &readRange, reinterpret_cast<void**>(&m_cbGPUAddress[i]));
						memcpy(m_cbGPUAddress[i], data, sizeofData);
					}

					m_rootDescriptor.RegisterSpace = 0/*m_cbGPUAddress[0]*/;
					m_rootDescriptor.ShaderRegister = registerNb;

					m_rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
					m_rootParameters[0].Descriptor = m_rootDescriptor;

					switch (shaderVisibility)
					{
					case EShaderEnum::VERTEX_SHADER:
					{
						m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
						break;
					}

					case EShaderEnum::PIXEL_SHADER:
					{
						m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
						break;
					}

					case EShaderEnum::GEOMETRY_SHADER:
					{
						m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_GEOMETRY;
						break;
					}

					case EShaderEnum::HULL_SHADER:
					{
						m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_HULL;
						break;
					}

					case EShaderEnum::DOMAIN_SHADER:
					{
						m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_DOMAIN;
						break;
					}

					default:
					{
						m_rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
						break;
					}
					}

				}

				template<typename T>
				void Update(T* data, int sizeofData, int frameIndex)
				{
					if (data)
						memcpy(m_cbGPUAddress[frameIndex], data, sizeofData);
				}

				D3D12_ROOT_PARAMETER* GetRootParameters() const;
				int GetRootParametersNb() const;
				ID3D12Resource** GetCbUploadHeap() const;
				UINT8** GetGPUAddress() const;
				int GetRegisterNb() const;
				EShaderEnum GetShaderVisibility() const;

			private:

				ID3D12Device* m_device;
				int m_frameBufferSize;
				int m_registerNb;
				EShaderEnum m_shaderVisibility;
				ID3D12Resource** m_cbUploadHeap;
				D3D12_DESCRIPTOR_HEAP_DESC m_heapDesc;
				D3D12_CONSTANT_BUFFER_VIEW_DESC m_cbvDesc;
				UINT8** m_cbGPUAddress;
				D3D12_ROOT_DESCRIPTOR m_rootDescriptor;
				D3D12_ROOT_PARAMETER*  m_rootParameters;
				int m_rootParameterNb = 1;
			};
		}
	}
}

#endif
