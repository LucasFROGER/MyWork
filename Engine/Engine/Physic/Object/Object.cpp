#include "Object.h"
#include "../Scene/Scene.h" 
#include "../Utils/ConvertionHandler.h"
#include "../PhysicMgr.h"
#include "../../SceneGraph/GameObject.h"
#include "../../SceneGraph/SceneMgr.h"

engine::physic::Object::Object(int id, bool isStatic, Transform* transform, Scene* scene, scene_graph::GameObject* gameObject) :
	m_id{ id },
	m_isStatic{ isStatic },
	m_transform{ transform },
	m_scene{ scene },
	m_rigidbody{ nullptr },
	m_material{ nullptr },
	m_actor{ nullptr },
	m_simulate{ false },
	m_active{ true },
	m_gameObject{ gameObject },
	m_landing{ false }
{
	PhysicMgr* physMgr = m_scene->GetPhysicMgr();

	m_actor = physMgr->GetPhysics()->createRigidDynamic(ConvertionHandler::EngineToPhysx(*m_transform));
	m_material = physMgr->GetPhysics()->createMaterial(5.0f, 1.0f, 1.0f);
	physx::PxScene* pxScene = m_scene->GetPxScene();
	pxScene->addActor(*m_actor);
	m_actor->userData = this;

	m_actor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
	m_actor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
}

engine::physic::Object::~Object()
{
	for (int i{ 0 }; i < m_colliders.size(); ++i)
	{
		if (m_colliders[i] != nullptr)
		{
			delete m_colliders[i];
			m_colliders[i] = nullptr;
		}
	}
	m_colliders.clear();

	if (m_rigidbody != nullptr)
	{
		delete m_rigidbody;
		m_rigidbody = nullptr;
	}
	ClearObject();
}

void engine::physic::Object::Move(float deltaTime)
{
	if (m_isStatic || !HasRigidbody())
	{
		m_actor->setMassSpaceInertiaTensor(physx::PxVec3(0, 0, 0));
		m_landing = true;
	}
	else
	{
		m_actor->setMassSpaceInertiaTensor(physx::PxVec3(1, 1, 1));
		m_landing = false;
	}
	m_actor->setGlobalPose(ConvertionHandler::EngineToPhysx(*m_transform));
}

void engine::physic::Object::Result()
{
	m_transform->SetPosition(ConvertionHandler::PhysxToEngine(m_actor->getGlobalPose().p), engine::physic::ESpace::WORLD);
	if (IsLanding())
		Stop();
}

void engine::physic::Object::SetActive(bool active)
{
	m_active = active;

	if (m_isStatic)
		return;

	if (m_actor != nullptr)
		active ? m_actor->wakeUp() : m_actor->putToSleep();
}

int engine::physic::Object::AddCollider(component::ECollType collType, bool trigger)
{
	int id = m_colliderId.GetNewId();
	if (id < m_colliders.size())
	{
		switch (collType)
		{
		case engine::physic::component::ECollType::CUBE:
		{
			m_colliders[id] = new component::CubeCollider(m_actor, m_scene->GetPhysicMgr(), trigger, m_transform, *m_material);
			break;
		}
		case engine::physic::component::ECollType::CAPSULE:
		{
			m_colliders[id] = new component::CapsuleCollider(m_actor, m_scene->GetPhysicMgr(), trigger, m_transform, *m_material);
			break;
		}
		case engine::physic::component::ECollType::SPHERE:
		{
			m_colliders[id] = new component::SphereCollider(m_actor, m_scene->GetPhysicMgr(), trigger, m_transform, *m_material);
			break;
		}

		}
	}
	else
	{
		switch (collType)
		{
		case engine::physic::component::ECollType::CUBE:
		{
			m_colliders.push_back(new component::CubeCollider(m_actor, m_scene->GetPhysicMgr(), trigger, m_transform, *m_material));
			break;
		}
		case engine::physic::component::ECollType::CAPSULE:
		{
			m_colliders.push_back(new component::CapsuleCollider(m_actor, m_scene->GetPhysicMgr(), trigger, m_transform, *m_material));
			break;
		}
		case engine::physic::component::ECollType::SPHERE:
		{
			m_colliders.push_back(new component::SphereCollider(m_actor, m_scene->GetPhysicMgr(), trigger, m_transform, *m_material));
			break;
		}
		}
	}
	return id;
}

