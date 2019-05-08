#include "RootSignatureManager.h"

engine::rhi::RootSignatureManager::RootSignatureManager(ID3D12Device* device) : m_device { device }
{}

engine::rhi::RootSignatureManager::~RootSignatureManager()
{
	SAFE_DELETE_VECTOR(m_rootSignatures);
}

engine::rhi::resources::RootSignature* engine::rhi::RootSignatureManager::FindRootSignature(D3D12_ROOT_PARAMETER* rootParameters, int rootParameterNb,
														D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
														D3D12_ROOT_SIGNATURE_FLAGS flags)
{
	bool exist = true;
	for (unsigned int i{ 0 }; i < m_rootSignatures.size(); ++i)
	{
		if (m_rootSignatures[i]->GetFlags() == flags &&
			m_rootSignatures[i]->GetRootParameterNb() == rootParameterNb &&
			m_rootSignatures[i]->GetSamplerNb() == samplerNb)
		{
			for (unsigned int j{ 0 }; j < rootParameterNb; ++j)
			{
				if (m_rootSignatures[i]->GetRootParameters()[j].ParameterType != rootParameters[j].ParameterType ||
					m_rootSignatures[i]->GetRootParameters()[j].ShaderVisibility != rootParameters[j].ShaderVisibility)
				{
					exist = false;
				}
			}
			for (unsigned int j{ 0 }; j < samplerNb; ++j)
			{
				if (m_rootSignatures[i]->GetSamplers()[j].AddressU != samplers[j].AddressU ||
					m_rootSignatures[i]->GetSamplers()[j].AddressV != samplers[j].AddressV ||
					m_rootSignatures[i]->GetSamplers()[j].AddressW != samplers[j].AddressW ||
					m_rootSignatures[i]->GetSamplers()[j].BorderColor != samplers[j].BorderColor ||
					m_rootSignatures[i]->GetSamplers()[j].ComparisonFunc != samplers[j].ComparisonFunc ||
					m_rootSignatures[i]->GetSamplers()[j].Filter != samplers[j].Filter ||
					m_rootSignatures[i]->GetSamplers()[j].MaxAnisotropy != samplers[j].MaxAnisotropy ||
					m_rootSignatures[i]->GetSamplers()[j].MaxLOD != samplers[j].MaxAnisotropy ||
					m_rootSignatures[i]->GetSamplers()[j].MinLOD != samplers[j].MinLOD ||
					m_rootSignatures[i]->GetSamplers()[j].MipLODBias != samplers[j].MipLODBias ||
					m_rootSignatures[i]->GetSamplers()[j].RegisterSpace != samplers[j].RegisterSpace ||
					m_rootSignatures[i]->GetSamplers()[j].ShaderRegister != samplers[j].ShaderRegister ||
					m_rootSignatures[i]->GetSamplers()[j].ShaderVisibility != samplers[j].ShaderVisibility)
				{
					exist = false;
				}
			}
			if (exist)
				return m_rootSignatures[i];
		}
	}

	resources::RootSignature* newRootSignature = new resources::RootSignature(m_device, m_rootSignatures.size(), rootParameters, rootParameterNb, samplers, samplerNb, flags);
	m_rootSignatures.push_back(newRootSignature);
	return newRootSignature;
}

engine::rhi::resources::RootSignature* engine::rhi::RootSignatureManager::GetRootSignatureByIndex(int index) const
{
	if (index < m_rootSignatures.size())
		return m_rootSignatures[index];
	return nullptr;
}