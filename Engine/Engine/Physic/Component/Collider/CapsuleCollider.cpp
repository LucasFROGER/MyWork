#include "CapsuleCollider.h"
#include "../../Utils/ConvertionHandler.h"


engine::physic::component::CapsuleCollider::CapsuleCollider(physx::PxRigidActor* actor, PhysicMgr* physicMgr, bool trigger, 
	Transform* objectTransform, physx::PxMaterial& mat) : 
	engine::physic::component::ACollider(physicMgr, trigger, objectTransform, ECollType::CAPSULE, mat),
	m_halfRadius{ 0.25f },
	m_radius{ 0.25f }
{
	ChangeActor(actor);
	BuildShape();
}

engine::physic::component::CapsuleCollider::~CapsuleCollider()
{
	if (m_shape)
	{
		m_actor->detachShape(*m_shape);
	}
}

void engine::physic::component::CapsuleCollider::Update()
{

}

void engine::physic::component::CapsuleCollider::SetDimensions(float halfRadius, float radius)
{
	m_halfRadius = halfRadius;
	m_radius = radius;
	BuildShape();
}

float engine::physic::component::CapsuleCollider::GetHalfRadius() const
{
	return m_halfRadius;
}

float engine::physic::component::CapsuleCollider::GetRadius() const
{
	return m_radius;
}

void engine::physic::component::CapsuleCollider::BuildShape()
{
	if (!m_shape)
	{
		m_shape = m_actor->createShape(physx::PxCapsuleGeometry(m_radius, m_halfRadius), m_material);
		engine::physic::Transform trans = ConvertionHandler::PhysxToEngine(m_shape->getLocalPose());
		trans.Rotate(engine::core::maths::Quaternion::Euler({ 0.f, 0.f, 90.f }));
		m_shape->setLocalPose(engine::physic::ConvertionHandler::EngineToPhysx(trans));
	}
	else
	{
		m_shape->setGeometry(physx::PxCapsuleGeometry(m_radius, m_halfRadius));
		engine::physic::Transform trans = ConvertionHandler::PhysxToEngine(m_shape->getLocalPose());
		//trans.Rotate(engine::core::maths::Quaternion::Euler({ 0.f, 0.f, 90.f }));
		//m_shape->setLocalPose(engine::physic::ConvertionHandler::EngineToPhysx(trans));
	}
	SetTriggerFlag();
	m_shape->userData = this;
}