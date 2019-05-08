#include "DirectionnalLight.h"

#include "../../Engine.h"
#include "../../SceneGraph/GameObject.h"

engine::component::light::DirectionnalLight::DirectionnalLight(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(false, typeid(DirectionnalLight).name(), gameObject, engine),
	m_light{ nullptr },
	m_direction{ -0.5f, -0.5f, -0.5f },
	m_color{ 1.f, 1.f, 1.f, 1.f },
	m_intensity{ 100.f }
{
	m_engine = engine;
}

void engine::component::light::DirectionnalLight::Init()
{
	if(m_engine)
		m_light = m_engine->GetLightMgr()->AddDirectionalLight(m_direction, m_color, m_intensity);
}

void engine::component::light::DirectionnalLight::Render()
{

}

void engine::component::light::DirectionnalLight::OnDestroy()
{

}

void engine::component::light::DirectionnalLight::OnActivation()
{

}

void engine::component::light::DirectionnalLight::OnDeactivation()
{

}

void engine::component::light::DirectionnalLight::SetDirection(engine::core::maths::Vec3 direction)
{
	m_direction = direction;
	if (m_light != nullptr)
		m_light->SetLight(direction);
}

void engine::component::light::DirectionnalLight::SetColor(engine::core::maths::Vec4 color)
{
	m_color = color;
	if (m_light != nullptr)
		m_light->SetColor(color);
}

void engine::component::light::DirectionnalLight::SetIntensity(float intensity)
{
	m_intensity = intensity;
	if (m_light != nullptr)
		m_light->SetIntensity(intensity);
}