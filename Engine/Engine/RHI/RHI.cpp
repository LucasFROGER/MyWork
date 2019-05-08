#include "../../stdafx.h"
#include "RHI.h"
#include <fstream>

engine::rhi::RHI::RHI(HINSTANCE hInstance, int ShowWnd, const int frameBufferSize) :
	m_hInstance{ hInstance },
	m_showWnd{ ShowWnd },
	m_frameBufferSize{ frameBufferSize },
	m_device{ new Device(frameBufferSize) },
	m_activeWindow{ nullptr }
{}

engine::rhi::RHI::~RHI()
{
	SAFE_DELETE(m_device);
	SAFE_DELETE_VECTOR(m_windows);
}

bool engine::rhi::RHI::Render()
{
	bool _continue = false;
	Window* activeWindow = nullptr;

	for (unsigned int i = 0; i < m_windows.size(); ++i)
	{
		if (m_windows[i] != nullptr)
		{
			if (!m_windows[i]->Update())
				DeleteWindow(i);
			else
			{
				if (GetActiveWindow() == m_windows[i]->GetHWND())
					activeWindow = m_windows[i];

				_continue = true;
			}
		}
	}
	m_activeWindow = activeWindow;
	return _continue;
}

int engine::rhi::RHI::GenWindow(int width, int height, const char* winName, const char* winTitle, bool fullscreen)
{
	if (winName && winTitle)
	{
		std::vector<wchar_t> vec;
		size_t len = strlen(winName);
		vec.resize(len + 1);
		mbstowcs(&vec[0], winName, len);
		const wchar_t* wWinName = &vec[0];

		std::vector<wchar_t> vec2;
		size_t len2 = strlen(winTitle);
		vec2.resize(len2 + 1);
		mbstowcs(&vec2[0], winTitle, len2);
		const wchar_t* wWinTitle = &vec2[0];

		for (size_t i{ 0 }; i < m_windows.size(); ++i)
		{
			if (m_windows[i] == nullptr)
			{
				m_windows[i] = new Window(m_device, m_hInstance, m_showWnd, width, height, wWinName, wWinTitle, fullscreen, i);
				return i;
			}
		}
		m_windows.push_back(new Window(m_device, m_hInstance, m_showWnd, width, height, wWinName, wWinTitle, fullscreen, (unsigned int)m_windows.size()));
		return (int)(m_windows.size() - 1);
	}
	else
		MessageBox(NULL, L"Window name or Title nullptr", L"Error", MB_OK | MB_ICONERROR);

	return -999;
}

void engine::rhi::RHI::DeleteWindow(int id)
{
	if (id >= -1 && id < m_windows.size())
	{
		if (m_windows[id])
		{
			DestroyWindow(m_windows[id]->GetHWND());
			SAFE_DELETE(m_windows[id]);
		}
	}
}

void engine::rhi::RHI::DeleteWindow(HWND window)
{
	for (int i{ 0 }; i < m_windows.size(); ++i)
	{
		if (m_windows[i]->GetHWND() == window)
		{
			DestroyWindow(m_windows[i]->GetHWND());
			SAFE_DELETE(m_windows[i]);
		}
	}
}

int engine::rhi::RHI::GenShader(const char* path, resources::EShaderEnum type)
{
	if (path)
	{
		std::vector<wchar_t> vec;
		size_t len = strlen(path);
		vec.resize(len + 1);
		mbstowcs(&vec[0], path, len);
		const wchar_t* wPath = &vec[0];

		return m_device->GetResourcesManager()->GetShaderManager()->FindShader(wPath, type)->GetId();
	}
	else
		MessageBox(NULL, L"Window name or Title nullptr", L"Error", MB_OK | MB_ICONERROR);

	return -999;
}

int engine::rhi::RHI::GenTexture(const char* path)
{
	if (path)
	{
		std::vector<wchar_t> vec;
		size_t len = strlen(path);
		vec.resize(len + 1);
		mbstowcs(&vec[0], path, len);
		const wchar_t* wPath = &vec[0];

		return m_device->GetResourcesManager()->GetTextureManager()->FindTexture(wPath)->GetId();
	}
	else
		MessageBox(NULL, L"Window name or Title nullptr", L"Error", MB_OK | MB_ICONERROR);

	return -999;
}

