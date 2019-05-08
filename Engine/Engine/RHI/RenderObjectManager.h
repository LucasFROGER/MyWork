#ifndef _RENDER_OBJECT_MANAGER_H_
#define _RENDER_OBJECT_MANAHER_H_

#include "Resources/RenderObject.h"

namespace engine
{
	namespace rhi
	{
		class RenderObjectManager
		{

		public:

			RenderObjectManager(ID3D12Device* device);
			~RenderObjectManager();

			resources::RenderObject* FindRenderObject(resources::PSO* pso, resources::RootSignature* rootSignature,
				std::vector<resources::ConstantBuffer*> cb, std::vector<resources::Texture*> textures, D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
				float* vertexBuffer, int strydeInBytes, int bufferSize,
				int* iList, int ibufferSize, bool isStatic);
			resources::RenderObject* GetRenderObjectByIndex(int index)const;

		private:

			ID3D12Device* m_device;
			std::vector<resources::RenderObject*> m_renderObjectTab;


		};
	}
}
#endif
