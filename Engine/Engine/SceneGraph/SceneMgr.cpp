#include "SceneMgr.h"

#include "../Loader/Extractor.h"

using namespace engine::loader;
using namespace engine::resource;

engine::scene_graph::SceneMgr::SceneMgr(engine::Engine* engine) :
	m_engine{ engine },
	m_targetWinIds{  },
	m_paused{ false },
	m_started{ false }
{}

engine::scene_graph::SceneMgr::~SceneMgr()
{
	for (engine::scene_graph::Scene*& scenePtr : m_allocatedScenes)
	{
		if (scenePtr != nullptr)
		{
			delete scenePtr;
			scenePtr = nullptr;
		}
	}
}

engine::scene_graph::Scene* engine::scene_graph::SceneMgr::NewScene(Folder* destination)
{
	if (destination == nullptr)
		return nullptr;

	std::string name;
	Extractor::FindValidSceneName(name, destination);

	Scene* scenePtr{ new Scene(name, m_engine, nullptr, this) };
	m_allocatedScenes.emplace_back(scenePtr);
	destination->Add(scenePtr);

	return scenePtr;
}

void engine::scene_graph::SceneMgr::Add(engine::scene_graph::Scene* scene)
{
	if (scene == nullptr)
		return;

	auto it{ std::find(m_activeScenes.begin(), m_activeScenes.end(), scene) };
	if (it == m_activeScenes.end())
		m_activeScenes.emplace_back(scene);
}

void engine::scene_graph::SceneMgr::Remove(engine::scene_graph::Scene* scene)
{
	if (scene == nullptr)
		return;

	auto it{ std::find(m_activeScenes.begin(), m_activeScenes.end(), scene) };
	if (it != m_activeScenes.end())
		m_activeScenes.erase(it);
}

void engine::scene_graph::SceneMgr::Load(size_t id)
{
	if (id < m_activeScenes.size())
	{
		if (m_started)
			m_currentScene->Exit();
		int i{ 0 };
		m_currentScene = m_activeScenes[id];

		if (m_started)
			m_currentScene->Start();
	}
}

void engine::scene_graph::SceneMgr::Update(float deltaTime)
{
	if (m_currentScene != nullptr)
		m_currentScene->Update(deltaTime);
}

void engine::scene_graph::SceneMgr::FixedUpdate(float deltaTime)
{
	if (m_currentScene != nullptr)
		m_currentScene->FixedUpdate(deltaTime);
}

void engine::scene_graph::SceneMgr::LateUpdate(float deltaTime)
{
	if (m_currentScene != nullptr)
		m_currentScene->LateUpdate(deltaTime);
}

void engine::scene_graph::SceneMgr::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}

void engine::scene_graph::SceneMgr::AddRenderWin(int winId)
{
	for (size_t i = 0; i < m_targetWinIds.size(); i++)
		if (m_targetWinIds[i] == winId)
			return;
	m_targetWinIds.push_back(winId);
}

void engine::scene_graph::SceneMgr::RemoveRenderWin(int winId)
{
	for (size_t i = 0; i < m_targetWinIds.size(); i++)
	{
		if (m_targetWinIds[i] == winId)
		{
			m_targetWinIds.erase(m_targetWinIds.begin() + i);
		}
	}
}

std::vector<int> engine::scene_graph::SceneMgr::GetTargetWinIds() const
{
	return m_targetWinIds;
}

void engine::scene_graph::SceneMgr::Start()
{
	m_started = true;
	if (m_currentScene != nullptr)
		m_currentScene->Start();
}

void engine::scene_graph::SceneMgr::Exit()
{
	m_started = false;
	if (m_currentScene != nullptr)
		m_currentScene->Exit();
}

void engine::scene_graph::SceneMgr::Pause()
{
	m_paused = true;
}

void engine::scene_graph::SceneMgr::UnPause()
{
	m_paused = false;
}

void engine::scene_graph::SceneMgr::Close()
{
	if (m_currentScene != nullptr)
		m_currentScene->Close();
}

bool engine::scene_graph::SceneMgr::IsStarted() const
{
	return m_started;
}

bool engine::scene_graph::SceneMgr::IsPaused() const
{
	return m_paused;
}
