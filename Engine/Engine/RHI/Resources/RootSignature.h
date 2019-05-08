#ifndef _ROOT_SIGNATURE_H_
#define _ROOT_SIGNATURE_H_

#include "../../../stdafx.h"

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class RootSignature
			{
			public:

				RootSignature(ID3D12Device* device, const int id, D3D12_ROOT_PARAMETER* rootParameter, int rootParameterCount,
					D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
					D3D12_ROOT_SIGNATURE_FLAGS flags = D3D12_ROOT_SIGNATURE_FLAG_NONE);
				~RootSignature();

				ID3D12RootSignature* GetRootSignature()const;
				D3D12_ROOT_PARAMETER* GetRootParameters()const;
				int GetRootParameterNb()const;
				D3D12_STATIC_SAMPLER_DESC* GetSamplers() const;
				int GetSamplerNb() const;
				const D3D12_ROOT_SIGNATURE_FLAGS GetFlags()const;
				const int GetId()const;

				void SetRootSignature(ID3D12RootSignature* newRS);
				void SetRootParameter(D3D12_ROOT_PARAMETER* newRP);
				void SetRootParameterNb(int newRPNb);
				void SetFlags(D3D12_ROOT_SIGNATURE_FLAGS newFlags);

				bool operator==(const RootSignature& other)const;
				bool operator!=(const RootSignature& other)const;

			private:

				ID3D12RootSignature* m_rootSignature;
				D3D12_ROOT_PARAMETER* m_rootParameters;
				int m_rootParameterNb;
				CD3DX12_ROOT_SIGNATURE_DESC m_rootSignatureDesc;
				ID3DBlob* m_signature;
				D3D12_STATIC_SAMPLER_DESC* m_samplers;
				int m_samplerNb;
				D3D12_ROOT_SIGNATURE_FLAGS m_flags;
				const int m_id;
			};
		}
	}
}

#endif
