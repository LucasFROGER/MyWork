#include "Rigidbody.h"
#include "../../SceneGraph/GameObject.h"

engine::component::physic::Rigidbody::Rigidbody(scene_graph::GameObject* gameObject, engine::Engine* engine) :
	Component(true, typeid(Rigidbody).name(), gameObject, engine),
	m_physObject{ gameObject->GetPhysObject() },
	m_posConst{ engine::core::maths::Vec3{ 1.f, 1.f, 1.f } },
	m_rotConst{ engine::core::maths::Vec3{ 1.f, 1.f, 1.f } },
	m_rigidbody{ nullptr },
	m_useGravity{ true }
{

}

void engine::component::physic::Rigidbody::Init()
{
	if (*m_physObject != nullptr)
	{
		m_rigidbody = (*m_physObject)->AddRigidbody();
		m_rigidbody->SetPositionConstraint(GetPosXConstraint(), GetPosYConstraint(), GetPosZConstraint());
		m_rigidbody->SetRotationConstraint(GetRotXConstraint(), GetRotYConstraint(), GetRotZConstraint());
		m_rigidbody->SetUseGravity(m_useGravity);
	}
}

void engine::component::physic::Rigidbody::OnDestroy()
{
	if (*m_physObject != nullptr)
	{
		(*m_physObject)->RemoveRigidbody();
		m_rigidbody = nullptr;
	}
}

void engine::component::physic::Rigidbody::UseGravity(bool useGravity)
{
	m_useGravity = useGravity;
	if(m_rigidbody != nullptr)
		m_rigidbody->SetUseGravity(useGravity);
}

bool engine::component::physic::Rigidbody::IsUsingGravity()
{
	return m_rigidbody->IsUsingGravity();
}

void engine::component::physic::Rigidbody::SetPositionConstraint(bool x, bool y, bool z)
{
	m_posConst = engine::core::maths::Vec3(x ? 0 : 1, y ? 0 : 1, z ? 0 : 1);
	if (m_rigidbody)
		m_rigidbody->SetPositionConstraint(x, y, z);
}

void engine::component::physic::Rigidbody::SetRotationConstraint(bool x, bool y, bool z)
{
	m_rotConst = engine::core::maths::Vec3(x ? 0 : 1, y ? 0 : 1, z ? 0 : 1);
	if (m_rigidbody)
		m_rigidbody->SetRotationConstraint(x, y, z);
}

bool engine::component::physic::Rigidbody::GetPosXConstraint() const
{
	return m_posConst.m_x == 0;
}

bool engine::component::physic::Rigidbody::GetPosYConstraint() const
{
	return m_posConst.m_y == 0;
}

bool engine::component::physic::Rigidbody::GetPosZConstraint() const
{
	return m_posConst.m_z == 0;
}

bool engine::component::physic::Rigidbody::GetRotXConstraint() const
{
	return m_rotConst.m_x == 0;
}

bool engine::component::physic::Rigidbody::GetRotYConstraint() const
{
	return m_rotConst.m_y == 0;
}

bool engine::component::physic::Rigidbody::GetRotZConstraint() const
{
	return m_rotConst.m_z == 0;
}
