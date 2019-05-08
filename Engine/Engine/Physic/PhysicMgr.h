#ifndef _PHYSIC_MGR_H_
#define _PHYSIC_MGR_H_

//#define DEBUG
#define FIXED_TIME_INTERVAL 0.0f

#include "Utils/PhysicLibLoader.h"
#include "PxPhysicsAPI.h"
#include "Scene/Scene.h"


namespace engine
{
	namespace resource 
	{ 
		class Mesh; 
		class Material;
	}

	namespace physic
	{
		class PhysicMgr
		{
		public:
			PhysicMgr();
			~PhysicMgr();
			
			bool InitializePhysics();

			physx::PxFoundation* GetFoundation() const;
			physx::PxPvd* GetPvd() const;
			physx::PxPhysics* GetPhysics() const;
			physx::PxCooking* GetCooking() const;

			void SetCubeMesh(resource::Mesh* mesh);
			void SetSphereMesh(resource::Mesh* mesh);
			void SetCapsuleMeshs(resource::Mesh* up, resource::Mesh* corp, resource::Mesh* down);
			void SetPhysMaterial(resource::Material* material);

			resource::Mesh* GetCubeMesh();
			resource::Mesh* GetSphereMesh();
			resource::Mesh* GetCapsuleUpMesh();
			resource::Mesh* GetCapsuleCorpMesh();
			resource::Mesh* GetCapsuleBotMesh();
			resource::Material* GetPhysMaterial();

		private:
			physx::PxFoundation* m_foundation;
			physx::PxPvd* m_pvd;
			physx::PxPhysics* m_physics;
			physx::PxCooking* m_cooking;

			resource::Mesh* m_cubeMesh;
			resource::Mesh* m_sphereMesh;
			resource::Mesh* m_capsuleUpMesh;
			resource::Mesh* m_capsuleCorpMesh;
			resource::Mesh* m_capsuleBotMesh;

			resource::Material* m_physMaterial;
		};
	}
}



#endif
