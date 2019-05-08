#include "Text.h"
#include "../../Resource/Vertex.h"
engine::rhi::resources::Text::Text(ID3D12Device* device, int frameBufferSize, std::wstring text, FontInfo* font, PSO* pso, std::vector<ConstantBuffer*> cbs,
	engine::core::maths::Vec2 pos, engine::core::maths::Vec2 scale, engine::core::maths::Vec2 padding, engine::core::maths::Vec4 color, int id) :
	m_id{ id },
	m_device{ device },
	m_frameBufferSize{ frameBufferSize },
	m_text{ new std::wstring(text) },
	m_pso{ pso },
	m_font{ font },
	m_constantBuffers{ cbs },
	m_maxCharacters{ 1024 },
	m_pos{ pos },
	m_scale{ scale },
	m_padding{ padding },
	m_color{ color },
	m_vertexBuffer{ new ID3D12Resource*[m_frameBufferSize] },
	m_vertexBufferView{ new D3D12_VERTEX_BUFFER_VIEW[m_frameBufferSize] },
	m_vBGPUAddress{ new UINT8*[m_frameBufferSize] }
{
	HRESULT hr;

	m_heapDesc = {};
	m_heapDesc.NumDescriptors = 1;
	m_heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	m_heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	m_device->CreateDescriptorHeap(&m_heapDesc, IID_PPV_ARGS(&m_mainDescriptorHeap));

	UINT srvHandleSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	CD3DX12_CPU_DESCRIPTOR_HANDLE srvHandle(m_mainDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), 0, m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

	m_device->CreateShaderResourceView(m_font->m_fontTexture->GetBuffer(), &m_font->m_fontTexture->GetsrvDesc(), srvHandle);


	for (int i = 0; i < m_frameBufferSize; ++i)
	{
		hr = m_device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // upload heap
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(m_maxCharacters * sizeof(resource::TextVertex)),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer[i]));
		if (FAILED(hr))
		{
			MessageBox(0, L"Text uploadHeap creation failed", L"Error", MB_OK);
		}
		m_vertexBuffer[i]->SetName(L"Text Vertex Buffer Upload Resource Heap");

		CD3DX12_RANGE readRange(0, 0);    // We do not intend to read from this resource on the CPU. (so end is less than or equal to begin)

		// map the resource heap to get a gpu virtual address to the beginning of the heap
		hr = m_vertexBuffer[i]->Map(0, &readRange, reinterpret_cast<void**>(&m_vBGPUAddress[i]));

		m_vertexBufferView[i].BufferLocation = m_vertexBuffer[i]->GetGPUVirtualAddress();
		m_vertexBufferView[i].StrideInBytes = sizeof(resource::TextVertex);
		m_vertexBufferView[i].SizeInBytes = m_maxCharacters * sizeof(resource::TextVertex);
	}
}

engine::rhi::resources::Text::~Text()
{
	for (int i = 0; i < m_frameBufferSize; ++i)
		SAFE_RELEASE(m_vertexBuffer[i]);
	for (int i = 0; i < m_frameBufferSize; ++i)
		SAFE_DELETE_ARRAY(m_vertexBuffer);
	for (int i = 0; i < m_frameBufferSize; ++i)
		SAFE_DELETE_ARRAY(m_vBGPUAddress);

	SAFE_DELETE_ARRAY(m_vertexBufferView);
	SAFE_RELEASE(m_mainDescriptorHeap);
	SAFE_DELETE(m_text);
}

int engine::rhi::resources::Text::GetId() const
{
	return m_id;
}

std::wstring* engine::rhi::resources::Text::GetText() const
{
	return m_text;
}

engine::rhi::resources::PSO* engine::rhi::resources::Text::GetPso() const
{
	return m_pso;
}

engine::rhi::resources::FontInfo* engine::rhi::resources::Text::GetFont() const
{
	return m_font;
}

std::vector<engine::rhi::resources::ConstantBuffer*> engine::rhi::resources::Text::GetConstantBuffers() const
{
	return m_constantBuffers;
}

int engine::rhi::resources::Text::GetMaxCharacters() const
{
	return m_maxCharacters;
}

ID3D12Resource** engine::rhi::resources::Text::GetVertexBuffer() const
{
	return m_vertexBuffer;
}

D3D12_VERTEX_BUFFER_VIEW* engine::rhi::resources::Text::GetVertexBufferView() const
{
	return m_vertexBufferView;
}

UINT8 ** engine::rhi::resources::Text::GetVGPUAddress() const
{
	return m_vBGPUAddress;
}

engine::core::maths::Vec2 engine::rhi::resources::Text::GetPos() const
{
	return m_pos;
}

engine::core::maths::Vec2 engine::rhi::resources::Text::GetScale() const
{
	return m_scale;
}

engine::core::maths::Vec2 engine::rhi::resources::Text::GetPadding() const
{
	return m_padding;
}

engine::core::maths::Vec4 engine::rhi::resources::Text::GetColor() const
{
	return m_color;
}

void engine::rhi::resources::Text::SetText(std::wstring newText)
{
	*m_text = newText;
}

void engine::rhi::resources::Text::SetFont(FontInfo* newFont)
{
	m_font = newFont;
}

void engine::rhi::resources::Text::SetPos(engine::core::maths::Vec2 pos)
{
	m_pos = pos;
}

bool engine::rhi::resources::Text::operator==(const Text & other) const
{
	if (*m_text == *other.GetText() && *m_font == *other.GetFont() && m_constantBuffers.size() == other.GetConstantBuffers().size())
		return true;
	return false;
}

ID3D12DescriptorHeap* engine::rhi::resources::Text::GetMainDescriptorHeap() const
{
	return m_mainDescriptorHeap;
}

D3D12_DESCRIPTOR_HEAP_DESC engine::rhi::resources::Text::GetHeapDesc() const
{
	return m_heapDesc;
}