#include "GameObject.h"

#include "Scene.h"
#include "../Component/Component.h"

using namespace engine::physic;
using namespace engine::component;

engine::scene_graph::GameObject::GameObject(Scene* scene, engine::Engine* engine, std::string name, GameObject* parent) :
	m_scene{ scene },
	m_name{ name },
	m_engine{ engine },
	m_parent{ parent },
	m_isActive{ true },
	m_isStatic{ false },
	m_wasAwakeCalled{ false },
	m_wasInitCalled{ false },
	m_physObject{ nullptr }
{
	if (m_parent != nullptr)
	{
		m_transform.SetParent(m_parent->GetTransform());
		m_parent->m_children.emplace_back(this);
	}
}

engine::scene_graph::GameObject::~GameObject()
{
	m_scene->GetPhysScene()->DeleteObject(m_physObject);
	OnExit();


	ClearComponentsList();
	if (m_parent != nullptr)
		m_parent->Remove(this);
}

void engine::scene_graph::GameObject::Init()
{
	if (m_wasInitCalled)
		return;
	m_physObject = m_scene->GetPhysScene()->CreateObject(&m_transform, m_isStatic, this);
	m_wasInitCalled = true;
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->Init();
	}
}

void engine::scene_graph::GameObject::Awake()
{
	m_wasAwakeCalled = true;
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->Awake();
	}
}

void engine::scene_graph::GameObject::PreProcess()
{
	if (!m_wasAwakeCalled)
	{
		Awake();
		return;
	}
	
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr && wrapper->Get()->GetIsEnable())
			wrapper->Get()->PreProcess();
	}
}

void engine::scene_graph::GameObject::ContinuousProcess(float deltaTime)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr && wrapper->Get()->GetIsEnable())
			wrapper->Get()->ContinuousProcess(deltaTime);
	}
}

void engine::scene_graph::GameObject::Process(float deltaTime)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr && wrapper->Get()->GetIsEnable())
			wrapper->Get()->Process(deltaTime);
	}
}

void engine::scene_graph::GameObject::FixedProcess(float deltaTime)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr && wrapper->Get()->GetIsEnable())
			wrapper->Get()->FixedProcess(deltaTime);
	}
}

void engine::scene_graph::GameObject::LateProcess(float deltaTime)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr && wrapper->Get()->GetIsEnable())
			wrapper->Get()->LateProcess(deltaTime);
	}
}

void engine::scene_graph::GameObject::Render()
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr && wrapper->Get()->GetIsEnable())
			wrapper->Get()->Render();
	}
}

void engine::scene_graph::GameObject::OnExit()
{
	if (m_wasAwakeCalled)
	{
		m_wasAwakeCalled = false;
		for (ComponentWrapper* wrapper : m_componentWrappers)
		{
			if (wrapper->Get() != nullptr)
				wrapper->Get()->OnExit();
		}
	}
}

void engine::scene_graph::GameObject::OnDestroy()
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
		{
			if(m_wasAwakeCalled)
				wrapper->Get()->OnExit();
			wrapper->Get()->OnDestroy();
		}
	}
	m_scene->GetPhysScene()->DeleteObject(m_physObject);
}

void engine::scene_graph::GameObject::OnActivation()
{
	m_physObject->SetActive(true);
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnActivation();
	}
}

void engine::scene_graph::GameObject::OnDeactivation()
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnDeactivation();
	}
	m_physObject->SetActive(false);
}

bool engine::scene_graph::GameObject::Remove(GameObject* child)
{
	if (child != nullptr)
	{
		auto it{ std::find(m_children.begin(), m_children.end(), child) };
		if (it != m_children.end())
		{
			m_children.erase(it);
			return true;
		}
	}

	return false;
}

bool engine::scene_graph::GameObject::Remove(Component* component)
{
	if (component != nullptr)
	{
		auto it{ m_componentWrappers.begin() };
		auto end{ m_componentWrappers.end() };
		for (; it != end; ++it)
		{
			if ((*it)->Get() == component)
			{
				(*it)->Get()->OnDestroy();
				m_componentWrappers.erase(it);
				delete component;
				return true;
			}
		}
	}

	return false;
}

void engine::scene_graph::GameObject::ClearComponentsList()
{
	for (ComponentWrapper*& wrapper : m_componentWrappers)
	{
		if (wrapper != nullptr)
		{
			delete wrapper;
			wrapper = nullptr;
		}
	}

	m_componentWrappers.clear();
}

void engine::scene_graph::GameObject::DeleteComponentsList()
{
	ClearComponentsList();
	m_componentWrappers.shrink_to_fit();
}

bool engine::scene_graph::GameObject::GetIsActive() const
{
	return m_isActive;
}

const std::string& engine::scene_graph::GameObject::GetName() const
{
	return m_name;
}

engine::scene_graph::Scene* engine::scene_graph::GameObject::GetScene() const
{
	return m_scene;
}

engine::Engine* engine::scene_graph::GameObject::GetEngine() const
{
	return m_engine;
}

engine::scene_graph::GameObject* engine::scene_graph::GameObject::GetParent() const
{
	return m_parent;
}

const std::vector<engine::scene_graph::GameObject*>& engine::scene_graph::GameObject::GetChildren() const
{
	return m_children;
}

Transform* engine::scene_graph::GameObject::GetTransform()
{
	return &m_transform;
}

bool engine::scene_graph::GameObject::IsStatic() const
{
	return m_isStatic;
}

engine::physic::Object** engine::scene_graph::GameObject::GetPhysObject()
{
	return &m_physObject;
}

void engine::scene_graph::GameObject::SetParent(GameObject* parent)
{
	if (m_parent != nullptr)
		m_parent->Remove(this);

	if (parent != nullptr)
	{
		parent->m_children.emplace_back(this);
		m_transform.SetParent(parent->GetTransform());
	}

	else
		m_transform.SetParent(nullptr);

	m_parent = parent;
}

void engine::scene_graph::GameObject::SetIsActive(bool isActive)
{
	m_isActive = isActive;

	isActive ? OnActivation() : OnDeactivation();
}

void engine::scene_graph::GameObject::SetIsStatic(bool isStatic)
{
	m_isStatic = isStatic;
	if (m_physObject != nullptr)
		m_physObject->SetIsStatic(isStatic);
}

void engine::scene_graph::GameObject::OnCollisionEnter(engine::physic::CollisionInfo info)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnCollisionEnter(info);
	}
}

void engine::scene_graph::GameObject::OnCollisionStay(engine::physic::CollisionInfo info)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnCollisionStay(info);
	}
}

void engine::scene_graph::GameObject::OnCollisionExit(engine::physic::CollisionInfo info)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnCollisionExit(info);
	}
}

void engine::scene_graph::GameObject::OnTriggerEnter(engine::physic::TriggerInfo info)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnTriggerEnter(info);
	}
}

void engine::scene_graph::GameObject::OnTriggerStay(engine::physic::TriggerInfo info)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnTriggerStay(info);
	}

}

void engine::scene_graph::GameObject::OnTriggerExit(engine::physic::TriggerInfo info)
{
	for (ComponentWrapper* wrapper : m_componentWrappers)
	{
		if (wrapper->Get() != nullptr)
			wrapper->Get()->OnTriggerExit(info);
	}
}
