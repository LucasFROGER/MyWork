#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_

#include "../Resources/PSO.h"
#include "ConstantBuffer.h"
#include "Texture.h"

namespace engine
{

	namespace rhi
	{
		namespace resources
		{
			class RenderObject
			{
			public:

				RenderObject(ID3D12Device* device, PSO* pso, RootSignature* rootSignature,
					std::vector<ConstantBuffer*> cb, std::vector<Texture*> textures, D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
					float* vertexBuffer, int strideInBytes, int vBufferSize,
					int* iList, int ibufferSize, bool isStatic, const int id);
				~RenderObject();
				PSO* GetPso()const;
				RootSignature* GetRootSignature()const;
				float* GetVList()const;
				int GetStrideInBytes()const;
				int GetVBufferSize()const;
				int* GetIndexList()const;
				int GetIndexBufferSize()const;
				ID3D12Resource* GetVertexBuffer()const;
				D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView()const;
				ID3D12Resource* GetvBufferUploadHeap()const;
				D3D12_SUBRESOURCE_DATA GetVertexData()const;
				ID3D12Resource* GetIndexBuffer()const;
				D3D12_INDEX_BUFFER_VIEW GetIndexBufferView()const;
				ID3D12Resource* GetIndexBufferUploadHeap()const;
				D3D12_SUBRESOURCE_DATA GetIndexData()const;
				ID3D12DescriptorHeap* GetMainDescriptorHeap()const;
				D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc() const;
				std::vector<ConstantBuffer*> GetConstantBuffer()const;
				std::vector<Texture*> GetTextures() const;
				D3D12_STATIC_SAMPLER_DESC* GetSamplers() const;
				int GetSamplerNb() const;
				bool GetIsStatic() const;
				bool GetIsRendered()const;
				const int GetId()const;    void SetIsRendered(bool);

				void SetRootSignature(RootSignature* newRS);
				void SetPSO(PSO* newPSO);
				void SetConstantBuffers(std::vector<ConstantBuffer*> newCB);
				void SetTextures(std::vector<Texture*> newTex);
				void SetSamplers(D3D12_STATIC_SAMPLER_DESC* newSamplers, int newSamplerNb);

			private:

				ID3D12Device* m_device;
				PSO* m_pso;
				RootSignature* m_rootSignature;
				float* m_vList;
				int m_strideInBytes;
				int m_vBufferSize;
				int* m_iList;
				int m_iBufferSize;
				ID3D12Resource* m_vertexBuffer;
				D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
				ID3D12Resource* m_vBufferUploadHeap;
				D3D12_SUBRESOURCE_DATA m_vertexData;
				ID3D12Resource* m_indexBuffer;
				D3D12_INDEX_BUFFER_VIEW m_indexBufferView;
				ID3D12Resource* m_iBufferUploadHeap;
				D3D12_SUBRESOURCE_DATA m_indexData;
				ID3D12DescriptorHeap* m_mainDescriptorHeap;
				D3D12_DESCRIPTOR_HEAP_DESC m_heapDesc;
				std::vector<ConstantBuffer*> m_constantBuffers;
				std::vector<Texture*> m_textures;
				D3D12_STATIC_SAMPLER_DESC* m_samplers;
				int m_samplerNb;
				bool m_static;
				bool m_rendered;
				const int m_id;
			};
		}
	}
}

#endif
