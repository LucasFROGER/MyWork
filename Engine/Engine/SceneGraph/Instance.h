#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "GameObject.h"

class Instance
{
public:
	template<typename T>
	static T* Instantiate(GameObject* gameObject);
};

template<typename T>
T* Instance::Instantiate(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return nullptr;

	T* ptr{ gameObject->GetComponent<T>() };
	if (ptr != nullptr && !ptr->MustBeUnique())
		return new T(gameObject);

	return nullptr;
}

#endif