#ifndef _SAMPLER_MANAGER_H_
#define _SAMPLER_MANAGER_H_

#include "../../stdafx.h"
namespace engine
{
	namespace rhi
	{
		class SamplerManager
		{
		public:
			SamplerManager(ID3D12Device* device);
			~SamplerManager();

			int FindSampler(D3D12_FILTER filters, int registerNb, int MaxAnisotropy, float minLOD, float maxLOD);
			D3D12_STATIC_SAMPLER_DESC GetSamplerByIndex(int index);

		private:

			ID3D12Device* m_device;
			std::vector<D3D12_STATIC_SAMPLER_DESC> m_samplers;

		};
	}
}
#endif
