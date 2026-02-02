#include "pch.h"
#include "CLevelMgr.h"

#include "CCameraMoveScript.h"
#include "CAssetMgr.h"
#include "components.h"
#include "CGameObject.h"
#include "CLevel.h"

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
	
	// CameraObject 생성
	CGameObject* MainCameraObject = new CGameObject;
	MainCameraObject->SetName(L"MainCamera");
	MainCameraObject->AddComponent(new CTransform);
	MainCameraObject->AddComponent(new CCamera);
	MainCameraObject->AddComponent(new CCameraMoveScript);
	MainCameraObject->Camera()->SetPriority(0); // 메인 카메라로 설정
	CurrentLevel->AddObject(0, MainCameraObject);

	CGameObject* PlayerObject = new CGameObject;
	PlayerObject->SetName(L"Player"); // 디버깅용 이름 설정
	PlayerObject->AddComponent(new CTransform);
	PlayerObject->AddComponent(new CMeshRender);
	PlayerObject->AddComponent(new CPlayerScript);
	PlayerObject->Transform()->SetRelativePos(0.f, 0.f, 100.f);
	PlayerObject->Transform()->SetRelativeScale(100.f, 100.f, 0.5f);

	PlayerObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	PlayerObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMaterial"));
	//PlayerObject->MeshRender()->GetMaterial()->SetScalarParam(ScalarParam::Int_0, 0);
	//PlayerObject->MeshRender()->GetMaterial()->SetScalarParam(ScalarParam::Vec4_3, Vec4(0, 3.14, 0, 0));
	Matrix Mat;
	Mat._44 = 2.1f;
	PlayerObject->MeshRender()->GetMaterial()->SetScalarParam(ScalarParam::Mat_1, Mat);

	PlayerObject->MeshRender()->GetMaterial()->SetTexParam(
		TextureParam::Texture_0, 
		CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Character.png")
	);

	CurrentLevel->AddObject(0, PlayerObject);
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

CLevel* CLevelMgr::GetCurrentLevel() const
{
	return CurrentLevel;
}
