#ifndef _TEXT_H_
#define _TEXT_H_

#include "PSO.h"
#include "FontInfo.h"
#include "ConstantBuffer.h"
#include "../../Core/Maths/Vector/Vec2.h"
#include "../../Core/Maths/Vector/Vec4.h"

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class Text
			{
			public:

				Text(ID3D12Device* device, int frameBufferSize, std::wstring text, FontInfo* fontId, PSO* pso, std::vector<ConstantBuffer*> cbs,
					engine::core::maths::Vec2 pos, engine::core::maths::Vec2 scale, engine::core::maths::Vec2 padding, engine::core::maths::Vec4 color, int id);
				~Text();

				int GetId() const;
				std::wstring* GetText() const;
				PSO* GetPso() const;
				FontInfo* GetFont() const;
				std::vector<ConstantBuffer*> GetConstantBuffers() const;
				int GetMaxCharacters() const;
				ID3D12Resource** GetVertexBuffer() const;
				D3D12_VERTEX_BUFFER_VIEW* GetVertexBufferView() const;
				UINT8** GetVGPUAddress() const;
				ID3D12DescriptorHeap* GetMainDescriptorHeap()const;
				D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc() const;
				engine::core::maths::Vec2 GetPos() const;
				engine::core::maths::Vec2 GetScale() const;
				engine::core::maths::Vec2 GetPadding() const;
				engine::core::maths::Vec4 GetColor() const;

				void SetText(std::wstring newText);
				void SetFont(FontInfo* newFont);
				void SetPos(engine::core::maths::Vec2);

				bool operator==(const Text& other) const;

			private:

				int m_id;
				ID3D12Device* m_device;
				int m_frameBufferSize;
				std::wstring* m_text;
				FontInfo* m_font;
				PSO* m_pso;
				std::vector<ConstantBuffer*> m_constantBuffers;
				ID3D12DescriptorHeap* m_mainDescriptorHeap;
				D3D12_DESCRIPTOR_HEAP_DESC m_heapDesc;
				int m_maxCharacters;
				engine::core::maths::Vec2 m_pos;
				engine::core::maths::Vec2 m_scale;
				engine::core::maths::Vec2 m_padding;
				engine::core::maths::Vec4 m_color;

				ID3D12Resource** m_vertexBuffer;
				D3D12_VERTEX_BUFFER_VIEW* m_vertexBufferView;
				UINT8** m_vBGPUAddress;
			};
		}
	}
}
#endif
