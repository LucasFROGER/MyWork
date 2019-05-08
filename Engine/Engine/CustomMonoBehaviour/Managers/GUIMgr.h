#ifndef _GUIMGR_H_
#define _GUIMGR_H_

#include "../GUI/Menu.h"

class GUIMgr : public engine::component::MonoBehaviour
{
public:
	GUIMgr(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

	void SetInfoTextRenderer(engine::component::TextRenderer* renderer);
	void SetPauseMenu(Menu* menu);

	void SetInfoText(const char* str);
	const char* GetInfoText();

	void OpenPauseMenu();
	void ClosePauseMenu();
	
private:
	engine::component::TextRenderer* m_infoTextRenderer;
	Menu* m_pauseMenu;
};

#endif
