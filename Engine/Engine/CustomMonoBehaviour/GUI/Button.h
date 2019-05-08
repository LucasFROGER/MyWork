#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>
#include <string>

#include "../../Component/MonoBehaviour.h"

#include "../../Engine.h"
#include "../../Fenestration/Window.h"
#include "../../Component/MeshRenderer.h"
#include "../../Component/Physic/SphereCollider.h"
#include "../../Component/Physic/CubeCollider.h"
#include "../../Component/Physic/CapsuleCollider.h"
#include "../../Component/Physic/Rigidbody.h"
#include "../../Component/TextRenderer.h"

class Button : public engine::component::MonoBehaviour
{
public:
	Button(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);
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

	void SetTextRenderer(engine::component::TextRenderer* textRenderers);

	void SetPosition(engine::core::maths::Vec2 pos);
	void SetText(const char* text);
	void SetFunction(std::function<void(void)> function);

	void Select(bool selected);
	void Displayed(bool display);

	void Execute();


private:
	engine::component::TextRenderer* m_textRenderer;
	std::function<void(void)> m_function;
	std::string m_str;
	engine::core::maths::Vec2 m_pos;
	bool m_selected;
	bool m_displayed;
};

#endif
