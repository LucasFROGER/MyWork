#include "../../stdafx.h"
#include "Device.h"

engine::rhi::Device::Device(int frameBufferSize) : m_frameBufferSize(frameBufferSize)
{
	if (!InitDevice())
	{
		MessageBox(0, L"Device Initialization - Failed", L"Error", MB_OK);

	}
	m_resourcesManager = new ResourcesManager(m_device, m_frameBufferSize);
}

engine::rhi::Device::~Device()
{
	SAFE_RELEASE(m_device);
	SAFE_DELETE(m_device);
	SAFE_DELETE(m_resourcesManager);
}

bool engine::rhi::Device::InitDevice()
{
	HRESULT hr;

	hr = CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
	if (FAILED(hr))
	{
		return false;
	}

	IDXGIAdapter1* adapter;
	int adapterIndex = 0;
	bool adapterFound = false;
	while (m_factory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			continue;

		hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr);
		if (SUCCEEDED(hr))
		{
			adapterFound = true;
			break;
		}

		adapterIndex++;
	}

	if (!adapterFound)
	{
		return false;
	}

	hr = D3D12CreateDevice(
		adapter,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m_device)
	);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

ID3D12Device* engine::rhi::Device::GetDevice() const
{
	return m_device;
}

const int engine::rhi::Device::GetFrameBufferSize() const
{
	return m_frameBufferSize;
}

IDXGIFactory4* engine::rhi::Device::GetFactory() const
{
	return m_factory;
}

engine::rhi::ResourcesManager* engine::rhi::Device::GetResourcesManager() const
{
	return m_resourcesManager;
}