#ifndef _DIRECTXWRAPPER_H_
#define _DIRECTXWRAPPER_H_

#include "Window.h"
#include "DrawingTags.h"

namespace engine
{
	namespace rhi
	{
		class RHI
		{
		public:
			RHI(HINSTANCE hInstance, int ShowWnd, const int m_frameBufferSize);
			~RHI();

			bool Render();
			int GenWindow(int width, int height, const char* winName, const char* winTitle, bool fullscreen);
			void DeleteWindow(int id);
			int GenShader(const char* path, resources::EShaderEnum type);
			int GenRenderObject(int* shaderTab, int shaderTabSize, int* cbID, int cbNb, int* textures, int textureNb, int* staticSamplers, int staticSamplerNb,
				EDrawingType drawingType, float* vertexBuffer, int strideInBytes, int vBufferSize,
				int* iList, int ibufferSize, bool isStatic);
			int GenStaticSampler(D3D12_FILTER filters, int registerNb, int MaxAnisotropy, float minLOD, float maxLOD);
			int GenTexture(const char* path);
			int GenFont(const char* path);
			int GenText(const char* text, int* shaderIDTab, int shaderTabSize, int* cbId, int cbNb, int* staticSamplers, int ssNb, int font,
				engine::core::maths::Vec2 pos, engine::core::maths::Vec2 scale, engine::core::maths::Vec2 padding, engine::core::maths::Vec4 color);

			template<typename T>
			int GenConstantBuffer(T* dataPtr, int dataSize, int registerNb, resources::EShaderEnum shaderVisibility = resources::EShaderEnum::COUNT)
			{
				return m_device->GetResourcesManager()->GetConstantBufferManager()->AddConstantBuffer(dataPtr, dataSize, registerNb, m_frameBufferSize, shaderVisibility);
			}

			template<typename T>
			void UpdateConstantBuffer(int cbID, T* dataPtr, int dataSize)
			{
				for (size_t i{ 0 }; i < m_windows.size(); ++i)
				{
					if (m_windows[i])
					{
						m_device->GetResourcesManager()->GetConstantBufferManager()->GetConstantBufferByIndex(cbID)->Update(
							dataPtr, dataSize, m_windows[i]->GetFrameIndex());
						return;
					}
				}
			}

			Device* GetDevice() const;
			std::vector<Window*> GetWindows() const;
			Window* GetWindowById(unsigned int Id) const;
			Window* GetCurrentWindow() const;
			const int GetFrameBufferSize() const;

			void SetResolution(unsigned int newWidth, unsigned int newHeight, int windowId);
			void SetClearColor(float R, float G, float B, float A, int windowId);
			void SetViewPort(float topLeftX, float topLeftY, unsigned int width, unsigned int height, float minDepth, float maxDepth, int windowId);
			void SetScissorRectangle(float topLeftX, float topLeftY, unsigned int width, unsigned int height, int windowId);
			void SetActive(int renderObject, bool active, int windowId, bool isText = false);
			void SetText(const char* newText, int textId);
			void SetPos(engine::core::maths::Vec2 newPos, int textId);
			void SetShadersConstantBuffersTexturesSamplers(int renderObjectId, int* shadersId, int shadersNb, int* cb, int cbNb,
															int* textures, int textureNb, int* staticSamplers, int staticSamplerNb);

		private:

			HINSTANCE m_hInstance;
			int m_showWnd;
			Device* m_device;
			std::vector<Window*> m_windows;
			const int m_frameBufferSize;
			Window* m_activeWindow;

			void DeleteWindow(HWND window);
			engine::rhi::resources::FontInfo LoadFontInfo(std::wstring filename, int windowWidth, int windowHeight);
			void RegenFont(Window* temp);
		};
	}
}

#endif
