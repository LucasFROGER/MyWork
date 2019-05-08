#include "CubeCollider.h"
#include "../../Utils/ConvertionHandler.h"

engine::physic::component::CubeCollider::CubeCollider(physx::PxRigidActor* actor, PhysicMgr* physicMgr, bool trigger,
	Transform* objectTransform, physx::PxMaterial& mat) :
	engine::physic::component::ACollider(physicMgr, trigger, objectTransform, ECollType::CUBE, mat),
	m_dimensions{ 0.25f, 0.25f, 0.25f }
{
	ChangeActor(actor);
	BuildShape();
}

engine::physic::component::CubeCollider::~CubeCollider()
{
	if (m_shape)
	{
		m_actor->detachShape(*m_shape);
	}
}

void engine::physic::component::CubeCollider::Update()
{

}

void engine::physic::component::CubeCollider::SetDimensions(engine::core::maths::Vec3 dimensions)
{
	m_dimensions = dimensions;
	BuildShape();
}

engine::core::maths::Vec3 engine::physic::component::CubeCollider::GetDimensions() const
{
	return m_dimensions;
}

void engine::physic::component::CubeCollider::BuildShape()
{
	if (m_shape == nullptr)
		m_shape = m_actor->createShape(physx::PxBoxGeometry(engine::physic::ConvertionHandler::EngineToPhysx(m_dimensions)), m_material);
	else
	{
		m_shape->setGeometry(physx::PxBoxGeometry(engine::physic::ConvertionHandler::EngineToPhysx(m_dimensions)));

	}
	SetTriggerFlag();
	m_shape->userData = this;
}