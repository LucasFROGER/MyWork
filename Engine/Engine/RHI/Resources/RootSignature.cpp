#include "RootSignature.h"

engine::rhi::resources::RootSignature::RootSignature(ID3D12Device* device, const int id, D3D12_ROOT_PARAMETER* rootParameter, int rootParameterCount,
								D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
								D3D12_ROOT_SIGNATURE_FLAGS flags) :
	m_id{ id },
	m_flags { flags },
	m_rootParameters{ rootParameter },
	m_rootParameterNb{ rootParameterCount },
	m_samplers{ samplers },
	m_samplerNb{ samplerNb }
{
	HRESULT hr;

	if (rootParameter == nullptr)
	{
		if (samplers == nullptr)
			m_rootSignatureDesc.Init(0, nullptr, 0, nullptr, flags);
		else
			m_rootSignatureDesc.Init(0, nullptr, m_samplerNb, m_samplers, flags);
	}
	else
	{
		if(samplers == nullptr)
			m_rootSignatureDesc.Init(rootParameterCount, rootParameter, 0, nullptr, flags);
		else
			m_rootSignatureDesc.Init(rootParameterCount, rootParameter, m_samplerNb, m_samplers, flags);
	}
	hr = D3D12SerializeRootSignature(&m_rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &m_signature, nullptr);
	if (FAILED(hr))
		MessageBox(0, L"Root serialization failed", L"Error", MB_OK);

	hr = device->CreateRootSignature(0, m_signature->GetBufferPointer(), m_signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
	if (FAILED(hr))
		MessageBox(0, L"Root signature creation failed", L"Error", MB_OK);
}

engine::rhi::resources::RootSignature::~RootSignature()
{
	SAFE_RELEASE(m_rootSignature);
	SAFE_DELETE(m_rootParameters);
}

ID3D12RootSignature* engine::rhi::resources::RootSignature::GetRootSignature() const
{
	return m_rootSignature;
}

D3D12_ROOT_PARAMETER* engine::rhi::resources::RootSignature::GetRootParameters() const
{
	return m_rootParameters;
}

int engine::rhi::resources::RootSignature::GetRootParameterNb() const
{
	return m_rootParameterNb;
}

const D3D12_ROOT_SIGNATURE_FLAGS engine::rhi::resources::RootSignature::GetFlags() const
{
	return m_flags;
}

const int engine::rhi::resources::RootSignature::GetId() const
{
	return m_id;
}

bool engine::rhi::resources::RootSignature::operator==(const RootSignature& other) const
{
	if (m_rootSignatureDesc.NumParameters == other.m_rootSignatureDesc.NumParameters &&
		m_rootSignatureDesc.NumStaticSamplers == other.m_rootSignatureDesc.NumStaticSamplers &&
		m_rootSignatureDesc.Flags == other.m_rootSignatureDesc.Flags)
	{
		for (unsigned int i{ 0 }; i < m_rootSignatureDesc.NumParameters; ++i)
		{
			if (m_rootSignatureDesc.pParameters[i].ParameterType != other.m_rootSignatureDesc.pParameters[i].ParameterType ||
				m_rootSignatureDesc.pParameters[i].ShaderVisibility != other.m_rootSignatureDesc.pParameters[i].ShaderVisibility)
			{
				return false;
			}
		}
		for (unsigned int i{ 0 }; i < m_rootSignatureDesc.NumStaticSamplers; ++i)
		{
			if (m_rootSignatureDesc.pStaticSamplers[i].AddressU != other.m_rootSignatureDesc.pStaticSamplers[i].AddressU ||
				m_rootSignatureDesc.pStaticSamplers[i].AddressV != other.m_rootSignatureDesc.pStaticSamplers[i].AddressV ||
				m_rootSignatureDesc.pStaticSamplers[i].AddressW != other.m_rootSignatureDesc.pStaticSamplers[i].AddressW ||
				m_rootSignatureDesc.pStaticSamplers[i].BorderColor != other.m_rootSignatureDesc.pStaticSamplers[i].BorderColor ||
				m_rootSignatureDesc.pStaticSamplers[i].ComparisonFunc != other.m_rootSignatureDesc.pStaticSamplers[i].ComparisonFunc ||
				m_rootSignatureDesc.pStaticSamplers[i].Filter != other.m_rootSignatureDesc.pStaticSamplers[i].Filter ||
				m_rootSignatureDesc.pStaticSamplers[i].MaxAnisotropy != other.m_rootSignatureDesc.pStaticSamplers[i].MaxAnisotropy ||
				m_rootSignatureDesc.pStaticSamplers[i].MaxLOD != other.m_rootSignatureDesc.pStaticSamplers[i].MaxLOD ||
				m_rootSignatureDesc.pStaticSamplers[i].MinLOD != other.m_rootSignatureDesc.pStaticSamplers[i].MinLOD ||
				m_rootSignatureDesc.pStaticSamplers[i].MipLODBias != other.m_rootSignatureDesc.pStaticSamplers[i].MipLODBias ||
				m_rootSignatureDesc.pStaticSamplers[i].RegisterSpace != other.m_rootSignatureDesc.pStaticSamplers[i].RegisterSpace ||
				m_rootSignatureDesc.pStaticSamplers[i].ShaderRegister != other.m_rootSignatureDesc.pStaticSamplers[i].ShaderRegister ||
				m_rootSignatureDesc.pStaticSamplers[i].ShaderVisibility != other.m_rootSignatureDesc.pStaticSamplers[i].ShaderVisibility)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool engine::rhi::resources::RootSignature::operator!=(const RootSignature& other) const
{
	if (m_rootSignatureDesc.NumParameters == other.m_rootSignatureDesc.NumParameters &&
		m_rootSignatureDesc.NumStaticSamplers == other.m_rootSignatureDesc.NumStaticSamplers &&
		m_rootSignatureDesc.Flags == other.m_rootSignatureDesc.Flags)
	{
		for (unsigned int i{ 0 }; i < m_rootSignatureDesc.NumParameters; ++i)
		{
			if (m_rootSignatureDesc.pParameters[i].ParameterType != other.m_rootSignatureDesc.pParameters[i].ParameterType ||
				m_rootSignatureDesc.pParameters[i].ShaderVisibility != other.m_rootSignatureDesc.pParameters[i].ShaderVisibility)
			{
				return true;
			}
		}
		for (unsigned int i{ 0 }; i < m_rootSignatureDesc.NumStaticSamplers; ++i)
		{
			if (m_rootSignatureDesc.pStaticSamplers[i].AddressU != other.m_rootSignatureDesc.pStaticSamplers[i].AddressU ||
				m_rootSignatureDesc.pStaticSamplers[i].AddressV != other.m_rootSignatureDesc.pStaticSamplers[i].AddressV ||
				m_rootSignatureDesc.pStaticSamplers[i].AddressW != other.m_rootSignatureDesc.pStaticSamplers[i].AddressW ||
				m_rootSignatureDesc.pStaticSamplers[i].BorderColor != other.m_rootSignatureDesc.pStaticSamplers[i].BorderColor ||
				m_rootSignatureDesc.pStaticSamplers[i].ComparisonFunc != other.m_rootSignatureDesc.pStaticSamplers[i].ComparisonFunc ||
				m_rootSignatureDesc.pStaticSamplers[i].Filter != other.m_rootSignatureDesc.pStaticSamplers[i].Filter ||
				m_rootSignatureDesc.pStaticSamplers[i].MaxAnisotropy != other.m_rootSignatureDesc.pStaticSamplers[i].MaxAnisotropy ||
				m_rootSignatureDesc.pStaticSamplers[i].MaxLOD != other.m_rootSignatureDesc.pStaticSamplers[i].MaxLOD ||
				m_rootSignatureDesc.pStaticSamplers[i].MinLOD != other.m_rootSignatureDesc.pStaticSamplers[i].MinLOD ||
				m_rootSignatureDesc.pStaticSamplers[i].MipLODBias != other.m_rootSignatureDesc.pStaticSamplers[i].MipLODBias ||
				m_rootSignatureDesc.pStaticSamplers[i].RegisterSpace != other.m_rootSignatureDesc.pStaticSamplers[i].RegisterSpace ||
				m_rootSignatureDesc.pStaticSamplers[i].ShaderRegister != other.m_rootSignatureDesc.pStaticSamplers[i].ShaderRegister ||
				m_rootSignatureDesc.pStaticSamplers[i].ShaderVisibility != other.m_rootSignatureDesc.pStaticSamplers[i].ShaderVisibility)
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

void engine::rhi::resources::RootSignature::SetRootSignature(ID3D12RootSignature* newRS)
{
	m_rootSignature = newRS;
}

void engine::rhi::resources::RootSignature::SetRootParameter(D3D12_ROOT_PARAMETER* newRP)
{
	m_rootParameters = newRP;
}

void engine::rhi::resources::RootSignature::SetRootParameterNb(int newRPNb)
{
	m_rootParameterNb = newRPNb;
}

D3D12_STATIC_SAMPLER_DESC* engine::rhi::resources::RootSignature::GetSamplers() const
{
	return m_samplers;
}

int engine::rhi::resources::RootSignature::GetSamplerNb() const
{
	return m_samplerNb;
}

void engine::rhi::resources::RootSignature::SetFlags(D3D12_ROOT_SIGNATURE_FLAGS newFlags)
{
	m_flags = newFlags;
}
