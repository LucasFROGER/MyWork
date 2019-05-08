#include "PointLight.h"

engine::light::PointLight::PointLight(int id, engine::core::maths::Vec3 position, engine::core::maths::Vec4 color, float intensity) : 
	Light(id, { position, 1.f }, color, intensity)
{

}

engine::light::PointLight::PointLight::PointLight(const PointLight& dirLight) : 
	Light(dirLight.GetId(), dirLight.m_lightVec, dirLight.m_color, dirLight.m_intensity)
{

}

engine::light::PointLight::PointLight::~PointLight()
{

}

engine::core::maths::Vec3 engine::light::PointLight::PointLight::GetPosition() const
{
	return { m_lightVec.m_x, m_lightVec.m_y, m_lightVec.m_z };
}

engine::light::PointLight& engine::light::PointLight::PointLight::operator=(const PointLight& other)
{
	return PointLight(other.GetId(), other.GetPosition(), other.GetColor(), other.GetIntensity());
}