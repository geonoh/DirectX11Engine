#include "pch.h"
#include "CRenderComponent.h"
#include "CMesh.h"
#include "CGraphicShader.h"

void CRenderComponent::SetMesh(const Ptr<CMesh>& InMesh)
{
	Mesh = InMesh;
}

void CRenderComponent::SetShader(const Ptr<CGraphicShader>& InShader)
{
	Shader = InShader;
}

Ptr<CMesh> CRenderComponent::GetMesh()
{
	return Mesh;
}

Ptr<CGraphicShader> CRenderComponent::GetShader()
{
	return Shader;
}

CRenderComponent::CRenderComponent(const EComponentType Type) : CComponent(Type)
{
}

CRenderComponent::~CRenderComponent()
{
}
