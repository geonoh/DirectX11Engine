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
#include "CPlayerScript.h"
#include "CTransform.h"

static CGameObject* Object = nullptr;
static CGameObject* Object2 = nullptr;

int TempInit()
{
	Object = new CGameObject;
	Object->AddComponent(new CTransform);
	Object->AddComponent(new CMeshRender);
	Object->AddComponent(new CPlayerScript);
	Object->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);

	Object->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	Object->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	Object2 = new CGameObject;
	Object2->AddComponent(new CTransform);
	Object2->AddComponent(new CMeshRender);
	Object2->Transform()->SetRelativeScale(0.5f, 0.5f, 0.5f);

	Object2->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	Object2->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempRelease()
{
	delete Object;
	delete Object2;
}

void TempTick()
{
	Object->Tick();
	Object2->Tick();
	Object->FinalTick();
	Object2->FinalTick();
}

void TempRender()
{
	Object->Render();
	Object2->Render();
}
