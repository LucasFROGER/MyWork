#include "Engine.h"

#define FIXED_RATE 0.02f

engine::Engine::Engine(HINSTANCE hInstance, int ShowWnd, const int m_frameBufferSize) :
	m_rhi{ new rhi::RHI(hInstance, ShowWnd, m_frameBufferSize) },
	m_physMgr{ new physic::PhysicMgr() },
	m_resourceMgr{ new resource::ResourceMgr()},
	m_simu{ nullptr },
	m_isRunning{ true },
	m_fixedTimer{ 0.0f }
{
	m_winWrap = new fenestration::WindowsWrapper(m_rhi);
	m_explorer = new resource_management::Explorer(m_resourceMgr);
	m_lightMgr = new engine::light::LightMgr(m_rhi);
	m_sceneMgr = new engine::scene_graph::SceneMgr(this);
}

engine::Engine::~Engine()
{
	m_simu->Exit();
	m_sceneMgr->Close();
	delete m_simu;
	delete m_sceneMgr;
	
	delete m_rhi;
	delete m_winWrap;
	delete m_physMgr;
	delete m_explorer;
	delete m_resourceMgr;
	delete m_lightMgr;
}

bool engine::Engine::Initialization()
{
	if(!m_physMgr->InitializePhysics())
		return false;
	m_simu = new Simulation(this);
	m_simu->Init();
	return true;
}

void engine::Engine::Update()
{
	float deltaTime = static_cast<float>(m_timer.GetFrameDelta());
	m_fixedTimer += deltaTime;

	m_winWrap->Update();
	m_simu->Update();
	if (m_winWrap->GetActiveWindow() != nullptr)
	{
		m_sceneMgr->Update(deltaTime);
		if (m_fixedTimer > FIXED_RATE)
		{
			m_sceneMgr->FixedUpdate(m_fixedTimer);
			m_fixedTimer = 0.0f;
		}
		m_sceneMgr->LateUpdate(deltaTime);
		m_lightMgr->Update();
	}
}

void engine::Engine::Render()
{
	m_sceneMgr->Render();
	m_isRunning = m_rhi->Render();
}

bool engine::Engine::IsRunning()
{
	return m_isRunning;
}

engine::rhi::RHI* engine::Engine::GetRHI() const
{
	return m_rhi;
}

engine::fenestration::WindowsWrapper* engine::Engine::GetWindowsWrapper() const
{
	return m_winWrap;
}

engine::physic::PhysicMgr* engine::Engine::GetPhysicMgr()  const
{
	return m_physMgr;
}

engine::resource::ResourceMgr* engine::Engine::GetResourceMgr() const
{
	return m_resourceMgr;
}

engine::resource_management::Explorer* engine::Engine::GetExplorer() const
{
	return m_explorer;
}

engine::scene_graph::SceneMgr* engine::Engine::GetSceneMgr() const
{
	return m_sceneMgr;
}

engine::light::LightMgr* engine::Engine::GetLightMgr() const
{
	return m_lightMgr;
}