int engine::rhi::RHI::GenFont(const char * path)
{
	if (path)
	{
		std::vector<wchar_t> vec;
		size_t len = strlen(path);
		vec.resize(len + 1);
		mbstowcs(&vec[0], path, len);
		const wchar_t* wPath = &vec[0];

		int id{ -1 };
		std::string texturePath = path;
		texturePath[texturePath.length() - 3] = 'p';
		texturePath[texturePath.length() - 2] = 'n';
		texturePath[texturePath.length() - 1] = 'g';

		for (unsigned int i{ 0 }; i < m_windows.size(); ++i)
		{
			resources::FontInfo info{ LoadFontInfo(wPath, m_windows[i]->GetWidth(), m_windows[i]->GetHeight()) };
			info.m_fontTexture = m_device->GetResourcesManager()->GetTextureManager()->GetTextureByIndex(GenTexture(texturePath.c_str()));

			resources::FontInfo* pInfo = m_device->GetResourcesManager()->GetFontManager()->FindFont(&info);

			id = pInfo->m_id;

			for (unsigned int j{ 0 }; j < m_windows[i]->GetFonts().size(); ++j)
			{
				if (id == m_windows[i]->GetFonts()[j]->m_id)
					return id;
			}
			m_windows[i]->AddFont(pInfo);
		}
		return id;
	}
}

