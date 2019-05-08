#include "../../stdafx.h"
#include "Window.h"
#include "../Resource/Vertex.h"

LRESULT CALLBACK engine::rhi::Window::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* pParent = nullptr;

	// Get pointer to window
	if (msg == WM_CREATE)
	{
		pParent = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pParent);
	}
	else
	{
		pParent = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (!pParent) return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	pParent->m_hwnd = hwnd;
	return pParent->WndProc(msg, wParam, lParam);
}

LRESULT CALLBACK engine::rhi::Window::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		m_running = false;
		return 0;
	}

	}
	return DefWindowProc(m_hwnd, msg, wParam, lParam);
}

engine::rhi::Window::Window(Device* device, HINSTANCE hInstance, int ShowWnd, int width, int height, LPCTSTR winName, LPCTSTR winTitle, bool fullscreen, unsigned int id) :
	m_device{ device },
	m_running{ true },
	m_width{ width },
	m_height{ height },
	m_name{ winName },
	m_title{ winTitle },
	m_fullScreen{ fullscreen },
	m_id{ id },
	m_clearColor{ 0.0f, 0.2f, 0.4f, 1.0f }
{
	m_renderTargets = new ID3D12Resource*[device->GetFrameBufferSize()]();
	m_commandAllocator = new ID3D12CommandAllocator*[device->GetFrameBufferSize()]();
	m_fence = new ID3D12Fence*[device->GetFrameBufferSize()]();
	m_fenceValue = new UINT64[device->GetFrameBufferSize()]();

	if (!InitializeWindow(device, hInstance, ShowWnd, m_fullScreen))
	{
		MessageBox(0, L"Window Initialization - Failed", L"Error", MB_OK);
	}

	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.Width = (FLOAT)m_width;
	m_viewport.Height = (FLOAT)m_height;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	m_scissorRect.left = 0;
	m_scissorRect.top = 0;
	m_scissorRect.right = m_width;
	m_scissorRect.bottom = m_height;
}

engine::rhi::Window::~Window()
{
	CleanUp();
}

bool engine::rhi::Window::InitializeWindow(Device* device, HINSTANCE hInstance, int ShowWnd, bool fullscreen)
{
	HRESULT hr;

	if (fullscreen)
	{
		HMONITOR hmon = MonitorFromWindow(m_hwnd,
			MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
		GetMonitorInfo(hmon, &mi);

		m_width = mi.rcMonitor.right - mi.rcMonitor.left;
		m_height = mi.rcMonitor.bottom - mi.rcMonitor.top;
	}

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticWndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	m_hwnd = CreateWindowEx(NULL,
		m_name,
		m_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_width, m_height,
		NULL,
		NULL,
		hInstance,
		this);

	if (!m_hwnd)
	{
		MessageBox(NULL, L"Error creating window", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (fullscreen)
	{
		SetWindowLong(m_hwnd, GWL_STYLE, 0);
	}

	ShowWindow(m_hwnd, ShowWnd);
	UpdateWindow(m_hwnd);

	D3D12_COMMAND_QUEUE_DESC cqDesc = {};
	cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = device->GetDevice()->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&m_commandQueue));
	if (FAILED(hr))
	{
		return false;
	}

	DXGI_MODE_DESC backBufferDesc = {};
	backBufferDesc.Width = m_width;
	backBufferDesc.Height = m_height;
	backBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	DXGI_SAMPLE_DESC sampleDesc = {};
	sampleDesc.Count = 1;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = device->GetFrameBufferSize();
	swapChainDesc.BufferDesc = backBufferDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = m_hwnd;
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.Windowed = !m_fullScreen;

	IDXGISwapChain* tempSwapChain;

	device->GetFactory()->CreateSwapChain(m_commandQueue, &swapChainDesc, &tempSwapChain);

	m_swapChain = static_cast<IDXGISwapChain3*>(tempSwapChain);

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	m_rtvDescriptorSize = device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = device->GetFrameBufferSize();
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = device->GetDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvDescriptorHeap));
	if (FAILED(hr))
	{
		return false;
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	for (int i = 0; i < device->GetFrameBufferSize(); i++)
	{
		hr = m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]));
		if (FAILED(hr))
		{
			return false;
		}

		device->GetDevice()->CreateRenderTargetView(m_renderTargets[i], nullptr, rtvHandle);

		rtvHandle.Offset(1, m_rtvDescriptorSize);
	}

	for (int i = 0; i < device->GetFrameBufferSize(); i++)
	{
		hr = device->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator[i]));
		if (FAILED(hr))
		{
			return false;
		}
	}

	hr = device->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator[m_frameIndex], NULL, IID_PPV_ARGS(&m_commandList));
	if (FAILED(hr))
	{
		return false;
	}
	m_commandList->Close();

	for (int i = 0; i < device->GetFrameBufferSize(); i++)
	{
		hr = device->GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence[i]));
		if (FAILED(hr))
		{
			MessageBox(NULL, L"Fence creation failed", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		m_fenceValue[i] = 0;
	}

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (m_fenceEvent == nullptr)
	{
		return false;
	}

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = device->GetDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsDescriptorHeap));
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Create dsvDescriptorHeap failed", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
	depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

	D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
	depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
	depthOptimizedClearValue.DepthStencil.Stencil = 0;

	device->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, m_width, m_height, 1, 1, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthOptimizedClearValue,
		IID_PPV_ARGS(&m_depthStencilBuffer)
	);

	hr = device->GetDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsDescriptorHeap));
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Create depthDescriptorHeap failed", L"Error", MB_OK | MB_ICONERROR);
		m_running = false;
	}

	m_dsDescriptorHeap->SetName(L"Depth/Stencil Resource Heap");
	device->GetDevice()->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilDesc, m_dsDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	return true;
}

