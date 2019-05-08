#include "CollisionInfo.h"

#include "../../Object/Object.h"

engine::physic::CollisionInfo::CollisionInfo(Object* other) : m_otherObject{ other->GetGameObject() }
{
}
