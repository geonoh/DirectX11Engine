#include "pch.h"
#include "CMeshRender.h"

#include "CGraphicShader.h"
#include "CMesh.h"

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{
	GetShader()->Binding();
	GetMesh()->Render();
}

CMeshRender::CMeshRender() : CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}
