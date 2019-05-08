#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <vector>
#include "DirectionnalLight.h"
#include "PointLight.h"
#include "LightsBuffer.h"

namespace engine
{
	namespace rhi { class RHI; }
	namespace light
	{
		class LightMgr
		{
		public:
			LightMgr(engine::rhi::RHI* rhi);
			~LightMgr();

			void Update();

			LightsBuffer& GetLightData();
			Light* AddDirectionalLight(engine::core::maths::Vec3 direction, engine::core::maths::Vec4 color, float intensity);
			Light* AddPointLight(engine::core::maths::Vec3 position, engine::core::maths::Vec4 color, float intensity);

			void DeleteLight(Light* light);
			void DeleteLight(int id);
			void ClearLights();
			//void SampleShadowMap(bool sample);
			void SetAmbientColor(engine::core::maths::Vec4 color);

			int GetLightBufferID() const;

		private:
			engine::rhi::RHI* m_rhi;

			LightsBuffer m_lightBuff;
			int m_lightBufferID;
		};
	}
}
#endif // !_LIGHTMGR_H_
