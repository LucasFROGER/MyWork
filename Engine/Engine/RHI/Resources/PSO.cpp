#include "PSO.h"

engine::rhi::resources::PSO::PSO(ID3D12Device* device, RootSignature* rootSignature, EDrawingType drawingType, const int id, std::vector<Shader*> shaderTab, int shaderNb, bool isTextPso) :
	m_rootSignature{ rootSignature },
	m_drawingType{ drawingType },
	m_shaderTab{ shaderTab },
	m_shaderNb{ shaderNb },
	m_isTextPso{ isTextPso },
	m_id{ id }
{
	HRESULT hr;

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc;
	D3D12_BLEND_DESC BlendStateDesc = {};
	psoDesc = {};
	D3D12_DEPTH_STENCIL_DESC DepthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	if (!m_isTextPso)
	{
		m_inputLayout = new D3D12_INPUT_ELEMENT_DESC[4];
		
		m_inputLayout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
		m_inputLayout[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
		m_inputLayout[2] = { "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
		m_inputLayout[3] = { "TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
		inputLayoutDesc.NumElements = 4;

		BlendStateDesc = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

	}
	else
	{
		m_inputLayout = new D3D12_INPUT_ELEMENT_DESC[3];

		m_inputLayout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
		m_inputLayout[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
		m_inputLayout[2] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };
		inputLayoutDesc.NumElements = 3;

		BlendStateDesc.AlphaToCoverageEnable = FALSE;
		BlendStateDesc.IndependentBlendEnable = FALSE;
		BlendStateDesc.RenderTarget[0].BlendEnable = TRUE;

		BlendStateDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
		BlendStateDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
		BlendStateDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;

		BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
		BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
		BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;

		BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		DepthStencilDesc.DepthEnable = false;
	}

	inputLayoutDesc.pInputElementDescs = m_inputLayout;

	psoDesc.InputLayout = inputLayoutDesc;
	psoDesc.pRootSignature = m_rootSignature->GetRootSignature();
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	switch (shaderNb)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			psoDesc.VS = shaderTab[0]->GetShaderByteCode();
			break;
		}
		case 2:
		{
			psoDesc.VS = shaderTab[0]->GetShaderByteCode();
			psoDesc.PS = shaderTab[1]->GetShaderByteCode();
			break;
		}
		case 3:
		{
			psoDesc.VS = shaderTab[0]->GetShaderByteCode();
			psoDesc.PS = shaderTab[1]->GetShaderByteCode();
			psoDesc.GS = shaderTab[2]->GetShaderByteCode();
			break;
		}
		case 4:
		{
			psoDesc.VS = shaderTab[0]->GetShaderByteCode();
			psoDesc.PS = shaderTab[1]->GetShaderByteCode();
			psoDesc.GS = shaderTab[2]->GetShaderByteCode();
			psoDesc.HS = shaderTab[3]->GetShaderByteCode();
			break;
		}
		case 5:
		{
			psoDesc.VS = shaderTab[0]->GetShaderByteCode();
			psoDesc.PS = shaderTab[1]->GetShaderByteCode();
			psoDesc.GS = shaderTab[2]->GetShaderByteCode();
			psoDesc.HS = shaderTab[3]->GetShaderByteCode();
			psoDesc.DS = shaderTab[4]->GetShaderByteCode();
			break;
		}
		default:
		{
			MessageBox(NULL, L"Error To Much Shaders in RenderObject", L"Error", MB_OK | MB_ICONERROR);
			break;
		}
	}

	switch (drawingType)
	{
		case EDrawingType::DPOINT:
		{
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
			break;
		}
		case EDrawingType::DLINE:
		{
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
			break;
		}
		case EDrawingType::DTRIANGLES:
		{
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			break;
		}
	
		default:
		{
			psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			break;
		}
	}

	DXGI_SAMPLE_DESC sampleDesc = {};
	sampleDesc.Count = 1;

	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc = sampleDesc;
	psoDesc.SampleMask = 0xffffffff;
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = BlendStateDesc;
	psoDesc.DepthStencilState = DepthStencilDesc;
	psoDesc.NumRenderTargets = 1;

	hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pso));
	if (FAILED(hr))
		MessageBox(NULL, L"Error Creating PSO", L"Error", MB_OK | MB_ICONERROR);
}

engine::rhi::resources::PSO::~PSO()
{
	SAFE_RELEASE(m_pso);
	SAFE_DELETE(m_inputLayout);
}

ID3D12PipelineState* engine::rhi::resources::PSO::GetPso() const
{
	return m_pso;
}

engine::rhi::resources::RootSignature* engine::rhi::resources::PSO::GetRootSignature()
{
	return m_rootSignature;
}

engine::rhi::resources::Shader* engine::rhi::resources::PSO::GetVertexShader() const
{
	return m_shaderTab[0];
}

engine::rhi::resources::Shader* engine::rhi::resources::PSO::GetPixelShader() const
{
	return m_shaderTab[1];
}

engine::rhi::resources::Shader* engine::rhi::resources::PSO::GetGeometryShader() const
{
	return m_shaderTab[2];
}

engine::rhi::resources::Shader* engine::rhi::resources::PSO::GetHullShader() const
{
	return m_shaderTab[3];
}

engine::rhi::resources::Shader* engine::rhi::resources::PSO::GetDomainShader() const
{
	return m_shaderTab[4];
}

std::vector<engine::rhi::resources::Shader*> engine::rhi::resources::PSO::GetShaders()const
{
	return m_shaderTab;
}

int engine::rhi::resources::PSO::GetShaderNb() const
{
	return m_shaderNb;
}

engine::rhi::EDrawingType engine::rhi::resources::PSO::GetDrawingType() const
{
	return m_drawingType;
}

bool engine::rhi::resources::PSO::GetIsTextPso() const
{
	return m_isTextPso;
}

const int engine::rhi::resources::PSO::GetId() const
{
	return m_id;
}

void engine::rhi::resources::PSO::SetPSO(ID3D12PipelineState* newPSO)
{
	m_pso = newPSO;
}

void engine::rhi::resources::PSO::SetRootSignature(RootSignature* newRS)
{
	m_rootSignature = newRS;
}
void engine::rhi::resources::PSO::SetShaderTab(std::vector<Shader*> newST)
{
	m_shaderTab = newST;
}

void engine::rhi::resources::PSO::SetShaderNb(int newShaderNb)
{
	m_shaderNb = newShaderNb;
}

void engine::rhi::resources::PSO::SetDrawingType(EDrawingType newDT)
{
	m_drawingType = newDT;
}

bool engine::rhi::resources::PSO::operator==(const PSO& other) const
{
	if (*m_rootSignature == *other.m_rootSignature &&
		m_shaderNb == other.m_shaderNb &&
		m_drawingType == other.m_drawingType &&
		m_isTextPso == other.m_isTextPso)
	{
		for (unsigned int i{ 0 }; i < m_shaderNb; ++i)
		{
			if (*m_shaderTab[i] != *other.m_shaderTab[i])
				return false;
		}
		return true;
	}
	return false;
}

bool engine::rhi::resources::PSO::operator!=(const PSO& other) const
{
	if (*m_rootSignature == *other.m_rootSignature &&
		m_shaderNb == other.m_shaderNb &&
		m_drawingType == other.m_drawingType &&
		m_isTextPso == other.m_isTextPso)
	{
		for (unsigned int i{ 0 }; i < m_shaderNb; ++i)
		{
			if (*m_shaderTab[i] != *other.m_shaderTab[i])
				return false;
		}
		return true;
	}
	return false;
}