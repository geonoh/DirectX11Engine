#include "pch.h"
#include "CMeshRender.h"

#include "CGraphicShader.h"
#include "CMesh.h"

void CMeshRender::FinalTick()
{
}

void CMeshRender::Render()
{
	GetShader()->Binding();
	GetMesh()->Render();
}

CMeshRender::CMeshRender() : CRenderComponent(EComponentType::MeshRender)
{
}

CMeshRender::~CMeshRender()
{
}
