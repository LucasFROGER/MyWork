#include "Scene.h"

#include "GameObject.h"
#include "SceneMgr.h"
#include "../Engine.h"

using namespace engine::rhi;

engine::scene_graph::Scene::Scene(const std::string& name, engine::Engine* engine, camera::FreeCamera* camera, SceneMgr* sceneMgr) :
	m_physScene( new engine::physic::Scene(engine->GetPhysicMgr())),
	m_root{ new engine::scene_graph::GameObject(this, engine, "Root") },
	m_sceneMgr{ sceneMgr },
	m_name{ name },
	m_engine{engine },
	m_editorCamera{ camera }, 
	m_simulate{ false }
{

}

engine::scene_graph::Scene::~Scene()
{
	ClearGameObjectsList();

	if (m_root != nullptr)
	{
		delete m_root;
		m_root = nullptr;
	}
	if (m_physScene != nullptr)
	{
		delete m_physScene;
		m_physScene = nullptr;
	}
}

void engine::scene_graph::Scene::Update(float deltaTime)
{
	Init(m_root);
	
	if (m_sceneMgr->IsStarted())
	{
		PreProcess(m_root);
		if (!m_sceneMgr->IsPaused())
		{
			Process(m_root, deltaTime);
		}
	}
	ContinuousProcess(m_root, deltaTime);
	if (m_sceneMgr->IsStarted())
	{
		if (!m_sceneMgr->IsPaused())
		{
			m_physScene->Update(deltaTime);
		}
	}
}

void engine::scene_graph::Scene::FixedUpdate(float deltaTime)
{
	if (m_sceneMgr->IsStarted())
	{
		if (!m_sceneMgr->IsPaused())
		{
			FixedProcess(m_root, deltaTime);
			m_physScene->FixedUpdate(deltaTime);
		}
	}
}

void engine::scene_graph::Scene::LateUpdate(float deltaTime)
{
	if (m_sceneMgr->IsStarted())
	{
		if (!m_sceneMgr->IsPaused())
		{
			m_physScene->LateUpdate(deltaTime);
			LateProcess(m_root, deltaTime);
		}
	}
}

void engine::scene_graph::Scene::Render()
{
	Render(m_root);
}

void engine::scene_graph::Scene::Start()
{
	m_simulate = true;
	m_physScene->Start();
}

void engine::scene_graph::Scene::Exit()
{
	m_simulate = false;
	CallOnExit(m_root);
	m_physScene->Exit();
}

void engine::scene_graph::Scene::Close()
{
	CallOnDestroy(m_root);
}

engine::scene_graph::GameObject* engine::scene_graph::Scene::NewGameObject(std::string name, GameObject* parent)
{
	if (parent == nullptr)
		parent = m_root;

	GameObject* gameObjectPtr{ new GameObject(this, m_engine, name, parent) };
	m_gameObjects.emplace_back(gameObjectPtr);
	return gameObjectPtr;
}

void engine::scene_graph::Scene::Remove(GameObject* gameObject)
{
	if (gameObject == nullptr || gameObject == m_root)
		return;

	CallOnDestroy(gameObject);

	for (GameObject* child : gameObject->GetChildren())
		Remove(child);

	auto it{ std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject) };
	if (it != m_gameObjects.end())
	{
		m_gameObjects.erase(it);
		delete gameObject;
	}
}

void engine::scene_graph::Scene::ClearGameObjectsList()
{
	auto children{ m_root->GetChildren() };
	for (GameObject* child : children)
		ClearGameObjectsList(child);

	m_gameObjects.clear();
}

void engine::scene_graph::Scene::DeleteGameObjectsList()
{
	ClearGameObjectsList();
	m_gameObjects.shrink_to_fit();
}

const std::string& engine::scene_graph::Scene::GetName() const
{
	return m_name;
}

engine::scene_graph::GameObject* engine::scene_graph::Scene::GetRoot() const
{
	return m_root;
}

engine::Engine * engine::scene_graph::Scene::GetEngine() const
{
	return m_engine;
}

engine::camera::Camera* engine::scene_graph::Scene::GetCamera() const
{
	return m_simulate? m_camera : m_editorCamera;
}

std::vector<int> engine::scene_graph::Scene::GetTargetWinIds() const
{
	return m_sceneMgr->GetTargetWinIds();
}

void engine::scene_graph::Scene::SetCamera(camera::Camera* camera)
{
	m_camera = camera;
}

void engine::scene_graph::Scene::SetEditorCamera(engine::camera::FreeCamera* camera)
{
	m_editorCamera = camera;
}

engine::physic::Scene* engine::scene_graph::Scene::GetPhysScene() const
{
	return m_physScene;
}

engine::scene_graph::SceneMgr * engine::scene_graph::Scene::GetSceneMgr()
{
	return m_sceneMgr;
}

bool engine::scene_graph::Scene::IsSimulate() const
{
	return m_simulate;
}

//Scene& Scene::operator=(const Scene& other)
//{
//	*m_root			= *other.m_root;
//
//	m_name			= other.m_name;
//	m_gameObjects	= other.m_gameObjects;
//	m_rhi			= other.m_rhi;
//	m_windowID		= other.m_windowID;
//	m_camera		= other.m_camera;
//
//	return *this;
//}
//
//Scene& Scene::operator=(Scene&& other)
//{
//	delete m_root;
//	m_root = other.m_root;
//	other.m_root = nullptr;
//
//	m_name			= other.m_name;
//	m_gameObjects	= other.m_gameObjects;
//	m_rhi			= other.m_rhi;
//	m_windowID		= other.m_windowID;
//	m_camera		= other.m_camera;
//
//	return *this;
//}

void engine::scene_graph::Scene::Init(GameObject * gameObject)
{
	gameObject->Init();

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			Init(child);
	}
}

void engine::scene_graph::Scene::PreProcess(GameObject* gameObject)
{
	gameObject->PreProcess();

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			PreProcess(child);
	}
}

void engine::scene_graph::Scene::ContinuousProcess(GameObject* gameObject, float deltaTime)
{
	gameObject->ContinuousProcess(deltaTime);

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			ContinuousProcess(child, deltaTime);
	}
}

void engine::scene_graph::Scene::Process(GameObject* gameObject, float deltaTime)
{
	gameObject->Process(deltaTime);

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			Process(child, deltaTime);
	}
}

void engine::scene_graph::Scene::FixedProcess(GameObject * gameObject, float deltaTime)
{
	gameObject->FixedProcess(deltaTime);

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			FixedProcess(child, deltaTime);
	}
}

void engine::scene_graph::Scene::LateProcess(GameObject* gameObject, float deltaTime)
{
	gameObject->LateProcess(deltaTime);

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			LateProcess(child, deltaTime);
	}
}

void engine::scene_graph::Scene::Render(GameObject* gameObject)
{
	gameObject->Render();

	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr && child->GetIsActive())
			Render(child);
	}
}

void engine::scene_graph::Scene::CallOnExit(GameObject* gameObject)
{
	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr)
			CallOnExit(child);
	}

	gameObject->OnExit();
}

void engine::scene_graph::Scene::CallOnDestroy(GameObject* gameObject)
{
	for (GameObject* child : gameObject->GetChildren())
	{
		if (child != nullptr)
			CallOnDestroy(child);
	}

	gameObject->OnDestroy();
}

void engine::scene_graph::Scene::ClearGameObjectsList(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return;

	auto children{ gameObject->GetChildren() };
	for (GameObject* child : children)
		ClearGameObjectsList(child);

	delete gameObject;
}