int engine::rhi::RHI::GenText(const char* text, int* shaderIDTab, int shaderTabSize, int* cbID, int cbNb,
	int* staticSamplers, int staticSamplerNb, int fontId,
	engine::core::maths::Vec2 pos, engine::core::maths::Vec2 scale, engine::core::maths::Vec2 padding, engine::core::maths::Vec4 color)
{
	if (text)
	{
		std::vector<wchar_t> vec;
		size_t len = strlen(text);
		vec.resize(len + 1);
		mbstowcs(&vec[0], text, len);
		const wchar_t* wText = &vec[0];

		resources::PSO* pso;
		resources::RootSignature* rootSignature;
		std::vector<resources::ConstantBuffer*> cb;
		for (int i{ 0 }; i < cbNb; ++i)
			cb.push_back(m_device->GetResourcesManager()->GetConstantBufferManager()->GetConstantBufferByIndex(cbID[i]));

		D3D12_DESCRIPTOR_RANGE  descriptorTableRanges[1];
		D3D12_ROOT_DESCRIPTOR_TABLE descriptorTable;

		descriptorTableRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorTableRanges[0].NumDescriptors = 1;
		descriptorTableRanges[0].BaseShaderRegister = 0;
		descriptorTableRanges[0].RegisterSpace = 0;
		descriptorTableRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		descriptorTable.NumDescriptorRanges = _countof(descriptorTableRanges);
		descriptorTable.pDescriptorRanges = &descriptorTableRanges[0];

		engine::rhi::resources::FontInfo* font = m_device->GetResourcesManager()->GetFontManager()->GetFontByIndex(fontId);
		D3D12_ROOT_PARAMETER* param = nullptr;
		size_t paramNb = cb.size() + 1;
		param = new D3D12_ROOT_PARAMETER[paramNb];
		param[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		param[0].DescriptorTable = descriptorTable;
		param[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		for (int i{ 0 }; i < cb.size(); ++i)
			param[i + 1] = *cb[i]->GetRootParameters();

		D3D12_STATIC_SAMPLER_DESC* samplers = nullptr;
		if (staticSamplerNb > 0)
		{
			samplers = new D3D12_STATIC_SAMPLER_DESC[staticSamplerNb];
			for (int i{ 0 }; i < staticSamplerNb; ++i)
				samplers[i] = m_device->GetResourcesManager()->GetSamplerManager()->GetSamplerByIndex(staticSamplers[i]);
		}

		switch (shaderTabSize)
		{
		case 0:
		{
			rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
			(
				param, paramNb, samplers, staticSamplerNb, D3D12_ROOT_SIGNATURE_FLAG_NONE
			);
			break;
		}
		case 1:
		{
			rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
			(
				param, paramNb, samplers, staticSamplerNb,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS
			);
			break;
		}
		case 2:
		{
			rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
			(
				param, paramNb, samplers, staticSamplerNb,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS
			);
			break;
		}
		case 3:
		{
			rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
			(
				param, paramNb, samplers, staticSamplerNb,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
			);
			break;
		}
		case 4:
		{
			rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
			(
				param, paramNb, samplers, staticSamplerNb,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
				D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
			);
			break;
		}
		case 5:
		{
			rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
			(
				param, paramNb, samplers, staticSamplerNb,
				D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
			);
			break;
		}
		default:
		{
			MessageBox(0, L"How many shaders are you loading ? o.o", L"Error", MB_OK);

		}
		}
		std::vector<resources::Shader*> shaderTab;
		for (int i = 0; i < shaderTabSize; ++i)
			shaderTab.push_back(m_device->GetResourcesManager()->GetShaderManager()->GetShaderByIndex(shaderIDTab[i]));
		pso = m_device->GetResourcesManager()->GetPsoManager()->FindPso(rootSignature, EDrawingType::DTRIANGLES, shaderTab, shaderTabSize, true);


		return m_device->GetResourcesManager()->GetTextManager()->FindText(wText, font, pso, cb, pos, scale, padding, color)->GetId();
	}
}

int engine::rhi::RHI::GenRenderObject(int* shaderIDTab, int shaderTabSize, int* cbID, int cbNb, int* textures, int textureNb, int* staticSamplers, int staticSamplerNb,
	EDrawingType drawingType, float* vertexBuffer, int strideInBytes, int vBufferSize,
	int* iList, int ibufferSize, bool isStatic)
{
	resources::PSO* pso;
	resources::RootSignature* rootSignature;
	std::vector<resources::ConstantBuffer*> cb;
	std::vector<resources::Texture*>text;
	for (int i{ 0 }; i < cbNb; ++i)
		cb.push_back(m_device->GetResourcesManager()->GetConstantBufferManager()->GetConstantBufferByIndex(cbID[i]));
	for (int i{ 0 }; i < textureNb; ++i)
		text.push_back(m_device->GetResourcesManager()->GetTextureManager()->GetTextureByIndex(textures[i]));


	D3D12_DESCRIPTOR_RANGE  descriptorTableRanges[1];
	D3D12_ROOT_DESCRIPTOR_TABLE descriptorTable;

	descriptorTableRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorTableRanges[0].NumDescriptors = textureNb;
	descriptorTableRanges[0].BaseShaderRegister = 0;
	descriptorTableRanges[0].RegisterSpace = 0;
	descriptorTableRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	descriptorTable.NumDescriptorRanges = _countof(descriptorTableRanges);
	descriptorTable.pDescriptorRanges = &descriptorTableRanges[0];


	D3D12_ROOT_PARAMETER* param = nullptr;
	size_t paramNb = 0;
	if (textures > 0)
	{
		paramNb = cb.size() + 1;
		param = new D3D12_ROOT_PARAMETER[paramNb];
		param[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		param[0].DescriptorTable = descriptorTable;
		param[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		for (int i{ 0 }; i < cb.size(); ++i)
			param[i + 1] = *cb[i]->GetRootParameters();
	}
	else
	{
		paramNb = cb.size();
		param = new D3D12_ROOT_PARAMETER[paramNb];
		for (int i{ 0 }; i < cb.size(); ++i)
			param[i] = *cb[i]->GetRootParameters();
	}




	D3D12_STATIC_SAMPLER_DESC* samplers = nullptr;
	if (staticSamplerNb > 0)
	{
		samplers = new D3D12_STATIC_SAMPLER_DESC[staticSamplerNb];
		for (int i{ 0 }; i < staticSamplerNb; ++i)
			samplers[i] = m_device->GetResourcesManager()->GetSamplerManager()->GetSamplerByIndex(staticSamplers[i]);
	}
	switch (shaderTabSize)
	{
	case 0:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb, D3D12_ROOT_SIGNATURE_FLAG_NONE
		);
		break;
	}
	case 1:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 2:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 3:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 4:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 5:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
		);
		break;
	}
	default:
	{
		MessageBox(0, L"How many shaders are you loading ? o.o", L"Error", MB_OK);

	}
	}
	std::vector<resources::Shader*> shaderTab;
	for (int i = 0; i < shaderTabSize; ++i)
		shaderTab.push_back(m_device->GetResourcesManager()->GetShaderManager()->GetShaderByIndex(shaderIDTab[i]));
	pso = m_device->GetResourcesManager()->GetPsoManager()->FindPso(rootSignature, drawingType, shaderTab, shaderTabSize, false);
	return m_device->GetResourcesManager()->GetRenderObjectManager()->FindRenderObject
	(
		pso, rootSignature, cb, text, samplers, staticSamplerNb,
		vertexBuffer, strideInBytes, vBufferSize,
		iList, ibufferSize, isStatic
	)->GetId();

}

