#include "Transform.h"

using namespace engine::core::maths;

engine::physic::Transform::Transform() :
	m_localScale{ Vec3::One() },
	m_isLocalWorldUpToDate{ true },
	m_isWorldLocalUpToDate{ true },
	m_parent{ nullptr }
{}

engine::physic::Transform::Transform(Transform* parent) :
	m_parent{ parent },
	m_localScale{ Vec3::One() },
	m_isLocalWorldUpToDate{ true },
	m_isWorldLocalUpToDate{ true }
{
	if (m_parent != nullptr)
		m_parent->m_children.emplace_back(this);
}

engine::physic::Transform::~Transform()
{
	if (m_parent != nullptr)
		m_parent->Remove(this);
}

Mat4 engine::physic::Transform::GetLocalToWorldMatrix(Transform* subject)
{
	if (subject != nullptr)
		return subject->GetLocalToWorldMatrix();

	return Mat4::Identity();
}

Mat4 engine::physic::Transform::GetWorldToLocalMatrix(Transform* subject)
{
	if (subject != nullptr)
		return subject->GetWorldToLocalMatrix();

	return Mat4::Identity();
}

Quaternion engine::physic::Transform::GetRotation(Transform* subject, engine::physic::ESpace space)
{
	if (subject != nullptr)
		return subject->GetRotation(space);

	return Quaternion::Identity();
}

void engine::physic::Transform::Remove(Transform* child)
{
	if (child != nullptr && m_children.size() > 0)
	{
		auto it{ std::find(m_children.begin(), m_children.end(), child) };
		if (it != m_children.end())
			m_children.erase(it);
	}
}

void engine::physic::Transform::Translate(const Vec3& translation, ESpace space)
{
	if (space == ESpace::LOCAL)
	{
		ChangeState();
		m_localPosition += translation; //m_localRotation.GetRotatedVertex(translation);
	}

	else if (space == ESpace::WORLD)
	{
		ChangeState();
		m_localPosition += translation; //GetRotation(m_parent).GetInverse().GetRotatedVertex(translation);
	}
}

void engine::physic::Transform::Rotate(const Quaternion& rotation, ESpace space)
{
	if (space == ESpace::LOCAL)
	{
		ChangeState();
		m_localRotation *= rotation;
	}

	else if (space == ESpace::WORLD)
	{
		ChangeState();
		m_localRotation *= GetRotation().GetInverse() * rotation * GetRotation();
	}
}

void engine::physic::Transform::Scale(const Vec3& scale)
{
	ChangeState();
	m_localScale = m_localScale + scale;
	m_localScale.m_x = m_localScale.m_x < 0.f ? 0.f : m_localScale.m_x;
	m_localScale.m_y = m_localScale.m_y < 0.f ? 0.f : m_localScale.m_y;
	m_localScale.m_z = m_localScale.m_z < 0.f ? 0.f : m_localScale.m_z;
}

engine::physic::Transform* engine::physic::Transform::GetParent()
{
	return m_parent;
}

Vec3 engine::physic::Transform::GetPosition(ESpace space) const
{
	if (space == ESpace::LOCAL)
		return m_localPosition;

	else if (space == ESpace::WORLD)
		return GetLocalToWorldMatrix(m_parent) * m_localPosition;

	return Vec3::Zero();
}

Quaternion engine::physic::Transform::GetRotation(ESpace space) const
{
	if (space == ESpace::LOCAL)
		return m_localRotation;

	else if (space == ESpace::WORLD)
		return GetRotation(m_parent) * m_localRotation;

	return Quaternion::Identity();
}

Vec3 engine::physic::Transform::GetScale(ESpace space) const
{
	//if (space == ESpace::LOCAL)
		return m_localScale;



	return Vec3::One();
}

const Mat4& engine::physic::Transform::GetLocalToWorldMatrix()
{
	if (!m_isLocalWorldUpToDate)
	{
		m_localToWorldMatrix = GetLocalToWorldMatrix(m_parent) * Mat4::TRS(m_localPosition, m_localRotation, m_localScale);
		m_isLocalWorldUpToDate = true;
	}

	return m_localToWorldMatrix;
}

const Mat4& engine::physic::Transform::GetWorldToLocalMatrix()
{
	if (!m_isWorldLocalUpToDate)
	{
		m_worldToLocalMatrix = GetLocalToWorldMatrix().GetInverse();
		m_isWorldLocalUpToDate = true;
	}

	return m_worldToLocalMatrix;
}

Vec3 engine::physic::Transform::GetRight() const
{
	return GetRotation().GetRotatedVertex(Vec3::Right());
}

Vec3 engine::physic::Transform::GetUp() const
{
	return GetRotation().GetRotatedVertex(Vec3::Up());
}

Vec3 engine::physic::Transform::GetForward() const
{
	return GetRotation().GetRotatedVertex(Vec3::Forward());
}

void engine::physic::Transform::SetParent(Transform* parent)
{
	if (m_parent != nullptr)
	{
		m_localPosition = GetLocalToWorldMatrix(m_parent) * m_localPosition;
		m_localRotation = GetRotation(m_parent) * m_localRotation;
		m_parent->Remove(this);
	}
	if (parent != nullptr)
		parent->m_children.emplace_back(this);

 	m_parent = parent;

	ChangeState();
	m_localPosition = GetWorldToLocalMatrix(m_parent) * m_localPosition;
	m_localRotation = GetRotation(m_parent).GetInverse() * m_localRotation;
	//Update();
}

void engine::physic::Transform::SetPosition(const Vec3& position, ESpace space)
{
	if (space == ESpace::LOCAL)
	{
		ChangeState();
		m_localPosition = position;
	}

	else if (space == ESpace::WORLD)
	{
		ChangeState();
		m_localPosition = GetWorldToLocalMatrix(m_parent) * position;
	}
}

void engine::physic::Transform::SetRotation(const engine::core::maths::Quaternion& rotation, ESpace space)
{
	if (space == ESpace::LOCAL)
	{
		ChangeState();
		m_localRotation = rotation;
	}

	else if (space == ESpace::WORLD)
	{
		ChangeState();
		m_localRotation = GetRotation(m_parent).GetInverse() * rotation;
	}
}

void engine::physic::Transform::SetScale(const engine::core::maths::Vec3& scale)
{
	ChangeState();
	m_localScale = scale;
}

void engine::physic::Transform::SetRight(const engine::core::maths::Vec3& right)
{

}

void engine::physic::Transform::SetUp(const engine::core::maths::Vec3& up)
{

}

void engine::physic::Transform::SetForward(const engine::core::maths::Vec3& forward)
{

}

void engine::physic::Transform::ChangeState()
{
	if (m_isLocalWorldUpToDate || m_isWorldLocalUpToDate)
	{
		m_isLocalWorldUpToDate = false;
		m_isWorldLocalUpToDate = false;

		for (Transform* child : m_children)
			child->ChangeState();
	}
}

void engine::physic::Transform::Update()
{
	m_localPosition = GetWorldToLocalMatrix(m_parent) * m_localPosition;
	m_localRotation = GetRotation(m_parent).GetInverse() * m_localRotation;

	for (Transform* child : m_children)
		child->Update();
}