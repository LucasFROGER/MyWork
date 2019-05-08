#ifndef _ROOT_SIGNATURE_MANAGER_H_
#define _ROOT_SIGNATURE_MANAGER_H_

#include "Resources/RootSignature.h"
#include <vector>

namespace engine
{
	namespace rhi
	{
		class RootSignatureManager
		{
		public:

			RootSignatureManager(ID3D12Device* device);
			~RootSignatureManager();

			resources::RootSignature* FindRootSignature(D3D12_ROOT_PARAMETER* rootParameters, int rootParameterNb,
									D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
									D3D12_ROOT_SIGNATURE_FLAGS flags);
			resources::RootSignature* GetRootSignatureByIndex(int index)const;
		private:

			ID3D12Device* m_device;
			std::vector<resources::RootSignature*> m_rootSignatures;
		};
	}
}
#endif
