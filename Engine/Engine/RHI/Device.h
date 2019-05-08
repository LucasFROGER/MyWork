#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "ResourcesManager.h"

namespace engine
{
	namespace rhi
	{
		class Device
		{
		public:

			Device(const int frameBufferSize);
			~Device();


			ID3D12Device* GetDevice() const;
			const int GetFrameBufferSize() const;
			IDXGIFactory4* GetFactory() const;
			ResourcesManager* GetResourcesManager() const;

		private:

			ID3D12Device* m_device;
			IDXGIFactory4* m_factory;
			const int m_frameBufferSize;
			ResourcesManager* m_resourcesManager;

			bool InitDevice();

		};
	}
}
#endif
