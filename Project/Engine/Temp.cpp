#include "pch.h"
#include "Temp.h"

#include "CConstBuffer.h"
#include "CDevice.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CMesh.h"

// Mesh
CMesh* g_RectMesh = nullptr;
CMesh* g_CircleMesh = nullptr;

// 정점 정보를 저장하는 버퍼
ComPtr<ID3D11Buffer> g_VB; // VertexBuffer

// 정점 버퍼내에서 사용할 정점을 가리키는 인덱스 정보를 저장하는 버퍼
ComPtr<ID3D11Buffer> g_IB; // IndexBuffer

// 정점 하나를 구성하는 Layout 정보	// VertexShader에서 어떻게 데이터를 받을지.
ComPtr<ID3D11InputLayout> g_Layout;

// System Memory 정점 정보
Vtx g_arrVtx[4] = {};

// 물체의 위치, 크기, 회전
tTransform g_Trans = {};

// HLSL : 쉐이더 버전 C++이라고 생각하면된다

// VertexShader
ComPtr<ID3DBlob> g_VSBlob; // 컴파일 한 쉐이더 코드를 저장시키는 용도
ComPtr<ID3D11VertexShader> g_VS; // 저장된 쉐이더 코드를 이용해서 VS생성

// PixelShader
ComPtr<ID3DBlob> g_PSBlob; // 컴파일 한 쉐이더 코드를 저장시키는 용도
ComPtr<ID3D11PixelShader> g_PS; // 저장된 쉐이더 코드를 이용해서 PS생성

ComPtr<ID3DBlob> g_ErrBlob; // 에러 메시지 저장용

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

	// 버텍스 쉐이더
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	if (FAILED(D3DCompileFromFile(
		strPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS_Std2D",
		"vs_5_0",
		D3DCOMPILE_DEBUG,
		0,
		g_VSBlob.GetAddressOf(),
		g_ErrBlob.GetAddressOf())))
	{
		if (nullptr != g_ErrBlob)
		{
			// 문법 오류
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "버텍스 쉐이더 컴파일 오류", MB_OK);
			return E_FAIL;
		}
		else
		{
			// 경로 오류
			MessageBox(nullptr, L"파일을 찾을 수 없습니다.", L"버텍스 쉐이더 컴파일 오류", MB_OK);
			return E_FAIL;
		}
	}

	if (FAILED(DEVICE->CreateVertexShader(
		g_VSBlob->GetBufferPointer(), 
		g_VSBlob->GetBufferSize(),
		nullptr, 
		g_VS.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 정점 레이아웃 정보 만들기 (즉, Vtx의 구조)
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};

	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;// Vec3과 맞는 사이즈 강제로 맞춤;;; Vtx::vPos
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;

	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;// Vec4과 맞는 사이즈 강제로 맞춤, Vtx::vColor
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;
	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;

	if (FAILED(DEVICE->CreateInputLayout(
		LayoutDesc,
		2,
		g_VSBlob->GetBufferPointer(),
		g_VSBlob->GetBufferSize(),
		g_Layout.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 픽셀 쉐이더
	if (FAILED(D3DCompileFromFile(
		strPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS_Std2D",
		"ps_5_0",
		D3DCOMPILE_DEBUG,
		0,
		g_PSBlob.GetAddressOf(),
		g_ErrBlob.GetAddressOf())))
	{
		if (nullptr != g_ErrBlob)
		{
			// 문법 오류
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "픽셀 쉐이더 컴파일 오류", MB_OK);
			return E_FAIL;
		}
		else
		{
			// 경로 오류
			MessageBox(nullptr, L"파일을 찾을 수 없습니다.", L"픽셀 쉐이더 컴파일 오류", MB_OK);
			return E_FAIL;
		}
	}

	if (FAILED(DEVICE->CreatePixelShader(
		g_PSBlob->GetBufferPointer(),
		g_PSBlob->GetBufferSize(),
		nullptr,
		g_PS.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void TempRelease()
{
	if (g_RectMesh)
	{
		delete g_RectMesh;
		g_RectMesh = nullptr;
	}

	if (g_CircleMesh)
	{
		delete g_CircleMesh;
		g_CircleMesh = nullptr;
	}
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

	// System Memory에 있던 내용을 GPU로 갱신필요
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Trans);
	pCB->Binding();
}

void TempRender()
{
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	//g_RectMesh->Render();
	g_CircleMesh->Render();
}
