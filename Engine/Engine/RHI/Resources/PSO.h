#ifndef _PSO_H_
#define _PSO_H_

#include "Shader.h"
#include "../DrawingTags.h"
#include "RootSignature.h"

namespace engine
{
	namespace rhi
	{
		namespace resources
		{
			class PSO
			{
			public:

				//VERTEX->PIXEL->GEOMETRY->HULL->DOMAIN shader
				PSO(ID3D12Device* device, RootSignature* rootSignature, EDrawingType drawingType, const int id, std::vector<Shader*> shaderTab, int shaderNb, bool isTextPso);
				~PSO();

				ID3D12PipelineState* GetPso() const;
				RootSignature* GetRootSignature();
				Shader* GetVertexShader() const;
				Shader* GetPixelShader() const;
				Shader* GetGeometryShader() const;
				Shader* GetHullShader() const;
				Shader* GetDomainShader() const;
				std::vector<Shader*> GetShaders() const;
				int GetShaderNb() const;
				EDrawingType GetDrawingType() const;
				bool GetIsTextPso() const;
				const int GetId() const;

				void SetPSO(ID3D12PipelineState* newPSO);
				void SetRootSignature(RootSignature* newRS);
				void SetShaderTab(std::vector<Shader*> newST);
				void SetShaderNb(int newShaderNb);
				void SetDrawingType(EDrawingType newDT);

				bool operator==(const PSO& other) const;
				bool operator!=(const PSO& other) const;

			private:

				ID3D12PipelineState* m_pso;
				D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
				RootSignature* m_rootSignature;
				std::vector<Shader*> m_shaderTab;
				int m_shaderNb;
				D3D12_INPUT_ELEMENT_DESC* m_inputLayout;
				EDrawingType m_drawingType;
				bool m_isTextPso;
				const int m_id;

			};
		}
	}
}

#endif