#include "pch.h"
#include "CMeshRender.h"

#include "CGameObject.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CTransform.h"

void CMeshRender::FinalTick()
{
}

void CMeshRender::Render()
{
	// 오브젝트의 위치값을 상수버퍼를 통해서 바인딩
	GetOwner()->Transform()->Binding();

	GetMaterial()->Binding();

	GetMesh()->Render();
}

CMeshRender::CMeshRender() : CRenderComponent(EComponentType::MeshRender)
{
}

CMeshRender::~CMeshRender()
{
}
