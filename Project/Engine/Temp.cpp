#include "pch.h"
#include "Temp.h"

#include "CAssetMgr.h"
#include "CConstBuffer.h"
#include "CDevice.h"
#include "CGraphicShader.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMesh.h"
#include "ptr.h"

#include "CGameObject.h"
#include "CMeshRender.h"
#include "CTransform.h"

CGameObject* pObject = nullptr;

int TempInit()
{
	pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempRelease()
{
	delete pObject;
}

void TempTick()
{
	const float DT = CTimeMgr::GetInst()->GetDeltaTime();

	pObject->tick();
	pObject->finaltick();
}

void TempRender()
{
	pObject->render();
}
