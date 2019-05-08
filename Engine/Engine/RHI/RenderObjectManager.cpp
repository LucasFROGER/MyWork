#include "RenderObjectManager.h"

engine::rhi::RenderObjectManager::RenderObjectManager(ID3D12Device* device) : m_device{ device }
{}

engine::rhi::RenderObjectManager::~RenderObjectManager()
{
	SAFE_DELETE_VECTOR(m_renderObjectTab);
}

engine::rhi::resources::RenderObject* engine::rhi::RenderObjectManager::FindRenderObject(resources::PSO* pso, resources::RootSignature* rootSignature,
	std::vector<resources::ConstantBuffer*> cb, std::vector<resources::Texture*> textures,
	D3D12_STATIC_SAMPLER_DESC* samplers, int samplerNb,
	float* vertexBuffer, int strideInBytes, int bufferSize,
	int* iList, int ibufferSize, bool isStatic)
{
	for (unsigned int i{ 0 }; i < m_renderObjectTab.size(); ++i)
	{
		if (*m_renderObjectTab[i]->GetPso() == *pso && *m_renderObjectTab[i]->GetRootSignature() == *rootSignature &&
			m_renderObjectTab[i]->GetConstantBuffer() == cb && m_renderObjectTab[i]->GetVList() == vertexBuffer &&
			m_renderObjectTab[i]->GetTextures() == textures)
		{
			return m_renderObjectTab[i];
		}
	}

	resources::RenderObject* newRenderObject = new resources::RenderObject(m_device, pso, rootSignature, cb, textures, samplers, samplerNb, vertexBuffer, strideInBytes, bufferSize, iList, ibufferSize, isStatic, m_renderObjectTab.size());

	m_renderObjectTab.push_back(newRenderObject);
	return newRenderObject;
}

engine::rhi::resources::RenderObject* engine::rhi::RenderObjectManager::GetRenderObjectByIndex(int index) const
{
	if (index < m_renderObjectTab.size() && index >= 0)
		return m_renderObjectTab[index];
	else
		return nullptr;
}