bool engine::rhi::Window::Update()
{

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			MessageBox(NULL, L"WM_QUIT", L"Error", MB_OK | MB_ICONERROR);
			m_running = false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	else
	{
		Render();
	}
	return m_running;
}

void engine::rhi::Window::AddFont(engine::rhi::resources::FontInfo * font)
{
	m_fonts.push_back(font);
}

void engine::rhi::Window::UpdatePipeline()
{
	HRESULT hr;

	WaitForPreviousFrame(false);

	ClearRenderer();
	RenderRenderObject();
	RenderText();

	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	hr = m_commandList->Close();
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Couldn't close command list", L"Error", MB_OK | MB_ICONERROR);
	}
}

void engine::rhi::Window::Render()
{
	HRESULT hr;

	UpdatePipeline();

	ID3D12CommandList* ppCommandLists[] = { m_commandList };

	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	hr = m_commandQueue->Signal(m_fence[m_frameIndex], m_fenceValue[m_frameIndex]);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CommandQueue->Signal() failed", L"Error", MB_OK | MB_ICONERROR);
	}

	hr = m_swapChain->Present(0, 0);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"SwapChain->Present() failed", L"Error", MB_OK | MB_ICONERROR);
	}
}

void engine::rhi::Window::WaitForPreviousFrame(bool isCleaningUp)
{
	HRESULT hr;

	if (!isCleaningUp)
		m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	if (m_fence[m_frameIndex]->GetCompletedValue() < m_fenceValue[m_frameIndex])
	{
		hr = m_fence[m_frameIndex]->SetEventOnCompletion(m_fenceValue[m_frameIndex], m_fenceEvent);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"Error cleaning window (fence)", L"Error", MB_OK | MB_ICONERROR);
		}

		WaitForSingleObject(m_fenceEvent, 1000);
	}

	m_fenceValue[m_frameIndex]++;
}

void engine::rhi::Window::CleanUp()
{
	for (int i = 0; i < m_device->GetFrameBufferSize(); ++i)
	{
		m_frameIndex = i;
		WaitForPreviousFrame(true);
	}

	BOOL fs = false;
	if (m_swapChain->GetFullscreenState(&fs, NULL))
		m_swapChain->SetFullscreenState(false, NULL);

	SAFE_RELEASE(m_swapChain);
	SAFE_RELEASE(m_commandQueue);
	SAFE_RELEASE(m_rtvDescriptorHeap);
	SAFE_RELEASE(m_commandList);

	for (int i = 0; i < m_device->GetFrameBufferSize(); ++i)
	{
		SAFE_RELEASE(m_renderTargets[i]);
		SAFE_RELEASE(m_commandAllocator[i]);
		SAFE_RELEASE(m_fence[i]);
	};
	SAFE_DELETE_ARRAY(m_renderTargets);
	SAFE_DELETE_ARRAY(m_commandAllocator);
	SAFE_DELETE_ARRAY(m_fence);
	SAFE_DELETE_ARRAY(m_fenceValue);
	SAFE_RELEASE(m_dsDescriptorHeap);
	SAFE_RELEASE(m_depthStencilBuffer);
	if (m_renderedObject.empty())
	{
		for (auto&& child : m_renderedObject)
		{
			delete child;
		}
		m_renderedObject.clear();
	}
	m_fonts.clear();
}

