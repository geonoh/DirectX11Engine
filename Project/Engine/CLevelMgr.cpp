#include "pch.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"
#include "CGameObject.h"
#include "CLevel.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"
#include "CTransform.h"

CLevelMgr::CLevelMgr() : CurrentLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if (CurrentLevel)
	{
		delete CurrentLevel;
		CurrentLevel = nullptr;
	}
}

void CLevelMgr::Init()
{
	CurrentLevel = new CLevel();
	
	CGameObject* Object = new CGameObject;
	Object->AddComponent(new CTransform);
	Object->AddComponent(new CMeshRender);
	Object->AddComponent(new CPlayerScript);
	Object->Transform()->SetRelativeScale(.5f, .5f, 0.2f);

	Object->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	Object->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));
	Object->MeshRender()->SetTexture(CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Character.png"));

	CurrentLevel->AddObject(0, Object);
}

void CLevelMgr::Tick()
{
	if (!CurrentLevel)
	{
		return;
	}

	CurrentLevel->Tick();
	CurrentLevel->FinalTick();
}

void CLevelMgr::Render()
{
	if (!CurrentLevel)
	{
		return;
	}

	CurrentLevel->Render();
}
