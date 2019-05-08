#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "../Gameplay/Player.h"

class GameMgr : public engine::component::MonoBehaviour
{
public:
	GameMgr(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

	void SetGuiMgr(GUIMgr* guiMgr);

	void Pause();
	void Resume();

private:
	GUIMgr* m_guiMgr;

	bool m_paused;

	Player* m_player;
	std::vector<Pickable*> m_pickables;
};

#endif
