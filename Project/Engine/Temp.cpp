#include "pch.h"
#include "Temp.h"

#include "CAssetMgr.h"
#include "CConstBuffer.h"
#include "CDevice.h"
#include "CGraphicShader.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CMesh.h"
#include "ptr.h"

// 물체의 위치, 크기, 회전
tTransform g_Trans = {};

int TempInit()
{
	return S_OK;
}

void TempRelease()
{
	//if (g_RectMesh)
	//{
	//	delete g_RectMesh;
	//	g_RectMesh = nullptr;
	//}
	//
	//if (g_CircleMesh)
	//{
	//	delete g_CircleMesh;
	//	g_CircleMesh = nullptr;
	//}
	//
	//if (g_Shader)
	//{
	//	delete g_Shader;
	//	g_Shader = nullptr;
	//}
}

void TempTick()
{
	const float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		g_Trans.Position.y += DT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		g_Trans.Position.y -= DT;

	}
	if (KEY_PRESSED(KEY::A))
	{
		g_Trans.Position.x -= DT;

	}
	if (KEY_PRESSED(KEY::D))
	{
		g_Trans.Position.x += DT;
	}

	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Trans);
	pCB->Binding();
}

void TempRender()
{
	Ptr<CGraphicShader> pShader = CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader");
	pShader->Binding();

	Ptr<CMesh> pRectMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	if (pRectMesh.Get())
	{
		pRectMesh->Render();
	}
}
