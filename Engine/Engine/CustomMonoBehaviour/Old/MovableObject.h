#ifndef _MOVABLE_OBJECT_H_
#define _MOVABLE_OBJECT_H_

#include "../../Component/MonoBehaviour.h"

#include "../../Engine.h"
#include "../../Fenestration/Window.h"
#include "../../Component/MeshRenderer.h"
#include "../../Component/Physic/SphereCollider.h"
#include "../../Component/Physic/CubeCollider.h"
#include "../../Component/Physic/CapsuleCollider.h"
#include "../../Component/Physic/Rigidbody.h"

class MovableObject : public engine::component::MonoBehaviour
{
public:
	engine::Engine* m_engine;

	MovableObject(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);

	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Exit() override;

	void SetTransform(engine::core::maths::Vec3 pos, engine::core::maths::Vec3 rot, engine::core::maths::Vec3 scale);
	void Select(bool selected);
	void SetBasicMaterial(engine::resource::Material* basicMaterial);
	void SetSelectedMaterial(engine::resource::Material* selectedMaterial);
	void SetTriggerMaterial(engine::resource::Material* selectedMaterial);
	void SetCollisionMaterial(engine::resource::Material* selectedMaterial);

	void OnCollisionEnter(engine::physic::CollisionInfo info) override;
	void OnCollisionStay(engine::physic::CollisionInfo info) override;
	void OnCollisionExit(engine::physic::CollisionInfo info) override;

	void OnTriggerEnter(engine::physic::TriggerInfo info) override;
	void OnTriggerStay(engine::physic::TriggerInfo info) override;
	void OnTriggerExit(engine::physic::TriggerInfo info) override;

private:
	engine::component::MeshRenderer* m_meshRenderer;

	engine::resource::Material* m_basicMaterial;
	engine::resource::Material* m_selectedMaterial;
	engine::resource::Material* m_triggerMaterial;
	engine::resource::Material* m_collisionMaterial;

	bool m_selected;
	bool m_triggered;
	bool m_collsioned;
};

#endif