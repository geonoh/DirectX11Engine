#include "pch.h"
#include "CRenderComponent.h"
#include "CMesh.h"
#include "CGraphicShader.h"

void CRenderComponent::SetMesh(Ptr<CMesh> _Mesh)
{
	m_Mesh = _Mesh;
}

void CRenderComponent::SetShader(Ptr<CGraphicShader> _Shader)
{
	m_Shader = _Shader;
}

Ptr<CMesh> CRenderComponent::GetMesh()
{
	return m_Mesh;
}

Ptr<CGraphicShader> CRenderComponent::GetShader()
{
	return m_Shader;
}

CRenderComponent::CRenderComponent(COMPONENT_TYPE _Type) : CComponent(_Type)
{
}

CRenderComponent::~CRenderComponent()
{
}
