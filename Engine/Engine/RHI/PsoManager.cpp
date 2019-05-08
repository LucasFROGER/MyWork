#include "PsoManager.h"

engine::rhi::PsoManager::PsoManager(ID3D12Device* device) : m_device { device }
{
}

engine::rhi::PsoManager::~PsoManager()
{
	SAFE_DELETE_VECTOR(m_psos);
}

engine::rhi::resources::PSO* engine::rhi::PsoManager::FindPso(resources::RootSignature* rootSignature, EDrawingType drawingType, std::vector<resources::Shader*> shaderTab, int shaderNb, bool isText)
{
	bool exist = true;
	if (!isText)
	{
		for (unsigned int i{ 0 }; i < m_psos.size(); ++i)
		{
			if (*m_psos[i]->GetRootSignature() == *rootSignature &&
				m_psos[i]->GetDrawingType() == drawingType &&
				 m_psos[i]->GetShaderNb() == shaderNb)
			{
				for (unsigned int j{ 0 }; j < shaderNb; ++j)
				{
					if (*m_psos[i]->GetShaders()[j] != *shaderTab[j])
					{
						exist = false;
					}
				}
				if(exist)
					return m_psos[i];
			}
		}

		resources::PSO* newPSO = new resources::PSO(m_device, rootSignature, drawingType, (const int)m_psos.size(), shaderTab, shaderNb, isText);

		m_psos.push_back(newPSO);
		return newPSO;
	}
	else
	{
		for (unsigned int i{ 0 }; i < m_textPsos.size(); ++i)
		{
			if (*m_textPsos[i]->GetRootSignature() == *rootSignature &&
				m_textPsos[i]->GetDrawingType() == drawingType &&
				m_textPsos[i]->GetShaderNb() == shaderNb)
			{
				for (unsigned int j{ 0 }; j < shaderNb; ++j)
				{
					if (*m_textPsos[i]->GetShaders()[j] != *shaderTab[j])
					{
						exist = false;
					}
				}
				if (exist)
					return m_textPsos[i];
			}
		}

		resources::PSO* newPSO = new resources::PSO(m_device, rootSignature, drawingType, (const int)m_psos.size(), shaderTab, shaderNb, isText);

		m_textPsos.push_back(newPSO);
		return newPSO;
	}
}

engine::rhi::resources::PSO* engine::rhi::PsoManager::GetPsoByIndex(int index, bool isText) const
{
	if(!isText)
		if (index < m_psos.size())
			return m_psos[index];
	else
		if (index < m_textPsos.size())
			return m_textPsos[index];
	
	return nullptr;
}