int engine::rhi::RHI::GenStaticSampler(D3D12_FILTER filters, int registerNb, int MaxAnisotropy, float minLOD, float maxLOD)
{
	return m_device->GetResourcesManager()->GetSamplerManager()->FindSampler(filters, registerNb, MaxAnisotropy, minLOD, maxLOD);
}

engine::rhi::Device* engine::rhi::RHI::GetDevice()const
{
	return m_device;
}

std::vector<engine::rhi::Window*> engine::rhi::RHI::GetWindows() const
{
	return m_windows;
}

engine::rhi::Window* engine::rhi::RHI::GetWindowById(unsigned int id) const
{
	for (int i{ 0 }; i < m_windows.size(); ++i)
	{
		if (m_windows[i])
			if (m_windows[i]->GetId() == id)
				return m_windows[i];
	}
	return nullptr;
}

engine::rhi::Window* engine::rhi::RHI::GetCurrentWindow() const
{
	return m_activeWindow;
}


const int engine::rhi::RHI::GetFrameBufferSize() const
{
	return m_frameBufferSize;
}

void engine::rhi::RHI::SetResolution(unsigned int newWidth, unsigned int newHeight, int windowId)
{
	Window* temp = GetWindowById(windowId);
	if (temp)
	{
		temp->SetResolution(newWidth, newHeight);

		unsigned int textNb{ m_device->GetResourcesManager()->GetTextManager()->GetTextNb() };
		std::vector<int> idSave;
		idSave.resize(textNb);
		for (unsigned int i{ 0 }; i < textNb; ++i)
			idSave[i] = m_device->GetResourcesManager()->GetTextManager()->GetTextByIndex(i)->GetFont()->m_id;

		RegenFont(temp);

		for (unsigned int i{ 0 }; i < textNb; ++i)
			m_device->GetResourcesManager()->GetTextManager()->GetTextByIndex(i)->SetFont(m_device->GetResourcesManager()->GetFontManager()->GetFontByIndex(idSave[i]));

	}
}

void engine::rhi::RHI::SetClearColor(float R, float G, float B, float A, int windowId)
{
	Window* temp = GetWindowById(windowId);
	if (temp)
		temp->SetClearColor(R, G, B, A);
}

void engine::rhi::RHI::SetViewPort(float topLeftX, float topLeftY, unsigned int width, unsigned int height, float minDepth, float maxDepth, int windowId)
{
	Window* temp = GetWindowById(windowId);
	if (temp)
		temp->SetViewPort(topLeftX, topLeftY, width, height, minDepth, maxDepth);
}

void engine::rhi::RHI::SetScissorRectangle(float topLeftX, float topLeftY, unsigned int width, unsigned int height, int windowId)
{
	Window* temp = GetWindowById(windowId);
	if (temp)
		temp->SetScissorRectangle(topLeftX, topLeftY, width, height);
}

