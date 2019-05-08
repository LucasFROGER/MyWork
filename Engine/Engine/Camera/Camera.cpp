#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera.h"

engine::camera::Camera::Camera(EProjectType type, float width, float height, float _near, float _far, float fov, engine::core::maths::Vec3 pos, engine::core::maths::Vec3 target) :
	m_type{ type },
	m_viewWidth{ width },
	m_viewHeight{ height },
	m_fov{ fov },
	m_near{ _near },
	m_far{ _far },
	m_position{ pos },
	m_target{ target }
{
	InitProjectionMat();
	LookAt();
}

engine::camera::Camera::~Camera()
{

}

void engine::camera::Camera::InitProjectionMat()
{
	float ratio = m_viewWidth / m_viewHeight;
	float t{ tanf((m_fov * (float)M_PI / 180.f) / 2.f) };
	if (m_type == EProjectType::PERSPECTIVE)
	{
		m_projectMat.m_matrix[0][0] = 1.f / (t * ratio);
		m_projectMat.m_matrix[0][1] = 0.f;
		m_projectMat.m_matrix[0][2] = 0.f;
		m_projectMat.m_matrix[0][3] = 0.f;

		m_projectMat.m_matrix[1][0] = 0.f;
		m_projectMat.m_matrix[1][1] = 1.f / t;
		m_projectMat.m_matrix[1][2] = 0.f;
		m_projectMat.m_matrix[1][3] = 0.f;

		m_projectMat.m_matrix[2][0] = 0.f;
		m_projectMat.m_matrix[2][1] = 0.f;
		m_projectMat.m_matrix[2][2] = (m_far) / (m_far - m_near);
		m_projectMat.m_matrix[2][3] = -(m_near * m_far) / (m_far - m_near);

		m_projectMat.m_matrix[3][0] = 0.f;
		m_projectMat.m_matrix[3][1] = 0.f;
		m_projectMat.m_matrix[3][2] = 1.f;
		m_projectMat.m_matrix[3][3] = 0.f;
	}
	else if (m_type == EProjectType::ORTHOGRAPHIC)
	{
		float left{ -m_viewWidth / 2 };
		float right{ m_viewWidth / 2 };
		float top{ -m_viewHeight / 2 };
		float bottom{ m_viewHeight / 2 };

		m_near = 0.1f;
		m_far = 1.f;

		m_projectMat.m_matrix[0][0] = 2.f / (right - left);
		m_projectMat.m_matrix[0][1] = 0.f;
		m_projectMat.m_matrix[0][2] = 0.f;
		m_projectMat.m_matrix[0][3] = 0.f;
		m_projectMat.m_matrix[1][0] = 0.f;
		m_projectMat.m_matrix[1][1] = 2.f / (top - bottom);
		m_projectMat.m_matrix[1][2] = 0.f;
		m_projectMat.m_matrix[1][3] = 0.f;
		m_projectMat.m_matrix[2][0] = 0.f;
		m_projectMat.m_matrix[2][1] = 0.f;
		m_projectMat.m_matrix[2][2] = 1.f / (m_far - m_near);
		m_projectMat.m_matrix[2][3] = 0.f;
		m_projectMat.m_matrix[3][0] = -1.f * ((right + left) / (right - left));
		m_projectMat.m_matrix[3][1] = -1.f * ((top + bottom) / (top - bottom));
		m_projectMat.m_matrix[3][2] = -1.f * ((m_far + m_near) / (m_far - m_near));
		m_projectMat.m_matrix[3][3] = 0.f;
	}
}

void engine::camera::Camera::SetType(EProjectType type)
{
	if (type == m_type)
		return;
	m_type = type;
	InitProjectionMat();
}

void engine::camera::Camera::SetFov(float fov)
{
	m_fov = fov;
	InitProjectionMat();
}

void engine::camera::Camera::SetViewSize(float width, float height, float _near, float _far)
{
	m_viewWidth = width;
	m_viewHeight = height;
	m_near = _near;
	m_far = _far;
	InitProjectionMat();
}

engine::camera::EProjectType engine::camera::Camera::GetType() const
{
	return m_type;
}

engine::core::maths::Mat4 engine::camera::Camera::GetViewMat() const
{
	return m_viewMat;
}

engine::core::maths::Mat4 engine::camera::Camera::GetProjectMat() const
{
	return m_projectMat;
}

engine::core::maths::Vec3 engine::camera::Camera::GetTarget() const
{
	return m_target;
}

engine::core::maths::Vec3 engine::camera::Camera::GetPosition() const
{
	return m_position;
}

engine::core::maths::Vec3 engine::camera::Camera::GetForward() const
{
	return m_forward;
}

engine::core::maths::Vec3 engine::camera::Camera::GetRight() const
{
	return m_right;
}

engine::core::maths::Vec3 engine::camera::Camera::GetUp() const
{
	return m_up;
}

void engine::camera::Camera::SetPosition(engine::core::maths::Vec3 pos)
{
	m_position = pos;
	LookAt();
}

void engine::camera::Camera::SetTarget(engine::core::maths::Vec3 target)
{
	m_target = target;
	LookAt();
}

void engine::camera::Camera::LookAt()
{

	engine::core::maths::Vec3 up{ 0.f,1.f,0.f };
	engine::core::maths::Vec3 target{m_position + m_target};


	m_forward = m_target.GetNormalized(); // The "forward" vector.
	m_right = up.CrossProduct(m_forward).GetNormalized();	// The "right" vector.
	m_up = m_forward.CrossProduct(m_right); // The "up" vector.

	m_viewMat =
	{
		m_right.m_x,		m_right.m_y,		m_right.m_z,		-m_right.DotProduct(m_position),
		m_up.m_x,			m_up.m_y,			m_up.m_z,			-m_up.DotProduct(m_position),
		m_forward.m_x,		m_forward.m_y,		m_forward.m_z,		-m_forward.DotProduct(m_position),
		0.f,				0.f,				0.f,				1.f
	};
}

void engine::camera::Camera::Check()
{
	m_target;
	m_position;
	m_forward;
	m_right;
	m_up;
	m_viewMat;
	m_projectMat;
	engine::core::maths::Vec2 pos;
	pos += engine::core::maths::Vec2{ 1.f, 2.f };
}