#include "Light.h"

engine::light::Light::Light() :
	m_id{ -1 },
	m_used{ false }, 
	m_lightVec{ 0.f, 0.f, 0.f, 0.f },
	m_color{ 0.f, 0.f, 0.f, 0.f },
	m_intensity{ 0.f }
{
	SetProjection();
	SetView();
}

engine::light::Light::Light(const Light& other) :
	m_id{ other.m_id },
	m_used{ other.m_used },
	m_lightVec{ other.m_lightVec },
	m_color{ other.m_color },
	m_intensity{ other.m_intensity }
{
	SetProjection();
	SetView();
}

engine::light::Light::Light(int id, engine::core::maths::Vec4 light, engine::core::maths::Vec4 color, float intensity) :
	m_id{ id },
	m_used{ true },
	m_lightVec{ light },
	m_color{ color },
	m_intensity{ intensity }
{ 
	SetProjection();
	SetView();
}

engine::light::Light::~Light()
{

}

void engine::light::Light::SetColor(engine::core::maths::Vec4 color)
{
	m_color = color;
}

void engine::light::Light::SetIntensity(float intensity)
{
	m_intensity = intensity;
}

void engine::light::Light::SetUnused()
{
	m_used = false;
}

const int engine::light::Light::GetId() const
{
	return m_id;
}

engine::core::maths::Vec4 engine::light::Light::GetColor() const
{
	return m_color;
}

float engine::light::Light::GetIntensity() const
{
	return m_intensity;
}

void engine::light::Light::SetView()
{
	m_view = engine::core::maths::Mat4::Identity();
}

void engine::light::Light::SetProjection()
{
	m_projection = engine::core::maths::Mat4::Identity();
}

bool engine::light::Light::IsUsed() const
{
	return m_used;
}

void engine::light::Light::SetLight(engine::core::maths::Vec3 light)
{
	m_lightVec = engine::core::maths::Vec4{ light, m_lightVec.m_w };
}

engine::core::maths::Vec4 engine::light::Light::GetLightVec() const
{
	return m_lightVec;
}

engine::light::Light& engine::light::Light::operator=(const Light& other)
{
	this->m_lightVec = other.m_lightVec;
	this->m_color = other.m_color;
	this->m_intensity = other.m_intensity;
	this->m_projection = other.m_projection;
	this->m_view = other.m_view;
	this->m_used = other.m_used;
	this->m_id = other.m_id;
	return *this;
}