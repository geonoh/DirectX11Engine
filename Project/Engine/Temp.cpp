#include "pch.h"
#include "Temp.h"

#include "CAssetMgr.h"
#include "CConstBuffer.h"
#include "CDevice.h"
#include "CGraphicShader.h"
#include "CKeyMgr.h"
#include "CMesh.h"
#include "ptr.h"

#include "CGameObject.h"
#include "CMeshRender.h"
#include "CTransform.h"

static CGameObject* Object = nullptr;

int TempInit()
{
	Object = new CGameObject;
	Object->AddComponent(new CTransform);
	Object->AddComponent(new CMeshRender);
	Object->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	Object->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempRelease()
{
	delete Object;
}

void TempTick()
{
	Object->Tick();
	Object->FinalTick();
}

void TempRender()
{
	Object->Render();
}