void engine::rhi::RHI::SetActive(int renderObject, bool active, int windowId, bool isText)
{
	Window* temp = GetWindowById(windowId);
	HRESULT hr;
	if (!isText)
	{
		if (temp)
		{
			resources::RenderObject* object = m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObject);

			if (object)
			{
				if (!active)
				{
					for (std::list<resources::RenderObject*>::const_iterator it{ temp->GetRenderedObjectsTab().begin() }, end{ temp->GetRenderedObjectsTab().end() }; it != end; std::advance(it, 1))
						if ((*it)->GetId() == renderObject)
						{
							temp->GetRenderedObjectsTab().erase(it);
							return;
						}
				}
				if (active)
				{
					for (std::list<resources::RenderObject*>::const_iterator it{ temp->GetRenderedObjectsTab().begin() }, end{ temp->GetRenderedObjectsTab().end() }; it != end; std::advance(it, 1))
						if ((*it)->GetId() == renderObject)
							return;

					temp->WaitForPreviousFrame(false);
					hr = temp->GetCommandAllocator()[temp->GetFrameIndex()]->Reset();
					if (FAILED(hr))
					{
						MessageBox(NULL, L"Error reset command allocator", L"Error", MB_OK | MB_ICONERROR);
					}

					hr = temp->GetCommandList()->Reset(temp->GetCommandAllocator()[temp->GetFrameIndex()], nullptr);
					if (FAILED(hr))
					{
						MessageBox(NULL, L"Error reset commandList", L"Error", MB_OK | MB_ICONERROR);
					}
					UpdateSubresources(temp->GetCommandList(), object->GetVertexBuffer(), object->GetvBufferUploadHeap(), 0, 0, 1, &object->GetVertexData());
					// transition the vertex buffer data from copy destination state to vertex buffer state
					temp->GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(object->GetVertexBuffer(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

					if (object->GetIndexBufferSize() > 0)
					{
						UpdateSubresources(temp->GetCommandList(), object->GetIndexBuffer(), object->GetIndexBufferUploadHeap(), 0, 0, 1, &object->GetIndexData());
						// transition the vertex buffer data from copy destination state to vertex buffer state
						temp->GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(object->GetIndexBuffer(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER));
					}
					for (int i{ 0 }; i < object->GetTextures().size(); ++i)
					{
						UpdateSubresources(temp->GetCommandList(), object->GetTextures()[i]->GetBuffer(), object->GetTextures()[i]->GetUploadHeap(), 0, 0, 1, &object->GetTextures()[i]->GetData());
						temp->GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(object->GetTextures()[i]->GetBuffer(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
					}

					temp->GetCommandList()->Close();
					ID3D12CommandList* ppCommandLists[] = { temp->GetCommandList() };
					temp->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

					temp->GetFenceValue()[temp->GetFrameIndex()]++;
					hr = temp->GetCommandQueue()->Signal(temp->GetFence()[temp->GetFrameIndex()], temp->GetFenceValue()[temp->GetFrameIndex()]);
					if (FAILED(hr))
					{
						MessageBox(NULL, L"Signal failed in SetActive()", L"Error", MB_OK | MB_ICONERROR);
					}


					temp->GetRenderedObjectsTab().push_back(object);
				}
			}
		}
	}
	else
	{
		if (temp)
		{
			resources::Text* object = m_device->GetResourcesManager()->GetTextManager()->GetTextByIndex(renderObject);

			if (object)
			{
				if (!active)
				{
					for (std::list<resources::Text*>::const_iterator it{ temp->GetRenderedText().begin() }, end{ temp->GetRenderedText().end() }; it != end; std::advance(it, 1))
						if ((*it)->GetId() == renderObject)
						{
							temp->GetRenderedText().erase(it);
							return;
						}
				}
				if (active)
				{
					for (std::list<resources::Text*>::const_iterator it{ temp->GetRenderedText().begin() }, end{ temp->GetRenderedText().end() }; it != end; std::advance(it, 1))
						if ((*it)->GetId() == renderObject)
							return;

					temp->WaitForPreviousFrame(false);
					hr = temp->GetCommandAllocator()[temp->GetFrameIndex()]->Reset();
					if (FAILED(hr))
					{
						MessageBox(NULL, L"Error reset command allocator", L"Error", MB_OK | MB_ICONERROR);
					}

					hr = temp->GetCommandList()->Reset(temp->GetCommandAllocator()[temp->GetFrameIndex()], nullptr);
					if (FAILED(hr))
					{
						MessageBox(NULL, L"Error reset commandList", L"Error", MB_OK | MB_ICONERROR);
					}

					UpdateSubresources(temp->GetCommandList(), object->GetFont()->m_fontTexture->GetBuffer(), object->GetFont()->m_fontTexture->GetUploadHeap(), 0, 0, 1, &object->GetFont()->m_fontTexture->GetData());
					temp->GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(object->GetFont()->m_fontTexture->GetBuffer(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

					temp->GetCommandList()->Close();
					ID3D12CommandList* ppCommandLists[] = { temp->GetCommandList() };
					temp->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

					temp->GetFenceValue()[temp->GetFrameIndex()]++;
					hr = temp->GetCommandQueue()->Signal(temp->GetFence()[temp->GetFrameIndex()], temp->GetFenceValue()[temp->GetFrameIndex()]);
					if (FAILED(hr))
					{
						MessageBox(NULL, L"Signal failed in SetActive()", L"Error", MB_OK | MB_ICONERROR);
					}

					temp->GetRenderedText().push_back(object);
				}
			}
		}
	}
}

void engine::rhi::RHI::SetText(const char* newText, int textId)
{
	if (newText)
	{
		resources::Text* text = m_device->GetResourcesManager()->GetTextManager()->GetTextByIndex(textId);

		if (text)
		{
			std::vector<wchar_t> vec;
			size_t len = strlen(newText);
			vec.resize(len + 1);
			mbstowcs(&vec[0], newText, len);
			const wchar_t* wText = &vec[0];

			text->SetText(wText);
		}
	}
}

void engine::rhi::RHI::SetPos(engine::core::maths::Vec2 newPos, int textId)
{
	resources::Text* text = m_device->GetResourcesManager()->GetTextManager()->GetTextByIndex(textId);

	if (text)
	{
		text->SetPos(newPos);
	}
}

void engine::rhi::RHI::SetShadersConstantBuffersTexturesSamplers(int renderObjectId, int* shadersId, int shadersNb, int* cbId, int cbNb,
	int* textures, int textureNb, int* staticSamplers, int staticSamplerNb)
{
	resources::PSO* pso;
	resources::RootSignature* rootSignature;
	std::vector<resources::ConstantBuffer*> cb;
	std::vector<resources::Texture*>text;
	for (int i{ 0 }; i < cbNb; ++i)
		cb.push_back(m_device->GetResourcesManager()->GetConstantBufferManager()->GetConstantBufferByIndex(cbId[i]));
	for (int i{ 0 }; i < textureNb; ++i)
		text.push_back(m_device->GetResourcesManager()->GetTextureManager()->GetTextureByIndex(textures[i]));


	D3D12_DESCRIPTOR_RANGE  descriptorTableRanges[1];
	D3D12_ROOT_DESCRIPTOR_TABLE descriptorTable;

	descriptorTableRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorTableRanges[0].NumDescriptors = textureNb;
	descriptorTableRanges[0].BaseShaderRegister = 0;
	descriptorTableRanges[0].RegisterSpace = 0;
	descriptorTableRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	descriptorTable.NumDescriptorRanges = _countof(descriptorTableRanges);
	descriptorTable.pDescriptorRanges = &descriptorTableRanges[0];


	D3D12_ROOT_PARAMETER* param = nullptr;
	size_t paramNb = 0;
	if (textures > 0)
	{
		paramNb = cb.size() + 1;
		param = new D3D12_ROOT_PARAMETER[paramNb];
		param[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		param[0].DescriptorTable = descriptorTable;
		param[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		for (int i{ 0 }; i < cb.size(); ++i)
			param[i + 1] = *cb[i]->GetRootParameters();
	}
	else
	{
		paramNb = cb.size();
		param = new D3D12_ROOT_PARAMETER[paramNb];
		for (int i{ 0 }; i < cb.size(); ++i)
			param[i] = *cb[i]->GetRootParameters();
	}




	D3D12_STATIC_SAMPLER_DESC* samplers = nullptr;
	if (staticSamplerNb > 0)
	{
		samplers = new D3D12_STATIC_SAMPLER_DESC[staticSamplerNb];
		for (int i{ 0 }; i < staticSamplerNb; ++i)
			samplers[i] = m_device->GetResourcesManager()->GetSamplerManager()->GetSamplerByIndex(staticSamplers[i]);
	}
	switch (shadersNb)
	{
	case 0:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb, D3D12_ROOT_SIGNATURE_FLAG_NONE
		);
		break;
	}
	case 1:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 2:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 3:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 4:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS
		);
		break;
	}
	case 5:
	{
		rootSignature = m_device->GetResourcesManager()->GetRootSignatureManager()->FindRootSignature
		(
			param, paramNb, samplers, staticSamplerNb,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
		);
		break;
	}
	default:
	{
		MessageBox(0, L"How many shaders are you loading ? o.o", L"Error", MB_OK);

	}
	}
	std::vector<resources::Shader*> shaderTab;
	for (int i = 0; i < shadersNb; ++i)
		shaderTab.push_back(m_device->GetResourcesManager()->GetShaderManager()->GetShaderByIndex(shadersId[i]));

	pso = m_device->GetResourcesManager()->GetPsoManager()->FindPso
	(
		rootSignature,
		m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObjectId)->GetPso()->GetDrawingType(),
		shaderTab, shadersNb, false
	);

	m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObjectId)->SetSamplers(samplers, staticSamplerNb);
	m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObjectId)->SetTextures(text);
	m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObjectId)->SetConstantBuffers(cb);
	m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObjectId)->SetRootSignature(rootSignature);
	m_device->GetResourcesManager()->GetRenderObjectManager()->GetRenderObjectByIndex(renderObjectId)->SetPSO(pso);
}

