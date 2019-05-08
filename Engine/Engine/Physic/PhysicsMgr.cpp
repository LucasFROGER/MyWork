#include "PhysicMgr.h"
#include "Callbacks/UserCallback.h"

static engine::physic::UserErrorCallback gDefaultErrorCallback;
static physx::PxDefaultAllocator gDefaultAllocatorCallback;

engine::physic::PhysicMgr::PhysicMgr()
{

}

engine::physic::PhysicMgr::~PhysicMgr()
{
	PxCloseExtensions();
	m_physics->release();
	m_cooking->release();
	m_pvd->release();
	m_foundation->release(); // Must be the last release
}

bool engine::physic::PhysicMgr::InitializePhysics()
{
	m_foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback,
		gDefaultErrorCallback);
	if (!m_foundation)
		return false;

	bool recordMemoryAllocations = false;
	
	m_pvd = PxCreatePvd(*m_foundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("PhysicMgr", 5425, 10);
	m_pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	physx::PxTolerancesScale tolerancesScale;
	
	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, tolerancesScale, recordMemoryAllocations, m_pvd);
	if (!m_physics)
		return false;
	
	m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_foundation, physx::PxCookingParams(tolerancesScale));
	if (!m_cooking)
		return false;
	
	PxInitExtensions(*m_physics, m_pvd);
	
	return true;
}

physx::PxFoundation* engine::physic::PhysicMgr::GetFoundation() const
{
	return m_foundation;
}

physx::PxPvd* engine::physic::PhysicMgr::GetPvd() const
{
	return m_pvd;
}

physx::PxPhysics* engine::physic::PhysicMgr::GetPhysics() const
{
	return m_physics;
}

physx::PxCooking* engine::physic::PhysicMgr::GetCooking() const
{
	return m_cooking;
}

void engine::physic::PhysicMgr::SetCubeMesh(resource::Mesh* mesh)
{
	m_cubeMesh = mesh;
}

void engine::physic::PhysicMgr::SetSphereMesh(resource::Mesh* mesh)
{
	m_sphereMesh = mesh;
}

void engine::physic::PhysicMgr::SetCapsuleMeshs(resource::Mesh* up, resource::Mesh* corp, resource::Mesh* down)
{
	m_capsuleUpMesh = up;
	m_capsuleCorpMesh = corp;
	m_capsuleBotMesh = down;
}

void engine::physic::PhysicMgr::SetPhysMaterial(resource::Material* material)
{
	m_physMaterial = material;
}

engine::resource::Mesh* engine::physic::PhysicMgr::GetCubeMesh()
{
	return m_cubeMesh;
}

engine::resource::Mesh* engine::physic::PhysicMgr::GetSphereMesh()
{
	return m_sphereMesh;
}

engine::resource::Mesh* engine::physic::PhysicMgr::GetCapsuleUpMesh()
{
	return m_capsuleUpMesh;
}

engine::resource::Mesh* engine::physic::PhysicMgr::GetCapsuleCorpMesh()
{
	return m_capsuleCorpMesh;
}
engine::resource::Mesh* engine::physic::PhysicMgr::GetCapsuleBotMesh()
{
	return m_capsuleBotMesh;
}

engine::resource::Material* engine::physic::PhysicMgr::GetPhysMaterial()
{
	return m_physMaterial;
}