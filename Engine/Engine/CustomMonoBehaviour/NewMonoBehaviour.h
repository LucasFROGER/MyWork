#ifndef _NEWMONOBEHAVIOUR_H_
#define _NEWMONOBEHAVIOUR_H_

#include "../Component/MonoBehaviour.h"

#include "../Engine.h"
#include "../Fenestration/Window.h"
#include "../Component/MeshRenderer.h"
#include "../Component/Physic/SphereCollider.h"
#include "../Component/Physic/CubeCollider.h"
#include "../Component/Physic/CapsuleCollider.h"
#include "../Component/Physic/Rigidbody.h"

class NewMonoBehaviour : public engine::component::MonoBehaviour
{
public:
	NewMonoBehaviour(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

private:

};

#endif
