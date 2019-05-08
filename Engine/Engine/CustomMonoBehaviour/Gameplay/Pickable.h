#ifndef _PICKABLE_H_
#define _PICKABLE_H_

#include "../Managers/GUIMgr.h"

class Player;

class Pickable : public engine::component::MonoBehaviour
{
public:
	Pickable(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

	void UseGravityWhenPicked(bool useGravity);
	
	bool IsUsingGravityWhenPicked() const;

	void Pick(engine::physic::Transform* transform);
	void Release();

	void Pause(bool pause);
private:
	GUIMgr* m_guiMgr;
	

	engine::component::physic::Rigidbody* m_rigidbody;
	engine::physic::Object** m_physObject;
	engine::physic::Transform* m_parent;
	engine::core::maths::Vec3 m_velocity;
	Player* m_player;

	bool m_paused;
	bool m_picked;
	bool m_triggered;
	bool m_useGravity;
};

#endif