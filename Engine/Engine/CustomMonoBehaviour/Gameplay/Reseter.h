#ifndef _RESETER_H_
#define _RESETER_H_

#include "../../Component/MonoBehaviour.h"

class Player;
class Pickable;
class Trap;

class Reseter : public engine::component::MonoBehaviour
{
public:
	Reseter(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
	void Init() override;
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Exit() override;

	void Reset();

private:
	engine::physic::Transform m_save;
	Pickable* m_pickable;
	Player* m_player;
	Trap* m_trap;
};

#endif

