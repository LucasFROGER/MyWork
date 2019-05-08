#include "TriggerInfo.h"

#include "../../Object/Object.h"

engine::physic::TriggerInfo::TriggerInfo(Object * other) : m_otherObject{ other->GetGameObject() }
{

}