engine::rhi::resources::FontInfo engine::rhi::RHI::LoadFontInfo(std::wstring filename, int windowWidth, int windowHeight)
{
	std::wifstream fs;
	fs.open(filename);

	engine::rhi::resources::FontInfo font;
	std::wstring tmp;
	int startpos;

	// extract font name
	fs >> tmp >> tmp; // info face="Arial"
	startpos = tmp.find(L"") + 1;
	font.m_name = filename;

	// get font size
	fs >> tmp; // size=73
	startpos = tmp.find(L"=") + 1;
	font.m_size = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

	// bold, italic, charset, unicode, stretchH, smooth, aa, padding, spacing
	fs >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp; // bold=0 italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1 

														 // get padding
	fs >> tmp; // padding=5,5,5,5 
	startpos = tmp.find(L"=") + 1;
	tmp = tmp.substr(startpos, tmp.size() - startpos); // 5,5,5,5

													   // get up padding
	startpos = tmp.find(L",") + 1;
	font.m_toppadding = std::stoi(tmp.substr(0, startpos)) / (float)windowWidth;

	// get right padding
	tmp = tmp.substr(startpos, tmp.size() - startpos);
	startpos = tmp.find(L",") + 1;
	font.m_rightpadding = std::stoi(tmp.substr(0, startpos)) / (float)windowWidth;

	// get down padding
	tmp = tmp.substr(startpos, tmp.size() - startpos);
	startpos = tmp.find(L",") + 1;
	font.m_bottompadding = std::stoi(tmp.substr(0, startpos)) / (float)windowWidth;

	// get left padding
	tmp = tmp.substr(startpos, tmp.size() - startpos);
	font.m_leftpadding = std::stoi(tmp) / (float)windowWidth;

	fs >> tmp; // spacing=0,0

			   // get lineheight (how much to move down for each line), and normalize (between 0.0 and 1.0 based on size of font)
	fs >> tmp >> tmp; // common lineHeight=95
	startpos = tmp.find(L"=") + 1;
	font.m_lineHeight = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)windowHeight;

	// get base height (height of all characters), and normalize (between 0.0 and 1.0 based on size of font)
	fs >> tmp; // base=68
	startpos = tmp.find(L"=") + 1;
	font.m_baseHeight = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)windowHeight;

	// get texture width
	fs >> tmp; // scaleW=512
	startpos = tmp.find(L"=") + 1;
	font.m_textureWidth = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

	// get texture height
	fs >> tmp; // scaleH=512
	startpos = tmp.find(L"=") + 1;
	font.m_textureHeight = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

	// get pages, packed, page id
	fs >> tmp >> tmp; // pages=1 packed=0
	fs >> tmp >> tmp; // page id=0

					  // get texture filename
	std::wstring wtmp;
	fs >> wtmp; // file="Arial.png"
	startpos = wtmp.find(L"") + 1;
	font.m_fontImage = wtmp.substr(startpos, wtmp.size() - startpos - 1);

	// get number of characters
	fs >> tmp >> tmp; // chars count=97
	startpos = tmp.find(L"=") + 1;
	font.m_numCharacters = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

	// initialize the character list
	font.m_CharList = new engine::rhi::resources::FontChar[font.m_numCharacters];

	for (int c = 0; c < font.m_numCharacters; ++c)
	{
		// get unicode id
		fs >> tmp >> tmp; // char id=0
		startpos = tmp.find(L"=") + 1;
		font.m_CharList[c].id = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

		// get x
		fs >> tmp; // x=392
		startpos = tmp.find(L"=") + 1;
		font.m_CharList[c].u = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)font.m_textureWidth;

		// get y
		fs >> tmp; // y=340
		startpos = tmp.find(L"=") + 1;
		font.m_CharList[c].v = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)font.m_textureHeight;

		// get width
		fs >> tmp; // width=47
		startpos = tmp.find(L"=") + 1;
		tmp = tmp.substr(startpos, tmp.size() - startpos);
		font.m_CharList[c].width = (float)std::stoi(tmp) / (float)windowWidth;
		font.m_CharList[c].twidth = (float)std::stoi(tmp) / (float)font.m_textureWidth;

		// get height
		fs >> tmp; // height=57
		startpos = tmp.find(L"=") + 1;
		tmp = tmp.substr(startpos, tmp.size() - startpos);
		font.m_CharList[c].height = (float)std::stoi(tmp) / (float)windowHeight;
		font.m_CharList[c].theight = (float)std::stoi(tmp) / (float)font.m_textureHeight;

		// get xoffset
		fs >> tmp; // xoffset=-6
		startpos = tmp.find(L"=") + 1;
		font.m_CharList[c].xoffset = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)windowWidth;

		// get yoffset
		fs >> tmp; // yoffset=16
		startpos = tmp.find(L"=") + 1;
		font.m_CharList[c].yoffset = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)windowHeight;

		// get xadvance
		fs >> tmp; // xadvance=65
		startpos = tmp.find(L"=") + 1;
		font.m_CharList[c].xadvance = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos)) / (float)windowWidth;

		// get page
		// get channel
		fs >> tmp >> tmp; // page=0    chnl=0
	}

	// get number of kernings
	fs >> tmp >> tmp; // kernings count=96
	startpos = tmp.find(L"=") + 1;
	font.m_numKernings = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

	// initialize the kernings list
	font.m_KerningsList = new engine::rhi::resources::FontKerning[font.m_numKernings];

	for (int k = 0; k < font.m_numKernings; ++k)
	{
		// get first character
		fs >> tmp >> tmp; // kerning first=87
		startpos = tmp.find(L"=") + 1;
		font.m_KerningsList[k].firstid = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

		// get second character
		fs >> tmp; // second=45
		startpos = tmp.find(L"=") + 1;
		font.m_KerningsList[k].secondid = std::stoi(tmp.substr(startpos, tmp.size() - startpos));

		// get amount
		fs >> tmp; // amount=-1
		startpos = tmp.find(L"=") + 1;
		int t = (float)std::stoi(tmp.substr(startpos, tmp.size() - startpos));
		font.m_KerningsList[k].amount = (float)t / (float)windowWidth;
	}

	return font;
}

void engine::rhi::RHI::RegenFont(Window* temp)
{
	unsigned int fontNb{ m_device->GetResourcesManager()->GetFontManager()->GetFontNb() };
	std::vector<std::vector<char>> save;
	save.resize(fontNb);

	for (unsigned int i{ 0 }; i < fontNb; ++i)
	{
		size_t len = wcslen(m_device->GetResourcesManager()->GetFontManager()->GetFontByIndex(i)->m_name.c_str());
		save[i].resize(len + 1);
		std::wcstombs(&save[i][0], m_device->GetResourcesManager()->GetFontManager()->GetFontByIndex(i)->m_name.c_str(), len);
	}
	m_device->GetResourcesManager()->GetFontManager()->ClearFonts();
	temp->GetFonts().clear();

	for (unsigned int i{ 0 }; i < fontNb; ++i)
		GenFont(&save[i][0]);
}
