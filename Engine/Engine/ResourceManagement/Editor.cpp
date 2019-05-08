#include "Editor.h"

#include "..\SceneGraph\GameObject.h"
#include "..\Component\Component.h"
#include "..\Component\MonoBehaviour.h"
#include "..\CustomMonoBehaviour\Fabio.h"
#include "..\CustomMonoBehaviour\Lucas.h"
#include "..\CustomMonoBehaviour\Steve.h"

using namespace engine::resource_management;
using namespace engine::scene_graph;
using namespace engine::resource;
using namespace engine::loader;

Editor::Editor(ResourceMgr* resourceMgr, Explorer* explorer, engine::rhi::RHI* rhi, engine::physic::PhysicMgr* physMgr) :
	m_resourceMgr{ resourceMgr },
	m_explorer{ explorer },
	m_rhi{ rhi },
	m_physMgr{ physMgr }
	//m_mainScene("", rhi, physMgr, nullptr)
{

}

bool Editor::Run()
{
	// while (Application.Run())
	{
		// if (Input.DradAndDrop())
		{
			Importer importer(m_resourceMgr, m_rhi);
			importer.Import("FBX/ironman/ironman.fbx", m_explorer->GetMainFolder());
			importer.Import("FBX/cube01.fbx", m_explorer->GetMainFolder());
			importer.Import("OBJ/chara.obj", m_explorer->GetMainFolder());
			importer.Import("OBJ/Cube.obj", m_explorer->GetMainFolder());
			importer.Import("OBJ/planet.obj", m_explorer->GetMainFolder());
			importer.Import("OBJ/Sphere.obj", m_explorer->GetMainFolder());
			importer.Import("OBJ/test.obj", m_explorer->GetMainFolder());
		}

		// if (Input.CreateEmpty())
		{
			GameObject* originGO = m_mainScene.NewGameObject();
			GameObject* parentGO = m_mainScene.NewGameObject(originGO);
			GameObject* cubeGO = m_mainScene.NewGameObject(parentGO);
		}

		// if (Input.AddComponent())
		{
			// originGO
			//m_mainScene.GetRoot()->GetChildren()[0]->NewComponent<Fabio>();

			// parentGO
			//m_mainScene.GetRoot()->GetChildren()[0]->GetChildren()[0]->NewComponent<Lucas>();

			// cubeGO
			//m_mainScene.GetRoot()->GetChildren()[0]->GetChildren()[0]->GetChildren()[0]->NewComponent<Steve>();
		}

		// if (Input.Play() || isPlaying)
		{
			// isPlaying = true;

			std::cout << "P L A Y" << std::endl;
			for (int i{ 0 }; i < 5; ++i) // temporary
			{
				std::cout << "Frame " << i << std::endl;
				Play();
			}
		}

		// if (Input.Stop())
		{
			// isPlaying = false;
			std::cout << "S T O P" << std::endl;
			Stop();
		}
	}
	return true;
}

bool Editor::Play()
{
	m_mainScene.Update();
	return true;
}

void Editor::Stop()
{
	m_mainScene.Exit();
}