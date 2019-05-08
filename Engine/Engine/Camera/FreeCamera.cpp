#include "FreeCamera.h"
#include "../Core/Maths/Defines.h"

#define YAW_LIMIT PI_f

engine::camera::FreeCamera::FreeCamera(float width, float height, float _near, float _far, float fov, engine::core::maths::Vec3 pos, engine::core::maths::Vec3 target, float speed, float sensitivity)
	: Camera(EProjectType::PERSPECTIVE, width, height, _near, _far, fov, pos, target),
	m_speed{ speed },
	m_sensitivity{ sensitivity },
	m_yaw { acosf(target.m_y)},
	m_pitch{ acosf(target.m_x / sinf(acosf(target.m_y))) }
{ }

engine::camera::FreeCamera::~FreeCamera()
{

}

void engine::camera::FreeCamera::MoveForward(float deltaTime)
{
	engine::core::maths::Vec3 dir{ m_forward * deltaTime * m_speed };
	m_position += dir;
	LookAt();
}

void engine::camera::FreeCamera::MoveBackward(float deltaTime)
{
	engine::core::maths::Vec3 dir{ -m_forward * deltaTime * m_speed };
	m_position += dir;
	LookAt();
}

void engine::camera::FreeCamera::MoveRight(float deltaTime)
{
	engine::core::maths::Vec3 dir{ m_right * deltaTime * m_speed };
	m_position += dir;
	LookAt();
}

void engine::camera::FreeCamera::MoveLeft(float deltaTime)
{
	engine::core::maths::Vec3 dir{ -m_right * deltaTime * m_speed };
	m_position += dir;
	LookAt();
}

void engine::camera::FreeCamera::MoveUp(float deltaTime)
{
	engine::core::maths::Vec3 dir{ m_up * deltaTime * m_speed };
	m_position += dir;
	LookAt();
}

void engine::camera::FreeCamera::MoveDown(float deltaTime)
{
	engine::core::maths::Vec3 dir{ -m_up * deltaTime * m_speed };
	m_position += dir;
	LookAt();
}

void engine::camera::FreeCamera::MoveTarget(engine::core::maths::Vec2 target, float deltaTime)
{
	float newPitch = m_pitch - (target.m_x * m_sensitivity * deltaTime);
	float newYaw = m_yaw + (target.m_y * m_sensitivity * deltaTime);
	m_pitch = newPitch;
	m_yaw = newYaw <= YAW_LIMIT && newYaw >= 0 ? newYaw : m_yaw;

	m_target.m_x = cosf(m_pitch) * sinf(m_yaw); // cosf
	m_target.m_y = cosf(m_yaw);
	m_target.m_z = sinf(m_pitch) * sinf(m_yaw);
	LookAt();
}

#undef YAW_LIMIT