void engine::rhi::Window::RenderRenderObject()
{
	if (!m_renderedObject.empty())
	{
		m_commandList->ClearDepthStencilView(m_dsDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		resources::PSO* oldPSO = m_renderedObject.begin()._Ptr->_Myval->GetPso();
		resources::RootSignature* oldRS = m_renderedObject.begin()._Ptr->_Myval->GetPso()->GetRootSignature();
		m_commandList->SetPipelineState(oldPSO->GetPso());
		m_commandList->SetGraphicsRootSignature(oldRS->GetRootSignature());
		for (std::list<resources::RenderObject*>::const_iterator it = m_renderedObject.begin(); it != m_renderedObject.end(); ++it)
		{
			if ((*it)->GetPso() != oldPSO)
				m_commandList->SetPipelineState((*it)->GetPso()->GetPso());
			if ((*it)->GetPso()->GetRootSignature() != oldRS)
				m_commandList->SetGraphicsRootSignature((*it)->GetPso()->GetRootSignature()->GetRootSignature());

			ID3D12DescriptorHeap* descriptorHeaps[] = { (*it)->GetMainDescriptorHeap() };

			if ((*it)->GetTextures().size() > 0 && (*it)->GetMainDescriptorHeap())
			{
				m_commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
				m_commandList->SetGraphicsRootDescriptorTable(0, (*it)->GetMainDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
				for (int i{ 0 }; i < (*it)->GetConstantBuffer().size(); ++i)
				{
					m_commandList->SetGraphicsRootConstantBufferView(i + 1, (*it)->GetConstantBuffer()[i]->GetCbUploadHeap()[m_frameIndex]->GetGPUVirtualAddress());
				}
			}
			else
			{
				for (int i{ 0 }; i < (*it)->GetConstantBuffer().size(); ++i)
				{
					m_commandList->SetGraphicsRootConstantBufferView(i, (*it)->GetConstantBuffer()[i]->GetCbUploadHeap()[m_frameIndex]->GetGPUVirtualAddress());
				}
			}

			m_commandList->RSSetViewports(1, &m_viewport);
			m_commandList->RSSetScissorRects(1, &m_scissorRect);
			if ((*it)->GetPso()->GetDrawingType() == EDrawingType::DTRIANGLES)
				m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			if ((*it)->GetPso()->GetDrawingType() == EDrawingType::DLINE)
				m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

			if ((*it)->GetPso()->GetDrawingType() == EDrawingType::DPOINT)
				m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

			m_commandList->IASetVertexBuffers(0, 1, &(*it)->GetVertexBufferView());
			if ((*it)->GetIndexBufferSize() > 0)
			{
				m_commandList->IASetIndexBuffer(&(*it)->GetIndexBufferView());
				m_commandList->DrawIndexedInstanced((*it)->GetIndexBufferSize(), 1, 0, 0, 0);
			}
			else
				m_commandList->DrawInstanced((*it)->GetVBufferSize(), 1, 0, 0);

			oldPSO = (*it)->GetPso();
			oldRS = (*it)->GetRootSignature();
		}
	}
}

void engine::rhi::Window::RenderText()
{
	if (!m_renderedText.empty())
	{
		m_commandList->ClearDepthStencilView(m_dsDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		resources::PSO* oldPSO = m_renderedText.begin()._Ptr->_Myval->GetPso();
		resources::RootSignature* oldRS = m_renderedText.begin()._Ptr->_Myval->GetPso()->GetRootSignature();
		m_commandList->SetPipelineState(oldPSO->GetPso());
		m_commandList->SetGraphicsRootSignature(oldRS->GetRootSignature());
		for (std::list<resources::Text*>::const_iterator it = m_renderedText.begin(); it != m_renderedText.end(); ++it)
		{
			if ((*it)->GetPso() != oldPSO)
				m_commandList->SetPipelineState((*it)->GetPso()->GetPso());
			if((*it)->GetPso()->GetRootSignature() != oldRS)
				m_commandList->SetGraphicsRootSignature((*it)->GetPso()->GetRootSignature()->GetRootSignature());

			ID3D12DescriptorHeap* descriptorHeaps[] = { (*it)->GetMainDescriptorHeap() };
			m_commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
			m_commandList->SetGraphicsRootDescriptorTable(0, (*it)->GetMainDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

			for (int i{ 0 }; i < (*it)->GetConstantBuffers().size(); ++i)
			{
				m_commandList->SetGraphicsRootConstantBufferView(i + 1, (*it)->GetConstantBuffers()[i]->GetCbUploadHeap()[m_frameIndex]->GetGPUVirtualAddress());
			}

			int numCharacters = 0;

			float topLeftScreenX = ((*it)->GetPos().m_x * 2.0f) - 1.0f;
			float topLeftScreenY = ((1.0f - (*it)->GetPos().m_y) * 2.0f) - 1.0f;

			float x = topLeftScreenX;
			float y = topLeftScreenY;

			float horrizontalPadding = (((*it)->GetFont()->m_leftpadding + (*it)->GetFont()->m_rightpadding) * (*it)->GetPadding().m_x);
			float verticalPadding = ((*it)->GetFont()->m_toppadding + (*it)->GetFont()->m_bottompadding) * (*it)->GetPadding().m_y;

			// cast the gpu virtual address to a textvertex, so we can directly store our vertices there 
			resource::TextVertex* vert = (resource::TextVertex*)(*it)->GetVGPUAddress()[m_frameIndex];

			wchar_t lastChar = -1; // no last character to start with 

			for (int i = 0; i < (*(*it)->GetText()).size(); ++i)
			{
				wchar_t c = (*(*it)->GetText())[i];


				resources::FontChar* fc = (*it)->GetFont()->GetChar(c);

				// character not in font char set 
				if (fc == nullptr)
					continue;

				// end of string 
				if (c == L'\0')
					break;

				// new line 
				if (c == L'\n')
				{
					x = topLeftScreenX;
					y -= ((*it)->GetFont()->m_lineHeight + verticalPadding) * (*it)->GetScale().m_y;
					continue;
				}

				// don't overflow the buffer. In your app if this is true, you can implement a resize of your text vertex buffer 
				if (numCharacters >= (*it)->GetMaxCharacters())
					break;

				float kerning = 0.0f;
				if (i > 0)
					kerning = (*it)->GetFont()->GetKerning(lastChar, c);

				vert[numCharacters] = resource::TextVertex((*it)->GetColor().m_x,
					(*it)->GetColor().m_y,
					(*it)->GetColor().m_z,
					(*it)->GetColor().m_w,
					fc->u,
					fc->v,
					fc->twidth,
					fc->theight,
					x + ((fc->xoffset + kerning) * (*it)->GetScale().m_x),
					y - (fc->yoffset * (*it)->GetScale().m_y),
					fc->width * (*it)->GetScale().m_x,
					fc->height * (*it)->GetScale().m_y);

				numCharacters++;

				// remove horrizontal padding and advance to next char position 
				x += (fc->xadvance - horrizontalPadding) * (*it)->GetScale().m_x;

				lastChar = c;
			}

			m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			m_commandList->IASetVertexBuffers(0, 1, &(*it)->GetVertexBufferView()[m_frameIndex]);
			// we are going to have 4 vertices per character (trianglestrip to make quad), and each instance is one character 
			m_commandList->DrawInstanced(4, numCharacters, 0, 0);
			
			oldPSO = (*it)->GetPso();
			oldRS = (*it)->GetPso()->GetRootSignature();
		}
	}
}

void engine::rhi::Window::ClearRenderer()
{
	HRESULT hr;
	hr = m_commandAllocator[m_frameIndex]->Reset();
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error reset command allocator", L"Error", MB_OK | MB_ICONERROR);
	}

	hr = m_commandList->Reset(m_commandAllocator[m_frameIndex], nullptr);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Error reset commandList", L"Error", MB_OK | MB_ICONERROR);
	}


	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

	m_commandList->ClearRenderTargetView(rtvHandle, m_clearColor, 0, nullptr);
	m_commandList->ClearDepthStencilView(m_dsDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}

HWND engine::rhi::Window::GetHWND() const
{
	return m_hwnd;
}

LPCTSTR engine::rhi::Window::GetName() const
{
	return m_name;
}

LPCTSTR engine::rhi::Window::GetTitle() const
{
	return m_title;
}

int engine::rhi::Window::GetWidth() const
{
	return m_width;
}

int engine::rhi::Window::GetHeight() const
{
	return m_height;
}

int engine::rhi::Window::GetFrameIndex() const
{
	return m_frameIndex;
}

bool engine::rhi::Window::GetFullScreen() const
{
	return m_fullScreen;
}

bool engine::rhi::Window::GetRunning() const
{
	return m_running;
}

unsigned int engine::rhi::Window::GetId() const
{
	return m_id;
}

ID3D12CommandQueue* engine::rhi::Window::GetCommandQueue() const
{
	return m_commandQueue;
}

ID3D12GraphicsCommandList* engine::rhi::Window::GetCommandList() const
{
	return m_commandList;
}

ID3D12CommandAllocator ** engine::rhi::Window::GetCommandAllocator() const
{
	return m_commandAllocator;
}

ID3D12Fence** engine::rhi::Window::GetFence() const
{
	return m_fence;
}

HANDLE engine::rhi::Window::GetFenceEvent() const
{
	return m_fenceEvent;
}

UINT64* engine::rhi::Window::GetFenceValue() const
{
	return m_fenceValue;
}

const IDXGISwapChain3* engine::rhi::Window::GetSwapChain() const
{
	return m_swapChain;
}

std::list<engine::rhi::resources::RenderObject*>& engine::rhi::Window::GetRenderedObjectsTab()
{
	return m_renderedObject;
}

std::list<engine::rhi::resources::Text*>& engine::rhi::Window::GetRenderedText()
{
	return m_renderedText;
}

std::vector<engine::rhi::resources::FontInfo*>& engine::rhi::Window::GetFonts()
{
	return m_fonts;
}

void engine::rhi::Window::SetResolution(unsigned int newWidth, unsigned int newHeight)
{
	if (newHeight != m_height || newWidth != m_width)
	{
		m_width = newWidth;
		m_height = newHeight;

		std::vector<std::string> path;

		HRESULT hr;

		// Flush all current GPU commands.
		WaitForPreviousFrame(false);

		// Release the resources holding references to the swap chain (requirement of
		// IDXGISwapChain::ResizeBuffers) and reset the frame fence values to the
		// current fence value.
		for (UINT i{ 0 }; i < m_device->GetFrameBufferSize(); ++i)
		{
			SAFE_RELEASE(m_renderTargets[i]);
			m_fenceValue[i] = m_fenceValue[m_frameIndex];
		}
		SAFE_RELEASE(m_depthStencilBuffer);
		// Resize the swap chain to the desired dimensions.
		DXGI_SWAP_CHAIN_DESC desc = {};
		m_swapChain->GetDesc(&desc);
		hr = m_swapChain->ResizeBuffers(m_device->GetFrameBufferSize(), m_width, m_height, desc.BufferDesc.Format, desc.Flags);
		if (FAILED(hr))
			MessageBox(NULL, L"Error ResizeBuffers", L"Error", MB_OK | MB_ICONERROR);

		BOOL fullscreenState;
		hr = m_swapChain->GetFullscreenState(&fullscreenState, nullptr);
		if (FAILED(hr))
			MessageBox(NULL, L"Error GetFullScreenState", L"Error", MB_OK | MB_ICONERROR);

		m_fullScreen = !fullscreenState;

		// Reset the frame index to the current back buffer index.
		m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

		for (int i = 0; i < m_device->GetFrameBufferSize(); i++)
		{
			hr = m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargets[i]));
			if (FAILED(hr))
			{
				MessageBox(NULL, L"Error swapChain->GetBuffer()", L"Error", MB_OK | MB_ICONERROR);
			}

			m_device->GetDevice()->CreateRenderTargetView(m_renderTargets[i], nullptr, rtvHandle);

			rtvHandle.Offset(1, m_rtvDescriptorSize);
		}
		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

		D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
		depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
		depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
		depthOptimizedClearValue.DepthStencil.Stencil = 0;

		m_device->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, m_width, m_height, 1, 1, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthOptimizedClearValue,
			IID_PPV_ARGS(&m_depthStencilBuffer)
		);
		m_device->GetDevice()->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilDesc, m_dsDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	}
}

void engine::rhi::Window::SetClearColor(float R, float G, float B, float A)
{
	float newClearColor[4]{ R, G, B, A };
	for (unsigned int i{ 0 }; i < 4; ++i)
		m_clearColor[i] = newClearColor[i];
}

void engine::rhi::Window::SetViewPort(float topLeftX, float topLeftY, unsigned int width, unsigned int height, float minDepth, float maxDepth)
{
	m_viewport.TopLeftX = (FLOAT)topLeftX;
	m_viewport.TopLeftY = (FLOAT)topLeftY;
	m_viewport.Width = (FLOAT)width;
	m_viewport.Height = (FLOAT)height;
	m_viewport.MinDepth = (FLOAT)minDepth;
	m_viewport.MaxDepth = (FLOAT)maxDepth;
}
void engine::rhi::Window::SetScissorRectangle(float topLeftX, float topLeftY, unsigned int width, unsigned int height)
{
	m_scissorRect.left = (LONG)topLeftX;
	m_scissorRect.top = (LONG)topLeftY;
	m_scissorRect.right = (LONG)width;
	m_scissorRect.bottom = (LONG)height;
}
