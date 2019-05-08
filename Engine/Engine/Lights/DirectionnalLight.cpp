#include "DirectionnalLight.h"

engine::light::DirectionnalLight::DirectionnalLight(int id, engine::core::maths::Vec3 direction, engine::core::maths::Vec4 color, float intensity) : 
	Light(id, { direction, 0.f }, color, intensity)
{

}

engine::light::DirectionnalLight::DirectionnalLight(const DirectionnalLight& dirLight) : 
	Light(dirLight.GetId(), dirLight.m_lightVec, dirLight.m_color, dirLight.m_intensity)
{

}


engine::light::DirectionnalLight::~DirectionnalLight()
{

}

engine::core::maths::Vec3 engine::light::DirectionnalLight::GetDirection() const
{
	return { m_lightVec.m_x, m_lightVec.m_y, m_lightVec.m_z };
}

engine::light::DirectionnalLight& engine::light::DirectionnalLight::operator=(const DirectionnalLight& other)
{
	*this = DirectionnalLight(other.GetId(), other.GetDirection(), other.GetColor(), other.GetIntensity());
	return *this;
}