#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Pickable.h"

class Player : public engine::component::MonoBehaviour
{
public:
	Player(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

	void Pick(Pickable* pickable);
	void ReleasePickable();

	bool GotPickable();
	bool CheckPickable(Pickable* pickable);

	void SetSpeed(float speed);
	void Pause(bool pause);
private:
	GUIMgr* m_guiMgr;

	engine::physic::Transform m_head;
	engine::component::MeshRenderer* m_meshRenderer;
	engine::camera::FreeCamera* m_camera;
	engine::component::physic::Rigidbody* m_rigidbody;
	engine::physic::Object** m_physObject;
	Pickable* m_pickable;

	bool m_paused;
	float m_speed;
	float m_rotSpeed;
	float m_jumpHeight;
	float m_pickDistance;
	engine::core::maths::Vec3 m_velocity;
};

#endif