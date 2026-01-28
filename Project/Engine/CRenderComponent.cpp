#include "pch.h"
#include "CRenderComponent.h"
#include "CMesh.h"
#include "CGraphicShader.h"
#include "CTexture.h"

void CRenderComponent::SetMesh(Ptr<CMesh> InMesh)
{
	Mesh = InMesh;
}

void CRenderComponent::SetMaterial(Ptr<CMaterial> InMaterial)
{
	Material = InMaterial;
}

Ptr<CMesh> CRenderComponent::GetMesh()
{
	return Mesh;
}

Ptr<CMaterial> CRenderComponent::GetMaterial()
{
	return Material;
}

CRenderComponent::CRenderComponent(const EComponentType Type) : CComponent(Type)
{
}

CRenderComponent::~CRenderComponent()
{
}
