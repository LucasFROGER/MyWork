#ifndef _SPECIFIC_COMPONENT_WRAPPER_H_
#define _SPECIFIC_COMPONENT_WRAPPER_H_

#include "ComponentWrapper.h"

namespace engine
{
	namespace component
	{
		template<typename T>
		class SpecificComponentWrapper : public ComponentWrapper
		{
		public:
			template<typename... Args>
			SpecificComponentWrapper(Args&&... args) :
				m_component{ new T(std::forward<Args>(args)...) }
			{}
			~SpecificComponentWrapper() { delete m_component; }

			//SpecificComponentWrapper<T>* Copy(scene_graph::GameObject* gameObject) const override { return new SpecificComponentWrapper<T>(gameObject, *m_component); }

			T* Get() const override { return m_component; }

		private:
			T * m_component;
		};
	}
}

#endif