#include "SamplerManager.h"

engine::rhi::SamplerManager::SamplerManager(ID3D12Device* device) : m_device{ device }
{}

engine::rhi::SamplerManager::~SamplerManager()
{
	m_samplers.clear();
}

int engine::rhi::SamplerManager::FindSampler(D3D12_FILTER filters, int registerNb, int MaxAnisotropy, float minLOD, float maxLOD)
{
	for (unsigned int i{ 0 }; i < m_samplers.size(); ++i)
		if (m_samplers[i].Filter == filters && m_samplers[i].MaxAnisotropy == MaxAnisotropy
			&& m_samplers[i].MinLOD == minLOD && m_samplers[i].MaxLOD == maxLOD &&
			m_samplers[i].ShaderRegister == registerNb)
			return i;

	D3D12_STATIC_SAMPLER_DESC newSampler; 

	newSampler.Filter = filters;
	newSampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	newSampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	newSampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	newSampler.MipLODBias = 0;
	newSampler.MaxAnisotropy = MaxAnisotropy;
	newSampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	newSampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	newSampler.MinLOD = minLOD;
	newSampler.MaxLOD = maxLOD;
	newSampler.ShaderRegister = registerNb;
	newSampler.RegisterSpace = 0;
	newSampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	m_samplers.push_back(newSampler);
	return m_samplers.size()-1;
}

D3D12_STATIC_SAMPLER_DESC engine::rhi::SamplerManager::GetSamplerByIndex(int index)
{
	return m_samplers[index];
}