#include "NewMonoBehaviour.h"

#include "../Fenestration/Inputs/KeyCode.h"

using namespace engine::fenestration;
using namespace engine::fenestration::input::keys;
using namespace engine::resource;
using namespace engine::core::maths;
using namespace engine::component::physic;

NewMonoBehaviour::NewMonoBehaviour(engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	MonoBehaviour(gameObject, engine, this)
{ }

void NewMonoBehaviour::Init()
{ }

void NewMonoBehaviour::Awake()
{ }

void NewMonoBehaviour::Start()
{ }

void NewMonoBehaviour::Update(float deltaTime)
{ }

void NewMonoBehaviour::LateUpdate(float deltaTime)
{ }

void NewMonoBehaviour::Exit()
{ }

void NewMonoBehaviour::OnCollisionEnter(engine::physic::CollisionInfo info)
{ }

void NewMonoBehaviour::OnCollisionStay(engine::physic::CollisionInfo info)
{ }

void NewMonoBehaviour::OnCollisionExit(engine::physic::CollisionInfo info)
{ }

void NewMonoBehaviour::OnTriggerEnter(engine::physic::TriggerInfo info)
{ }

void NewMonoBehaviour::OnTriggerStay(engine::physic::TriggerInfo info)
{ }

void NewMonoBehaviour::OnTriggerExit(engine::physic::TriggerInfo info)
{ }