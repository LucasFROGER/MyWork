#ifndef _TEXT_MANAGER_H_
#define _TEXT_MANAGER_H_

#include "Resources/Text.h"

namespace engine
{
	namespace rhi
	{
		class TextManager
		{

		public:

			TextManager(ID3D12Device* device, int frameBufferSize);
			~TextManager();

			resources::Text* FindText(std::wstring text, engine::rhi::resources::FontInfo* font, resources::PSO* pso, std::vector<resources::ConstantBuffer*> cbs,
				engine::core::maths::Vec2 pos, engine::core::maths::Vec2 scale, engine::core::maths::Vec2 padding, engine::core::maths::Vec4 color);
			resources::Text* GetTextByIndex(int index)const;
			unsigned int GetTextNb() const;

		private:

			ID3D12Device * m_device;
			int m_frameBufferSize;
			std::vector<resources::Text*> m_TextTab;


		};
	}
}
#endif

