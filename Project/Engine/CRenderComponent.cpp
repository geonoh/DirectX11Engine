#include "pch.h"
#include "CRenderComponent.h"
#include "CMesh.h"
#include "CGraphicShader.h"
#include "CTexture.h"

void CRenderComponent::SetMesh(Ptr<CMesh> InMesh)
{
	Mesh = InMesh;
}

void CRenderComponent::SetShader(Ptr<CGraphicShader> InShader)
{
	Shader = InShader;
}

void CRenderComponent::SetTexture(Ptr<CTexture> InTexture)
{
	Texture = InTexture;
}

Ptr<CMesh> CRenderComponent::GetMesh()
{
	return Mesh;
}

Ptr<CGraphicShader> CRenderComponent::GetShader()
{
	return Shader;
}

Ptr<CTexture> CRenderComponent::GetTexture()
{
	return Texture;
}

CRenderComponent::CRenderComponent(const EComponentType Type) : CComponent(Type)
{
}

CRenderComponent::~CRenderComponent()
{
}
