#include "pch.h"
#include "Temp.h"

#include "CConstBuffer.h"
#include "CDevice.h"
#include "CGraphicShader.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CMesh.h"
#include "ptr.h"

// Mesh
Ptr<CMesh> g_RectMesh = nullptr;
Ptr<CMesh> g_CircleMesh = nullptr;

// System Memory 정점 정보
Vtx g_arrVtx[4] = {};

// 물체의 위치, 크기, 회전
tTransform g_Trans = {};

// HLSL : 쉐이더 버전 C++이라고 생각하면된다
Ptr<CGraphicShader> g_Shader = nullptr;

int TempInit()
{
	// ===================
	// Rect Mesh
	// ===================
	// 0-- 1
	// | \ |
	// 3 --2

	g_arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	UINT arrIdx[6] = { 0,2,3,0,1,2 };
	g_RectMesh = new CMesh;
	g_RectMesh->Create(g_arrVtx, 4, arrIdx, 6);

	// ===================
	// Circle Mesh
	// ===================
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	Vtx firstVtx;
	firstVtx.vPos = Vec3(0.f, 0.f, 0.f);
	firstVtx.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(firstVtx);

	const float Radius = 0.5f;
	const UINT Slice = 60;
	float AngleStep = (2 * XM_PI) / Slice;

	float Angle = 0.f;
	for (int i = 0; i <= Slice; ++i)
	{
		Vtx v;
		v.vPos = Vec3(cosf(Angle) * Radius, sinf(Angle) * Radius, 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);

		Angle += AngleStep;
	}

	for (int i = 0; i <= Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	g_CircleMesh = new CMesh;
	g_CircleMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());

	g_Shader = new CGraphicShader;
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";
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
	g_CircleMesh->Render();
}
