#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <vector>

#include "../Component/Component.h"
#include "../Component/SpecificComponentWrapper.h"
#include "../Fenestration/WindowsWrapper.h"
#include "../Physic/Object/Object.h"

namespace engine
{
	namespace scene_graph
	{
		class Scene;
		class GameObject
		{
		public:
			//GameObject();
			GameObject(Scene* scene, engine::Engine* engine, std::string name, GameObject* parent = nullptr);
			~GameObject();

			void Init();
			void Awake();
			void PreProcess();
			void ContinuousProcess(float deltaTime);
			void Process(float deltaTime);
			void FixedProcess(float deltaTime);
			void LateProcess(float deltaTime);
			void Render();
			void OnExit();
			void OnDestroy();

			void OnActivation();
			void OnDeactivation();

			template<typename T>
			T* NewComponent();

			bool Remove(GameObject* child);
			bool Remove(component::Component* component);
			void ClearComponentsList();
			void DeleteComponentsList();

			bool GetIsActive() const;

			const std::string& GetName() const;
			Scene* GetScene() const;
			engine::Engine* GetEngine() const;
			GameObject* GetParent() const;
			const std::vector<GameObject*>& GetChildren() const;
			engine::physic::Transform* GetTransform();

			bool IsStatic() const;
			template<typename T>
			T* GetComponent() const;
			template<typename T>
			std::vector<T*> GetComponents() const;
			engine::physic::Object** GetPhysObject();
			void SetParent(GameObject* parent);
			void SetIsActive(bool isActive);
			void SetIsStatic(bool isStatic);

			void OnCollisionEnter(engine::physic::CollisionInfo info);
			void OnCollisionStay(engine::physic::CollisionInfo info);
			void OnCollisionExit(engine::physic::CollisionInfo info);

			void OnTriggerEnter(engine::physic::TriggerInfo info);
			void OnTriggerStay(engine::physic::TriggerInfo info);
			void OnTriggerExit(engine::physic::TriggerInfo info);

		private:
			std::string m_name;
			Scene* m_scene; // TODO: Use SceneMgr instead of Scene
			engine::Engine* m_engine;
			GameObject* m_parent;
			std::vector<engine::scene_graph::GameObject*> m_children;
			
			bool m_isStatic;
			engine::physic::Object* m_physObject;

			engine::physic::Transform m_transform;
			bool m_isActive;
			bool m_wasInitCalled;
			bool m_wasAwakeCalled;

			std::vector<component::ComponentWrapper*> m_componentWrappers;
		};



		template<typename T>
		T* GameObject::NewComponent()
		{
			T* ptr{ GetComponent<T>() };
			if (ptr == nullptr || (ptr != nullptr && !ptr->GetMustBeUnique()))
			{
				SpecificComponentWrapper<T>* specificWrapper{ new SpecificComponentWrapper<T>(this, m_engine) };
				m_componentWrappers.emplace_back(specificWrapper);
				return specificWrapper->Get();
			}

			return nullptr;
		}

		template<typename T>
		T* GameObject::GetComponent() const
		{
			for (component::ComponentWrapper* wrapper : m_componentWrappers)
			{
				if (wrapper->Get() != nullptr && wrapper->Get()->GetType() == typeid(T).name())
					return static_cast<T*>(wrapper->Get());
			}

			return nullptr;
		}

		template<typename T>
		std::vector<T*> GameObject::GetComponents() const
		{
			std::vector<T*> components;

			for (component::ComponentWrapper* wrapper : m_componentWrappers)
			{
				if (wrapper->Get() != nullptr && wrapper->Get()->GetType() == typeid(T).name())
					components.push_back(static_cast<T*>(wrapper->Get()));

			
			}
			return components;
		}
	}
}

#endif
