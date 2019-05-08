#ifndef _SCENE_MGR_H_
#define _SCENE_MGR_H_

#include "Scene.h"
#include "../Resource/Folder.h"
#include "../Resource/ResourceMgr.h"

namespace engine
{
	class Engine;

	namespace scene_graph
	{
		class SceneMgr
		{
		public:
			SceneMgr(engine::Engine* engine);
			~SceneMgr();

			// Generates a new persistant Scene.
			Scene* NewScene(resource::Folder* destination);

			// Adds the scene to the build.
			void Add(Scene* scene);
			// Removes the scene from the build.
			void Remove(Scene* scene);
			// Loads the specified Scene.
			void Load(size_t sceneID);
			// Updates the current Scene.
			void Update(float deltaTime);
			void FixedUpdate(float deltaTime);
			void LateUpdate(float deltaTime);
			void Render();

			void AddRenderWin(int winId);
			void RemoveRenderWin(int winId);
			std::vector<int> GetTargetWinIds() const;
		
			engine::Engine* GetEngine();

			void Start();
			void Exit();
			void Pause();
			void UnPause();

			void Close();

			bool IsStarted() const;
			bool IsPaused() const;
		private:
			engine::Engine* m_engine;
			std::vector<int> m_targetWinIds;

			Scene* m_currentScene;
			std::vector<Scene*> m_activeScenes;
			std::vector<Scene*> m_allocatedScenes;
			std::vector<GameObject*> m_dontDetroyOnLoadObjects;

			bool m_started;
			bool m_paused;
		};
	}
}

#endif