#include "Component.h"

#include "../Physic/Transform/Transform.h"
#include "../SceneGraph/GameObject.h"

 engine::component::Component::Component(bool mustBeUnique, const std::string& type, engine::scene_graph::GameObject* gameObject, engine::Engine* engine) :
	m_mustBeUnique{ mustBeUnique },
	m_type{ type },
	m_gameObject{ gameObject },
	m_transform{ gameObject->GetTransform() },
	m_engine{ engine },
	m_isEnable{ true }
{}

bool engine::component::Component::GetMustBeUnique() const
{
	return m_mustBeUnique;
}

const std::string& engine::component::Component::GetType() const
{
	return m_type;
}

engine::scene_graph::GameObject* engine::component::Component::GetGameObject() const
{
	return m_gameObject;
}

engine::physic::Transform * engine::component::Component::GetTransform() const
{
	return m_transform;
}

bool engine::component::Component::GetIsEnable() const
{
	return m_isEnable;
}

void engine::component::Component::SetIsEnable(bool isEnable)
{
	m_isEnable = isEnable;
}
