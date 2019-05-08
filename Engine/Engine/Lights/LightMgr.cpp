#include "LightMgr.h"

#include "../RHI/RHI.h"

engine::light::LightMgr::LightMgr(engine::rhi::RHI* rhi) :
	m_rhi{ rhi },
	m_lightBufferID{ -1 }
{
	m_lightBufferID = m_rhi->GenConstantBuffer(&m_lightBuff, sizeof(m_lightBuff), 1);
}

engine::light::LightMgr::~LightMgr()
{

}

void engine::light::LightMgr::Update()
{
	m_rhi->UpdateConstantBuffer(m_lightBufferID, &m_lightBuff, sizeof(m_lightBuff));
}

engine::light::Light* engine::light::LightMgr::AddDirectionalLight(engine::core::maths::Vec3 direction, engine::core::maths::Vec4 color, float intensity)
{
	for (int i{ 0 }; i < MAX_LIGHT_COUNT; ++i)
		if (m_lightBuff.m_lights[i].IsUsed() == false)
		{
			m_lightBuff.m_lights[i] = engine::light::DirectionnalLight(i, direction, color, intensity);
			return &m_lightBuff.m_lights[i];
		}
	return nullptr;
}

engine::light::Light* engine::light::LightMgr::AddPointLight(engine::core::maths::Vec3 position, engine::core::maths::Vec4 color, float intensity)
{
	for (int i{ 0 }; i < MAX_LIGHT_COUNT; ++i)
		if (m_lightBuff.m_lights[i].IsUsed() == false)
		{
			m_lightBuff.m_lights[i] = engine::light::PointLight(i, position, color, intensity);
			return &m_lightBuff.m_lights[i];
		}
	return nullptr;
}

void engine::light::LightMgr::DeleteLight(engine::light::Light* light)
{
	if (light != nullptr)
		DeleteLight(light->GetId());
}

void engine::light::LightMgr::DeleteLight(int id)
{
	if (id > 0 && id < MAX_LIGHT_COUNT)
		m_lightBuff.m_lights[id].SetUnused();
}

void engine::light::LightMgr::ClearLights()
{
	for (int i{ 0 }; i < MAX_LIGHT_COUNT; ++i)
		m_lightBuff.m_lights[i].SetUnused();
}


engine::light::LightsBuffer& engine::light::LightMgr::GetLightData()
{
	return m_lightBuff;
}
//
//void engine::light::LightMgr::SampleShadowMap(bool sample)
//{
//	m_lightBuff.m_sampleShadowMap = sample;
//}

void engine::light::LightMgr::SetAmbientColor(engine::core::maths::Vec4 color)
{
	m_lightBuff.m_ambientColor = color;
}

int engine::light::LightMgr::GetLightBufferID() const
{
	return m_lightBufferID;
}
