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

// HLSL : 쉐이더 버전 C++이라고 생각하면된다
Ptr<CGraphicShader> g_Shader = nullptr;

int TempInit()
{
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	g_Shader = new CGraphicShader;
	g_Shader->CreateVertexShader(strPath, "VS_Std2D");
	g_Shader->CreatePixelShader(strPath, "PS_Std2D");

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
	g_Shader->Binding();

	Ptr<CMesh> pRectMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	if (pRectMesh.Get())
	{
		pRectMesh->Render();
	}
}
