#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Physic/PhysicMgr.h"
#include "../Camera/FreeCamera.h"
#include "../RHI/RHI.h"
#include "GameObject.h"
#include "../Physic/Scene/Scene.h"

namespace engine
{
	class Engine;
	namespace scene_graph
	{
		class SceneMgr;
		class Scene
		{
		public:
			Scene(const std::string& name, engine::Engine* engine, camera::FreeCamera* camera, SceneMgr* sceneMgr);
			~Scene();

			void Update(float deltaTime);
			void FixedUpdate(float deltaTime);
			void LateUpdate(float deltaTime);
			void Render();
			void Start();
			void Exit();
			void Close();

			GameObject* NewGameObject(std::string name, GameObject* parent = nullptr);
			void Remove(GameObject* gameObject);
			void ClearGameObjectsList();
			void DeleteGameObjectsList();

			const std::string& GetName() const;
			GameObject* GetRoot() const;
			engine::Engine* GetEngine() const;
			camera::Camera* GetCamera() const;
			std::vector<int> GetTargetWinIds() const;
			template<typename T>
			std::vector<T*> FindAllObjectsOfType() const;
			template<typename T>
			T* FindObjectOfType() const;
			void SetCamera(camera::Camera* camera);
			void SetEditorCamera(camera::FreeCamera* camera);
			engine::physic::Scene* GetPhysScene() const;
			SceneMgr* GetSceneMgr();

			bool IsSimulate() const;
		private:
			bool m_simulate;

			SceneMgr* m_sceneMgr;
			std::string m_name;
			std::vector<GameObject*> m_gameObjects; // Allocated GameObjects
			GameObject* m_root;
			engine::Engine* m_engine;
			camera::FreeCamera* m_editorCamera;
			camera::Camera* m_camera;

			engine::physic::Scene* m_physScene;

			std::vector<int> m_targetWinId;

			void Init(GameObject* gameObject);
			void PreProcess(GameObject* gameObject);
			void ContinuousProcess(GameObject* gameObject, float deltaTime);
			void Process(GameObject* gameObject, float deltaTime);
			void FixedProcess(GameObject* gameObject, float deltaTime);
			void LateProcess(GameObject* gameObject, float deltaTime);
			void Render(GameObject* gameObject);
			void CallOnExit(GameObject* gameObject);
			void CallOnDestroy(GameObject* gameObject);

			void ClearGameObjectsList(GameObject* child);
		};
		
		template<typename T>
		std::vector<T*> Scene::FindAllObjectsOfType() const
		{
			std::vector<T*> objects;

			for (engine::scene_graph::GameObject* obj : m_gameObjects)
			{
				std::vector<T*> components = obj->GetComponents<T>();
				for (int i{ 0 }; i < components.size(); ++i)
				{
					objects.push_back(components[i]);
				}
			/*	T* component = obj->GetComponent<T>();
				if(component)
					objects.push_back(component);*/
			}
			return objects;
		}

		template<typename T>
		T* Scene::FindObjectOfType() const
		{
			for (engine::scene_graph::GameObject* obj : m_gameObjects)
			{
				T* component = obj->GetComponent<T>();
				if (component)
					return component;
			}
			return nullptr;
		}

	}
}

#endif