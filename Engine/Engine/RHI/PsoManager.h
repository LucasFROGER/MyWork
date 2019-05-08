#ifndef _PSO_MANAGER_H_
#define _PSO_MANAGER_H_

#include "../../stdafx.h"
#include "Resources/PSO.h"

namespace engine
{
	namespace rhi
	{
		class PsoManager
		{
		public:

			PsoManager(ID3D12Device* device);
			~PsoManager();

			resources::PSO* FindPso(resources::RootSignature* rootSignature, EDrawingType drawingType, std::vector<resources::Shader*> shaderTab, int shaderNb, bool isText);
			resources::PSO* GetPsoByIndex(int index, bool isText) const;

		private:

			ID3D12Device* m_device;
			std::vector<resources::PSO*> m_psos;
			std::vector<resources::PSO*> m_textPsos;
		};
	}
}
#endif
