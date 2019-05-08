#include "Scene.h"
#include "../PhysicMgr.h"
#include "PxPhysXConfig.h"
#include "PxFiltering.h"
#include "../Utils/ConvertionHandler.h"

engine::physic::Scene::Scene(PhysicMgr* physicMgr) :
	m_physicMgr{ physicMgr },
	m_simuCallback{ new SceneCallbackEvent() },
	m_colliModCallback{ new CollisionModificationCallback() },
	m_collisionMgr{ new CollisionMgr() },
	m_simulate{ false },
	m_gravity{ engine::core::maths::Vec3::Zero() }
{
	physx::PxTolerancesScale tolerancesScale;
	physx::PxSceneDesc sceneDesc(tolerancesScale);
	sceneDesc.gravity = physx::PxVec3(0.0f, 0.0f, 0.0f);


	sceneDesc.filterShader = engine::physic::SceneCallbackEvent::SampleFilterShader;
	sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
	sceneDesc.simulationEventCallback = m_simuCallback;
	sceneDesc.contactModifyCallback = m_colliModCallback;
	sceneDesc.flags = physx::PxSceneFlag::eENABLE_KINEMATIC_PAIRS | physx::PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS;
	m_scene = m_physicMgr->GetPhysics()->createScene(sceneDesc);
}

engine::physic::Scene::~Scene()
{
	for (int i{ 0 }; i < m_objects.size(); ++i)
	{
		if (m_objects[i] != nullptr)
		{
			delete m_objects[i];
			m_objects[i] = nullptr;
		}
	}
	m_objects.clear();
	m_scene->release();
	delete m_simuCallback;
	delete m_colliModCallback;
	delete m_collisionMgr;
}

void engine::physic::Scene::Start()
{
	m_simulate = true;
}

void engine::physic::Scene::Update(float deltaTime)
{
	if (!m_simulate)
		return;
	
	for (int i{ 0 }; i < m_objects.size(); ++i)
	{
		if (m_objects[i] != nullptr)
		{
			m_objects[i]->Move(deltaTime);
		}
	}

	m_scene->simulate(deltaTime);
	m_scene->fetchResults(true);

	for (int i{ 0 }; i < m_objects.size(); ++i)
	{
		if (m_objects[i] != nullptr)
		{
			m_objects[i]->Result();
		}
	}
	m_collisionMgr->FixedUpdate();
	m_collisionMgr->Update();
}

void engine::physic::Scene::FixedUpdate(float deltaTime)
{
	
}

void engine::physic::Scene::LateUpdate(float deltaTime)
{
}

void engine::physic::Scene::Exit()
{
	m_simulate = true;
}

engine::physic::Object* engine::physic::Scene::CreateObject(Transform* transform, bool isStatic, scene_graph::GameObject* gameObject)
{
	int id = m_idAllocator.GetNewId();
	if (id < m_objects.size())
	{
		m_objects[id] = new Object(id, isStatic, transform, this, gameObject);
		return m_objects[id];
	}
	m_objects.push_back(new Object(id, isStatic, transform, this, gameObject));
	return m_objects.back();
}

void engine::physic::Scene::DeleteObject(Object* object)
{
	if (object == nullptr)
		return;
	m_collisionMgr->RemoveObject(object);
	int id = object->GetId();
	for (int i{ 0 }; i < m_objects.size(); ++i)
	{
		if(m_objects[i] != nullptr)
		{
			if (id == m_objects[i]->GetId())
			{
				m_idAllocator.ReleaseId(id);
				delete m_objects[i];
				m_objects[i] = nullptr;
			}
		}
	}
}

void engine::physic::Scene::SetActive(bool active)
{
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] != nullptr)
			m_objects[i]->SetActive(active);
	}
}

void engine::physic::Scene::SetGravity(engine::core::maths::Vec3 gravity)
{
	m_gravity = gravity;
	m_gravity /= 10.f;
	m_scene->setGravity(engine::physic::ConvertionHandler::EngineToPhysx(m_gravity));
}

physx::PxScene* engine::physic::Scene::GetPxScene() const
{
	return m_scene;
}

engine::physic::PhysicMgr * engine::physic::Scene::GetPhysicMgr() const
{
	return m_physicMgr;
}

engine::physic::CollisionMgr* engine::physic::Scene::GetCollisionMgr() const
{
	return m_collisionMgr;
}

engine::core::maths::Vec3 engine::physic::Scene::GetGravity()
{
	return m_gravity * 10.f;
}