engine::physic::component::ACollider* engine::physic::Object::GetCollider(int id)
{
	if (id >= 0 && id < m_colliders.size() && m_colliderId.CheckFreeId(id) == false)
		return m_colliders[id];
	return nullptr;
}

void engine::physic::Object::RemoveCollider(int id)
{
	if (id >= 0 && id < m_colliders.size() && m_colliderId.CheckFreeId(id) == false)
	{
		m_colliderId.ReleaseId(id);
		delete m_colliders[id];
		m_colliders[id] = nullptr;
	}
}

engine::physic::component::Rigidbody* engine::physic::Object::AddRigidbody()
{
	if (m_rigidbody == nullptr)
	{
		m_rigidbody = new engine::physic::component::Rigidbody(m_actor, m_transform);
	}
	return m_rigidbody;
}

void engine::physic::Object::RemoveRigidbody()
{
	if (HasRigidbody())
	{
		delete m_rigidbody;
		m_rigidbody = nullptr;
	}
}

void engine::physic::Object::Stop()
{
	m_actor->clearForce();
	m_actor->clearTorque();
	m_actor->setLinearVelocity(ConvertionHandler::EngineToPhysx(engine::core::maths::Vec3::Zero()));
}

void engine::physic::Object::SetIsStatic(bool isStatic)
{
	m_isStatic = isStatic;
	m_actor->setMassSpaceInertiaTensor(isStatic? physx::PxVec3(0, 0, 0) : physx::PxVec3(1, 1, 1));
}

void engine::physic::Object::SetIsLanding(bool isLanding)
{
	m_landing = isLanding;
}

int engine::physic::Object::GetId() const
{
	return m_id;
}

engine::physic::Scene* engine::physic::Object::GetScene()
{
	return m_scene;
}

bool engine::physic::Object::IsStatic() const
{
	return m_isStatic;
}

bool engine::physic::Object::IsLanding() const
{
	return m_landing;
}

bool engine::physic::Object::HasRigidbody() const
{
	return m_rigidbody != nullptr;
}

void engine::physic::Object::OnCollisionEnter(CollisionInfo info)
{
	m_gameObject->OnCollisionEnter(info);
}

void engine::physic::Object::OnCollisionStay(CollisionInfo info)
{
	m_gameObject->OnCollisionStay(info);
}

void engine::physic::Object::OnCollisionExit(CollisionInfo info)
{
	m_gameObject->OnCollisionExit(info);
}

void engine::physic::Object::OnTriggerEnter(TriggerInfo info)
{
	m_gameObject->OnTriggerEnter(info);
}

void engine::physic::Object::OnTriggerStay(TriggerInfo info)
{
	m_gameObject->OnTriggerStay(info);
}

void engine::physic::Object::OnTriggerExit(TriggerInfo info)
{
	m_gameObject->OnTriggerExit(info);

}

engine::scene_graph::GameObject* engine::physic::Object::GetGameObject() const
{
	return m_gameObject;
}

void engine::physic::Object::ClearObject()
{
	if (m_material)
	{
		m_material->release();
		m_material = nullptr;
	}

	for (size_t i = 0; i < m_colliders.size(); i++)
	{
		RemoveCollider(i);
	}

	ClearActor();
}

void engine::physic::Object::ClearActor()
{
	if (m_actor)
	{
		m_actor->release();
		m_actor = nullptr;
	}
	//m_dynaActor = nullptr; // rigidBody
	//m_statActor = nullptr; 
}