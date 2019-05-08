#include "RenderObject.h"

engine::rhi::resources::RenderObject::RenderObject(ID3D12Device* device, PSO* pso, RootSignature* rootSignature,
	std::vector<ConstantBuffer*> cb, std::vector<Texture*> textures, D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
	float* vertexBuffer, int strideInBytes, int vBufferSize,
	int* iList, int iBufferSize, bool isStatic, const int id) :
	m_device{ device },
	m_pso{ pso },
	m_rootSignature{ rootSignature },
	m_constantBuffers{ cb },
	m_textures{ textures },
	m_samplers{ samplers },
	m_samplerNb{ samplerNb },
	m_vList{ vertexBuffer },
	m_strideInBytes{ strideInBytes },
	m_vBufferSize{ vBufferSize },
	m_iList{ iList },
	m_iBufferSize{ iBufferSize },
	m_static{ isStatic },
	m_rendered{ false },
	m_id{ id },
	m_mainDescriptorHeap{ NULL }
{
	if (m_textures.size() > 0)
	{
		m_heapDesc = {};
		m_heapDesc.NumDescriptors = m_textures.size();
		m_heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		m_heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		m_device->CreateDescriptorHeap(&m_heapDesc, IID_PPV_ARGS(&m_mainDescriptorHeap));

		UINT srvHandleSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		for (int i{ 0 }; i < m_textures.size(); ++i)
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(m_mainDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), i, srvHandleSize);
			m_device->CreateShaderResourceView(m_textures[i]->GetBuffer(), &m_textures[i]->GetsrvDesc(), srvHandle);
		}
	}
	m_device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), // a default heap
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(vBufferSize),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_vertexBuffer));
	m_vertexBuffer->SetName(L"Vertex Buffer Resource Heap");
	m_device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // upload heap
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(vBufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_vBufferUploadHeap));
	m_vBufferUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");
	// store vertex buffer in upload heap
	m_vertexData.pData = reinterpret_cast<BYTE*>(&vertexBuffer[0]);
	m_vertexData.RowPitch = vBufferSize;
	m_vertexData.SlicePitch = vBufferSize;
	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.StrideInBytes = strideInBytes;
	m_vertexBufferView.SizeInBytes = vBufferSize;
	if (iBufferSize > 0)
	{
		//IndexBuffer
		m_device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), // a default heap
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(m_iBufferSize),
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&m_indexBuffer));
		m_indexBuffer->SetName(L"Index Buffer Resource Heap");
		m_device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // upload heap
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(iBufferSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_iBufferUploadHeap));
		m_iBufferUploadHeap->SetName(L"Index Buffer Upload Resource Heap");
		m_indexData.pData = reinterpret_cast<BYTE*>(&iList[0]);
		m_indexData.RowPitch = iBufferSize;
		m_indexData.SlicePitch = iBufferSize;
		m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format = DXGI_FORMAT_R32_UINT; // 32-bit unsigned integer (this is what a dword is, double word, a word is 2 bytes)
		m_indexBufferView.SizeInBytes = iBufferSize;
	}
}
engine::rhi::resources::RenderObject::~RenderObject()
{
	SAFE_RELEASE(m_mainDescriptorHeap);
	SAFE_DELETE(m_mainDescriptorHeap);
	SAFE_DELETE_ARRAY(m_samplers);
	SAFE_RELEASE(m_vertexBuffer);
	if(m_iBufferSize > 0)
		SAFE_RELEASE(m_indexBuffer);
}

engine::rhi::resources::PSO* engine::rhi::resources::RenderObject::GetPso() const
{
	return m_pso;
}

engine::rhi::resources::RootSignature* engine::rhi::resources::RenderObject::GetRootSignature() const
{
	return m_rootSignature;
}

float* engine::rhi::resources::RenderObject::GetVList() const
{
	return m_vList;
}

int engine::rhi::resources::RenderObject::GetStrideInBytes() const
{
	return m_strideInBytes;
}

int engine::rhi::resources::RenderObject::GetVBufferSize() const
{
	return m_vBufferSize;
}

int* engine::rhi::resources::RenderObject::GetIndexList() const
{
	return m_iList;
}

int engine::rhi::resources::RenderObject::GetIndexBufferSize() const
{
	return m_iBufferSize;
}

