#ifndef _OBJECT_MOVER_H_
#define _OBJECT_MOVER_H_

#include "../../Component/MonoBehaviour.h"

#include "MovableObject.h"
#include "../../Engine.h"

class ObjectMover : public engine::component::MonoBehaviour
{
public:
	std::vector<MovableObject*> m_movableObjects;
	engine::Engine* m_engine;

	ObjectMover(engine::scene_graph::GameObject* gameObject, engine::Engine* engine);

	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Exit() override;

private:
	MovableObject* m_currentObject;
	float m_speed;
	int m_choose;
};

#endif