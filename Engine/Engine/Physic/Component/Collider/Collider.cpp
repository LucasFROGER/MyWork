#include "Collider.h"

#include "../../Scene/Scene.h"
#include "../../Utils/ConvertionHandler.h"

engine::physic::component::ACollider::ACollider(PhysicMgr* physicMgr, bool trigger,
	Transform* objectTransform, ECollType type, physx::PxMaterial& mat) :
	m_trigger{ trigger },
	m_type{ type },
	m_objectTransform{ objectTransform },
	m_shape{ nullptr },
	m_actor{ nullptr },
	m_material{ mat }
{

}

engine::physic::component::ACollider::~ACollider()
{

}

bool engine::physic::component::ACollider::IsTrigger() const
{
	return m_trigger;
}

void engine::physic::component::ACollider::SetTrigger(bool trigger)
{
	m_trigger = trigger;
	SetTriggerFlag();
}

void engine::physic::component::ACollider::SetRelativePos(engine::core::maths::Vec3 relativePos)
{
	m_relativePos = relativePos;
}

void engine::physic::component::ACollider::SetRelativeRot(engine::core::maths::Vec3 relativeRot)
{
	m_relativeRot = engine::core::maths::Quaternion::Euler(relativeRot);
}

void engine::physic::component::ACollider::ChangeActor(physx::PxRigidActor* actor)
{
	if (m_actor)
		m_actor->detachShape(*m_shape);
	m_actor = actor;
	if(m_shape)
		m_actor->attachShape(*m_shape);

}

engine::physic::component::ECollType engine::physic::component::ACollider::GetType() const
{
	return m_type;
}

engine::core::maths::Vec3 engine::physic::component::ACollider::GetRelativePos() const
{
	return m_relativePos;
}

engine::core::maths::Quaternion engine::physic::component::ACollider::GetRelativeRot() const
{
	return m_relativeRot;
}

void engine::physic::component::ACollider::SetTriggerFlag()
{
	//if (!m_trigger)
	//{
	//	m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
	//	m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
	//}
	//else
	//{
	//	m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	//	m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
	//}
}