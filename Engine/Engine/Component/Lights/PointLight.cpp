#include "PointLight.h"

#include "../../Engine.h"
#include "../../SceneGraph/GameObject.h"

engine::component::light::PointLight::PointLight(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(false, typeid(PointLight).name(), gameObject, engine),
	m_light{ nullptr },
	m_positionOffset{ 0.f, 0.f, 0.f },
	m_color{ 1.f, 1.f, 1.f, 1.f },
	m_intensity{ 100.f }
{
	m_engine = engine;
}

void engine::component::light::PointLight::Init()
{
	m_light = m_engine->GetLightMgr()->AddPointLight(m_transform->GetPosition(engine::physic::ESpace::WORLD) + m_positionOffset, m_color, m_intensity);
}

void engine::component::light::PointLight::Render()
{

}

void engine::component::light::PointLight::OnDestroy()
{

}

void engine::component::light::PointLight::OnActivation()
{

}

void engine::component::light::PointLight::OnDeactivation()
{

}

void engine::component::light::PointLight::SetPositionOffset(engine::core::maths::Vec3 positionOffset)
{
	m_positionOffset = positionOffset;
	if (m_light != nullptr)
		m_light->SetColor(m_transform->GetPosition(engine::physic::ESpace::WORLD) +  positionOffset);
}

void engine::component::light::PointLight::SetColor(engine::core::maths::Vec4 color)
{
	m_color = color;
	if (m_light != nullptr)
		m_light->SetColor(color);
}

void engine::component::light::PointLight::SetIntensity(float intensity)
{
	m_intensity = intensity;
	if (m_light != nullptr)
		m_light->SetIntensity(intensity);
}
