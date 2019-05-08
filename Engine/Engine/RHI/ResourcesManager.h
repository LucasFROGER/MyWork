#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "RenderObjectManager.h"
#include "RootSignatureManager.h"
#include "ShaderManager.h"
#include "PsoManager.h"
#include "ConstantBufferManager.h"
#include "TextureManager.h"
#include "SamplerManager.h"
#include "FontManager.h"
#include "TextManager.h"

namespace engine
{
	namespace rhi
	{
		class ResourcesManager
		{
		public:

			ResourcesManager(ID3D12Device* device, int frameBufferSize);
			~ResourcesManager();

			ID3D12Device* GetDevice()const;
			RenderObjectManager* GetRenderObjectManager()const;
			RootSignatureManager* GetRootSignatureManager()const;
			ShaderManager* GetShaderManager()const;
			PsoManager* GetPsoManager()const;
			ConstantBufferManager* GetConstantBufferManager()const;
			TextureManager* GetTextureManager() const;
			SamplerManager* GetSamplerManager() const;
			FontManager* GetFontManager() const;
			TextManager* GetTextManager() const;

		private:
			int m_frameBufferSize;
			ID3D12Device* m_device;
			RenderObjectManager* m_renderObjectManager;
			RootSignatureManager* m_rootSignatureManager;
			ShaderManager* m_shaderManager;
			PsoManager* m_psoManager;
			ConstantBufferManager* m_cbManager;
			TextureManager* m_textureManager;
			SamplerManager* m_samplerManager;
			FontManager* m_fontManager;
			TextManager* m_textManager;
		};
	}
}

#endif
