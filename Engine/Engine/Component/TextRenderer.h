#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include "Component.h"
#include "../Resource/Font.h"
#include "../Resource/Material.h"
#include "../LowRenderer/Vertex.h"
#include "../RHI/RHI.h"

namespace engine
{
	namespace component
	{
		class TextRenderer final : public Component
		{
		public:
			TextRenderer(scene_graph::GameObject* gameObject, engine::Engine* engine);

			void Init() override;
			void Awake() override {}
			void PreProcess() override {}
			void Process(float deltaTime) override {}
			void LateProcess(float deltaTime) override {}
			void Render() override;
			void OnExit() override {}
			void OnDestroy() override {}

			void OnActivation() override;
			void OnDeactivation() override;

			const char* GetText();

			void SetText(const char* str);
			void SetPosition(engine::core::maths::Vec2 pos);
			void SetScale(engine::core::maths::Vec2 scale);
			void SetPadding(engine::core::maths::Vec2 pad);
			void SetColor(engine::core::maths::Vec4 color);

			void SetFont(resource::Font* mesh);
			void SetShaderProgram(resource::ShaderProgram* shaders);

		private:

			engine::rhi::RHI* m_rhi;
			std::vector<int> m_windowIDs;
			resource::Font* m_font;
			resource::ShaderProgram* m_shaders;
			low_renderer::ConstantBufferPerObject m_transformBuffer;
			low_renderer::BufferPerText m_placeBuffer;
			int m_transformBufferID;

			int m_renderID;
			const char* m_str;
			void InitRenderObject();
		};
	}
}


#endif