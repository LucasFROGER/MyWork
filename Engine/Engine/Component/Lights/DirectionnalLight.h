#ifndef _COMPONENT_DIRECTIONNALLIGHT_H_
#define _COMPONENT_DIRECTIONNALLIGHT_H_

#include "../../Engine.h"
#include "../Component.h"

namespace engine
{
	namespace component
	{
		namespace light
		{
			class DirectionnalLight final : public Component
			{
			public:
				DirectionnalLight(scene_graph::GameObject* gameObject, engine::Engine* engine);

				engine::Engine* m_engine;

				virtual void Init() override;
				void Awake() override {}
				void PreProcess() override {}
				void Process(float deltaTime) override {}
				void ContinuousProcess(float deltaTime) override {}
				void LateProcess(float deltaTime) override {}
				void Render() override;
				void OnExit() override {}
				void OnDestroy() override;

				void OnActivation() override;
				void OnDeactivation() override;

				void SetDirection(engine::core::maths::Vec3 direction);
				void SetColor(engine::core::maths::Vec4 color);
				void SetIntensity(float intensity);

			private:
				engine::core::maths::Vec3 m_direction;
				engine::core::maths::Vec4 m_color;
				float m_intensity;

				engine::light::Light* m_light;
			};
		}
	}
}

#endif // !_COLLIDER_H_