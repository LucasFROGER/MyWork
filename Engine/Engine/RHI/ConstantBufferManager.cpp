#include "ConstantBufferManager.h"

engine::rhi::ConstantBufferManager::ConstantBufferManager(ID3D12Device* device) : m_device{ device }
{}

engine::rhi::ConstantBufferManager::~ConstantBufferManager()
{
	SAFE_DELETE_VECTOR(m_constantBuffers);
}

engine::rhi::resources::ConstantBuffer* engine::rhi::ConstantBufferManager::GetConstantBufferByIndex(int index) const
{
	if (index < m_constantBuffers.size() && index >= 0)
		return m_constantBuffers[index];
	return nullptr;
}