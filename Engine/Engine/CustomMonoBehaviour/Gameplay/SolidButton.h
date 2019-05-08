#ifndef _SOLIDBUTTON_H_
#define _SOLIDBUTTON_H_

#include "../../Component/MonoBehaviour.h"

#include "../../Engine.h"
#include "../../Fenestration/Window.h"
#include "../../Component/MeshRenderer.h"
#include "../../Component/Physic/SphereCollider.h"
#include "../../Component/Physic/CubeCollider.h"
#include "../../Component/Physic/CapsuleCollider.h"
#include "../../Component/Physic/Rigidbody.h"

class SolidButton : public engine::component::MonoBehaviour
{
public:
	SolidButton(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
	void Init() override;
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Exit() override;

	void OnCollisionEnter(engine::physic::CollisionInfo info) override;
	void OnCollisionStay(engine::physic::CollisionInfo info) override;
	void OnCollisionExit(engine::physic::CollisionInfo info) override;

	void OnTriggerEnter(engine::physic::TriggerInfo info) override;
	void OnTriggerStay(engine::physic::TriggerInfo info) override;
	void OnTriggerExit(engine::physic::TriggerInfo info) override;

	void SetCompletedMaterial(engine::resource::Material* mat);
	void Reset();

private:
	engine::component::MeshRenderer* m_meshRenderer;
	engine::resource::Material* m_completeMaterial;
	engine::resource::Material* m_material;

	bool m_completed;
};

#endif
