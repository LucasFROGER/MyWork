#include "TextRenderer.h"

#include "../Engine.h"
#include "../SceneGraph/GameObject.h"

using namespace engine::resource;

engine::component::TextRenderer::TextRenderer(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(true, typeid(TextRenderer).name(), gameObject, engine),
	m_windowIDs{},
	m_font{ nullptr },
	m_shaders{ nullptr },
	m_renderID{ -1 },
	m_transformBufferID{ -1 },
	m_str{""}
{
	m_rhi = engine->GetRHI();
}

void engine::component::TextRenderer::Init()
{
	InitRenderObject();
}

void engine::component::TextRenderer::Render()
{
	if (m_font == nullptr || m_shaders == nullptr)
		return;

	m_transformBuffer.wMat = m_transform->GetLocalToWorldMatrix();
	camera::Camera* camera = m_gameObject->GetScene()->GetCamera();
	m_transformBuffer.vpMat = camera->GetProjectMat() * camera->GetViewMat();

	if (m_transformBufferID != -1)
	{
		m_rhi->UpdateConstantBuffer(m_transformBufferID, &m_transformBuffer, sizeof(m_transformBuffer));
	}
}

void engine::component::TextRenderer::OnActivation()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, true, m_windowIDs[i], true);
		}
	}
}

void engine::component::TextRenderer::OnDeactivation()
{
	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
		{
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i], true);
		}
	}
}

const char* engine::component::TextRenderer::GetText()
{
	return m_str;
}

void engine::component::TextRenderer::SetText(const char* str)
{
	m_str = str;
	if (m_renderID != -1)
		m_rhi->SetText(str, m_renderID);
}

void engine::component::TextRenderer::SetPosition(engine::core::maths::Vec2 pos)
{
	m_placeBuffer.pos = pos;
	if (m_renderID != -1)
		m_rhi->SetPos(pos, m_renderID);
}

void engine::component::TextRenderer::SetScale(engine::core::maths::Vec2 scale)
{
	m_placeBuffer.scale = scale;
}

void engine::component::TextRenderer::SetPadding(engine::core::maths::Vec2 pad)
{
	m_placeBuffer.padding = pad;
}

void engine::component::TextRenderer::SetColor(engine::core::maths::Vec4 color)
{
	m_placeBuffer.color = color;
}

void engine::component::TextRenderer::SetFont(Font* font)
{
	m_font = font;

	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i], true);

		m_renderID = -1;
		InitRenderObject();
	}
}

void engine::component::TextRenderer::SetShaderProgram(resource::ShaderProgram* shaders)
{
	m_shaders = shaders;

	if (m_renderID != -1)
	{
		for (int i{ 0 }; i < m_windowIDs.size(); ++i)
			m_rhi->SetActive(m_renderID, false, m_windowIDs[i], true);

		m_renderID = -1;
		InitRenderObject();
	}
}

void engine::component::TextRenderer::InitRenderObject()
{
	if (m_font == nullptr)
		return;
	if (m_shaders == nullptr)
		return;

	if (m_renderID == -1)
	{
		m_windowIDs = m_gameObject->GetScene()->GetTargetWinIds();
		int bvTextShader = m_rhi->GenShader("Data/Shaders/BasicTextVertexShader.hlsl", engine::rhi::resources::EShaderEnum::VERTEX_SHADER);
		int bpTextShader = m_rhi->GenShader("Data/Shaders/BasicTextPixelShader.hlsl", engine::rhi::resources::EShaderEnum::PIXEL_SHADER);
		
		
		int bShaders[2]{ bvTextShader, bpTextShader };
		int basicSampler = m_rhi->GenStaticSampler(D3D12_FILTER_MIN_MAG_MIP_POINT, 0, 0, 0.0f, D3D12_FLOAT32_MAX);

		int font = m_rhi->GenFont("Data/Fonts/arial.fnt");
		int font2 = m_rhi->GenFont("Data/Fonts/Chiller.fnt");


		m_renderID = m_rhi->GenText(m_str, bShaders, 2, nullptr, 0, &basicSampler, 1, font2,
			m_placeBuffer.pos, m_placeBuffer.scale, m_placeBuffer.padding, m_placeBuffer.color);

		if (m_gameObject->GetIsActive() && m_renderID != -1)
		{
			for (int i{ 0 }; i < m_windowIDs.size(); ++i)
			{
				m_rhi->SetActive(m_renderID, true, m_windowIDs[i], true);
			}
		}
	}
}