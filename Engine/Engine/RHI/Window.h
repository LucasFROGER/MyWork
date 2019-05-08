#ifndef _RHI_WINDOW_H_
#define _RHI_WINDOW_H_

#include "Device.h"
#include "Resources/FontInfo.h"
#include "Resources/Text.h"
#include <list>

namespace engine
{
	namespace rhi
	{
		class Window
		{
		public:
			Window(Device* device, HINSTANCE hInstance, int ShowWnd, int width, int height, LPCTSTR winName, LPCTSTR winTitle, bool fullscreen, unsigned int id);
			~Window();

			bool Update();
			void AddFont(engine::rhi::resources::FontInfo* font);

			HWND GetHWND() const;
			LPCTSTR GetName() const;
			LPCTSTR GetTitle() const;
			int GetWidth() const;
			int GetHeight() const;
			int GetFrameIndex() const;
			bool GetFullScreen() const;
			bool GetRunning() const;
			unsigned int GetId() const;
			ID3D12CommandQueue* GetCommandQueue() const;
			ID3D12GraphicsCommandList* GetCommandList() const;
			ID3D12CommandAllocator** GetCommandAllocator() const;
			ID3D12Fence** GetFence() const;
			HANDLE GetFenceEvent() const;
			UINT64* GetFenceValue() const;
			const IDXGISwapChain3* GetSwapChain() const;
			std::list<resources::RenderObject*>& GetRenderedObjectsTab();
			std::list<resources::Text*>& GetRenderedText();
			std::vector<resources::FontInfo*>& GetFonts();

			void SetResolution(unsigned int newWidth, unsigned int newHeight);
			void SetClearColor(float R, float G, float B, float A);
			void SetViewPort(float topLeftX, float topLeftY, unsigned int width, unsigned int height, float minDepth, float maxDepth);
			void SetScissorRectangle(float topLeftX, float topLeftY, unsigned int width, unsigned int height);

			void WaitForPreviousFrame(bool isCleaningUp);
		private:
			Device* m_device;

			// Handle to the window
			HWND m_hwnd;
			LPCTSTR m_name;
			LPCTSTR m_title;
			int m_width;
			int m_height;
			bool m_fullScreen;
			bool m_running;
			unsigned int m_id;
			float m_clearColor[4];

			ID3D12CommandQueue* m_commandQueue;
			IDXGISwapChain3* m_swapChain;
			int m_frameIndex;
			ID3D12DescriptorHeap* m_rtvDescriptorHeap;
			ID3D12Resource** m_renderTargets;
			ID3D12CommandAllocator** m_commandAllocator;
			ID3D12GraphicsCommandList* m_commandList;
			ID3D12Fence** m_fence;
			HANDLE m_fenceEvent;
			UINT64* m_fenceValue;
			int m_rtvDescriptorSize;
			D3D12_VIEWPORT m_viewport;
			D3D12_RECT m_scissorRect;
			ID3D12Resource* m_depthStencilBuffer;
			ID3D12DescriptorHeap* m_dsDescriptorHeap;

			std::list<resources::RenderObject*> m_renderedObject;
			std::list<resources::Text*> m_renderedText;
			std::vector<resources::FontInfo*> m_fonts;

			bool InitializeWindow(Device* device, HINSTANCE hInstance, int ShowWnd, bool fullscreen);
			void UpdatePipeline();
			void Render();
			void CleanUp();

			void RenderRenderObject();
			void RenderText();
			void ClearRenderer();

			static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			LRESULT CALLBACK WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

		};
	}
}
#endif