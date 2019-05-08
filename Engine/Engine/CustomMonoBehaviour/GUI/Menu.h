#ifndef _MENU_H_
#define _MENU_H_

#include "Button.h"


class Menu : public engine::component::MonoBehaviour
{
public:
	Menu(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

	void AddButton(Button* button);

	void Open();
	void Close();

private:
	std::vector<Button*> m_buttons;
	engine::component::TextRenderer* m_textRenderer;

	bool m_open;
	int m_selected;
};

#endif
