#ifndef _COMPONENT_WRAPPER_H_
#define _COMPONENT_WRAPPER_H_

#include "Component.h"

namespace engine
{
	namespace component
	{
		class ComponentWrapper
		{
		public:
			//virtual ComponentWrapper* Copy(scene_graph::GameObject* gameObject) const = 0;
			virtual Component* Get() const = 0;
		};
	}
}

#endif