ID3D12Resource* engine::rhi::resources::RenderObject::GetVertexBuffer() const
{
	return m_vertexBuffer;
}

D3D12_VERTEX_BUFFER_VIEW engine::rhi::resources::RenderObject::GetVertexBufferView() const
{
	return m_vertexBufferView;
}

ID3D12Resource* engine::rhi::resources::RenderObject::GetvBufferUploadHeap() const
{
	return m_vBufferUploadHeap;
}

D3D12_SUBRESOURCE_DATA engine::rhi::resources::RenderObject::GetVertexData() const
{
	return m_vertexData;
}

ID3D12Resource* engine::rhi::resources::RenderObject::GetIndexBuffer() const
{
	return m_indexBuffer;
}

D3D12_INDEX_BUFFER_VIEW engine::rhi::resources::RenderObject::GetIndexBufferView() const
{
	return m_indexBufferView;
}

ID3D12Resource* engine::rhi::resources::RenderObject::GetIndexBufferUploadHeap()const
{
	return m_iBufferUploadHeap;
}

D3D12_SUBRESOURCE_DATA engine::rhi::resources::RenderObject::GetIndexData() const
{
	return m_indexData;
}

ID3D12DescriptorHeap* engine::rhi::resources::RenderObject::GetMainDescriptorHeap() const
{
	return m_mainDescriptorHeap;
}

D3D12_DESCRIPTOR_HEAP_DESC engine::rhi::resources::RenderObject::GetHeapDesc() const
{
	return m_heapDesc;
}

std::vector<engine::rhi::resources::ConstantBuffer*> engine::rhi::resources::RenderObject::GetConstantBuffer() const
{
	return m_constantBuffers;
}

std::vector<engine::rhi::resources::Texture*> engine::rhi::resources::RenderObject::GetTextures() const
{
	return m_textures;
}

D3D12_STATIC_SAMPLER_DESC* engine::rhi::resources::RenderObject::GetSamplers() const
{
	return m_samplers;
}

int engine::rhi::resources::RenderObject::GetSamplerNb() const
{
	return m_samplerNb;
}

bool engine::rhi::resources::RenderObject::GetIsStatic() const
{
	return m_static;
}

bool engine::rhi::resources::RenderObject::GetIsRendered() const
{
	return m_rendered;
}

const int engine::rhi::resources::RenderObject::GetId() const
{
	return m_id;
}

void engine::rhi::resources::RenderObject::SetIsRendered(bool newRendered)
{
	m_rendered = newRendered;
}

void engine::rhi::resources::RenderObject::SetRootSignature(RootSignature* newRS)
{
	m_rootSignature = newRS;
}

void engine::rhi::resources::RenderObject::SetPSO(PSO* newPSO)
{
	m_pso = newPSO;
}

void engine::rhi::resources::RenderObject::SetConstantBuffers(std::vector<ConstantBuffer*> newCB)
{
	m_constantBuffers = newCB;
}

void engine::rhi::resources::RenderObject::SetTextures(std::vector<Texture*> newTex)
{
	HRESULT hr;
	//SAFE_RELEASE(m_mainDescriptorHeap);

	m_textures = newTex;

	if (m_textures.size() > 0)
	{
		m_heapDesc.NumDescriptors = m_textures.size();
		m_heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		m_heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		m_heapDesc.NodeMask = 0;
		hr = m_device->CreateDescriptorHeap(&m_heapDesc, IID_PPV_ARGS(&m_mainDescriptorHeap));

		if (FAILED(hr))
		{
			MessageBox(NULL, L"Couldn't create mainDescriptorHeap", L"Error", MB_OK | MB_ICONERROR);

		}

		UINT srvHandleSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		for (int i{ 0 }; i < m_textures.size(); ++i)
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(m_mainDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), i, srvHandleSize);
			m_device->CreateShaderResourceView(m_textures[i]->GetBuffer(), &m_textures[i]->GetsrvDesc(), srvHandle);
		}
	}
	else
		m_mainDescriptorHeap = NULL;

}

void engine::rhi::resources::RenderObject::SetSamplers(D3D12_STATIC_SAMPLER_DESC* newSamplers, int newSamplerNb)
{
	m_samplers = newSamplers;
	m_samplerNb = newSamplerNb;
}