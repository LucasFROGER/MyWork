#include "ConstantBuffer.h"

engine::rhi::resources::ConstantBuffer::ConstantBuffer(ID3D12Device* device) :
	m_device{ device }

{}

engine::rhi::resources::ConstantBuffer::~ConstantBuffer()
{
	for (int i = 0; i < m_frameBufferSize; ++i)
	{
		SAFE_RELEASE(m_cbUploadHeap[i]);

	}
	SAFE_DELETE_ARRAY(m_cbUploadHeap);
	SAFE_DELETE_ARRAY(m_cbGPUAddress);
	SAFE_DELETE(m_rootParameters);
}

D3D12_ROOT_PARAMETER* engine::rhi::resources::ConstantBuffer::GetRootParameters() const
{
	return m_rootParameters;
}

int engine::rhi::resources::ConstantBuffer::GetRootParametersNb() const
{
	return m_rootParameterNb;
}

ID3D12Resource** engine::rhi::resources::ConstantBuffer::GetCbUploadHeap() const
{
	return m_cbUploadHeap;
}

UINT8** engine::rhi::resources::ConstantBuffer::GetGPUAddress() const
{
	return m_cbGPUAddress;
}

int engine::rhi::resources::ConstantBuffer::GetRegisterNb() const
{
	return m_registerNb;
}

engine::rhi::resources::EShaderEnum engine::rhi::resources::ConstantBuffer::GetShaderVisibility() const
{
	return m_shaderVisibility;
}
