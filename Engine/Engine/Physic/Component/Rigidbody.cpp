#include "Rigidbody.h"
#include "../Utils/ConvertionHandler.h"
#include "../../Component/Physic/Rigidbody.h"

engine::physic::component::Rigidbody::Rigidbody(physx::PxRigidDynamic* rigidbody, engine::physic::Transform* transform) :
	m_rigidbody{ rigidbody },
	m_transform{ transform },
	m_positionConstraints{ engine::core::maths::Vec3{ 1.f, 1.f, 1.f } },
	m_rotationConstraints{ engine::core::maths::Vec3{ 1.f, 1.f, 1.f } }
{
	SetUseGravity(true);
	UpdateLockFlag();
}

engine::physic::component::Rigidbody::~Rigidbody()
{
	m_rigidbody->clearForce();
	m_rigidbody->clearTorque();
	m_rigidbody->setLinearVelocity(ConvertionHandler::EngineToPhysx(engine::core::maths::Vec3::Zero()));
}

void engine::physic::component::Rigidbody::Move(float deltaTime)
{

}

void engine::physic::component::Rigidbody::Result()
{

}

void engine::physic::component::Rigidbody::Exit()
{
	m_rigidbody->clearForce();
	m_rigidbody->clearTorque();
	m_rigidbody->setLinearVelocity(ConvertionHandler::EngineToPhysx(engine::core::maths::Vec3::Zero()));
}

void engine::physic::component::Rigidbody::SetUseGravity(bool useGravity)
{
	m_useGravity = useGravity;
	m_rigidbody->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, !useGravity);
}

void engine::physic::component::Rigidbody::SetPositionConstraint(bool x, bool y, bool z)
{
	m_positionConstraints = engine::core::maths::Vec3(x ? 0 : 1, y ? 0 : 1, z ? 0 : 1); // If x, y, z = 0 there is a constraint
	UpdateLockFlag();
}

void engine::physic::component::Rigidbody::SetRotationConstraint(bool x, bool y, bool z)
{
	m_rotationConstraints = engine::core::maths::Vec3(x ? 0 : 1, y ? 0 : 1, z ? 0 : 1); // If x, y, z = 0 there is a constraint
	UpdateLockFlag();
}

bool engine::physic::component::Rigidbody::IsUsingGravity() const
{
	return m_useGravity;
}

void engine::physic::component::Rigidbody::UpdateLockFlag()
{
	m_rigidbody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X, m_positionConstraints.m_x == 0);
	m_rigidbody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, m_positionConstraints.m_y == 0);
	m_rigidbody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z, m_positionConstraints.m_z == 0);

	m_rigidbody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, m_rotationConstraints.m_x == 0);
	m_rigidbody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, m_rotationConstraints.m_y == 0);
	m_rigidbody->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, m_rotationConstraints.m_z == 0);
}
