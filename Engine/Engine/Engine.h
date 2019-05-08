#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "RHI/RHI.h"
#include "Lights/LightMgr.h"
#include "Fenestration/WindowsWrapper.h"
#include "Physic/PhysicMgr.h"
#include "Resource/ResourceMgr.h"
#include "ResourceManagement/Explorer.h"
#include "SceneGraph/SceneMgr.h"
#include "../Simulation.h"
#include "Utils/Timer.h"

namespace engine
{
	class Engine
	{
	public:
		Engine(HINSTANCE hInstance, int ShowWnd, const int m_frameBufferSize);
		~Engine();

		bool Initialization();
		void Update();
		void Render();
		bool IsRunning();

		rhi::RHI* GetRHI() const;
		fenestration::WindowsWrapper* GetWindowsWrapper() const;
		physic::PhysicMgr* GetPhysicMgr() const;
		resource::ResourceMgr* GetResourceMgr() const;
		resource_management::Explorer* GetExplorer() const;
		scene_graph::SceneMgr* GetSceneMgr() const;
		light::LightMgr* GetLightMgr() const;

	private:
		rhi::RHI* m_rhi;
		fenestration::WindowsWrapper* m_winWrap;
		physic::PhysicMgr* m_physMgr;
		resource::ResourceMgr* m_resourceMgr;
		resource_management::Explorer* m_explorer;
		scene_graph::SceneMgr* m_sceneMgr;
		light::LightMgr* m_lightMgr;
		utils::Timer m_timer;
		bool m_isRunning;
		float m_fixedTimer;
		Simulation* m_simu;
	};
}

#endif
