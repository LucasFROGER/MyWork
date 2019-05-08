#include "SphereCollider.h"
#include "../../Utils/ConvertionHandler.h"


engine::physic::component::SphereCollider::SphereCollider(physx::PxRigidActor* actor, PhysicMgr* physicMgr, bool trigger,
	Transform* objectTransform, physx::PxMaterial& mat) :
	engine::physic::component::ACollider(physicMgr, trigger, objectTransform, ECollType::SPHERE, mat),
	m_radius{ 0.5f }
{
	ChangeActor(actor);
	BuildShape();
}

engine::physic::component::SphereCollider::~SphereCollider()
{
	if (m_shape)
	{
		m_actor->detachShape(*m_shape);
	}
}

void engine::physic::component::SphereCollider::Update()
{

}

void engine::physic::component::SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
	BuildShape();
}

float engine::physic::component::SphereCollider::GetRadius() const
{
	return m_radius;
}

void engine::physic::component::SphereCollider::BuildShape()
{
	if (!m_shape)
		m_shape = m_actor->createShape(physx::PxSphereGeometry(m_radius), m_material);
	else
		m_shape->setGeometry(physx::PxSphereGeometry(m_radius));
	SetTriggerFlag();
	m_shape->userData = this;
}