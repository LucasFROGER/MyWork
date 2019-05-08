#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../../../stdafx.h"
#include "ShaderEnum.h"
#include <wincodec.h>

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class Texture
			{

			public:
				Texture(ID3D12Device* device, const wchar_t* path, const int id);
				~Texture();

				const std::wstring& GetPath() const;
				int GetId() const;
				EShaderEnum GetShaderVisibility() const;
				ID3D12Resource* GetBuffer() const;
				ID3D12Resource* GetUploadHeap() const;
				D3D12_RESOURCE_DESC GetDesc() const;
				D3D12_SUBRESOURCE_DATA GetData() const;
				D3D12_SHADER_RESOURCE_VIEW_DESC GetsrvDesc() const;
				UINT GetHangleSize() const;
				DXGI_FORMAT engine::rhi::resources::Texture::GetDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID);
				WICPixelFormatGUID Texture::GetConvertToWICFormat(WICPixelFormatGUID& wicFormatGUID);
				int Texture::GetDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat);
				int Texture::LoadImageDataFromFile(BYTE** imageData, D3D12_RESOURCE_DESC& resourceDescription, LPCWSTR filename, int &bytesPerRow);

				bool operator==(const Texture& other) const;

			private:
				const std::wstring m_path;
				int m_id;
				EShaderEnum m_shaderVisibility;
				ID3D12Resource* m_textureBuffer;
				ID3D12Resource* m_textureBufferUploadHeap;
				D3D12_RESOURCE_DESC m_textureDesc;
				D3D12_SUBRESOURCE_DATA m_textureData;
				D3D12_SHADER_RESOURCE_VIEW_DESC m_srvDesc;
				D3D12_DESCRIPTOR_HEAP_DESC m_heapDesc;
				UINT m_srvHandleSize;
				BYTE* m_imageData;

			};
		}
	}
}
#endif // _TEXTURE_H_
