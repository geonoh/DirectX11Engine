#include "pch.h"
#include "CAssetMgr.h"

void CAssetMgr::init()
{
	CreateDefaultMesh();

	CreateDefaultTexture();

	CreateDefaultMaterial();

	CreateDefaultGraphicShader();

	CreateDefaultComputeShader();
}

void CAssetMgr::CreateDefaultMesh()
{
	Ptr<CMesh> pMesh = nullptr;

	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// ===================
	// Rect Mesh
	// ===================
	// 0-- 1
	// | \ |
	// 3 --2

	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
	AddAsset<CMesh>(L"RectMesh", pMesh.Get());
	vecVtx.clear();
	vecIdx.clear();

	// ===================
	// Circle Mesh
	// ===================
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

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
	AddAsset<CMesh>(L"CircleMesh", pMesh.Get());
	vecVtx.clear();
	vecIdx.clear();
}

void CAssetMgr::CreateDefaultTexture()
{
}

void CAssetMgr::CreateDefaultMaterial()
{

}

void CAssetMgr::CreateDefaultGraphicShader()
{
}

void CAssetMgr::CreateDefaultComputeShader()
{
}