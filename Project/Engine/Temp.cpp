#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

// Graphics Pipeline

// =============================
// IA (Input Assembler)
// =============================
// Vertex Buffer
// Index Buffer
// Topology
// Layout

// =============================
// Vertex Shader Stage
// =============================
// 정점을 3차원 모델 좌표계에서 NDC 2차원 좌표로 맵핑

// Tessellation
// - Hull Shader
// - Domain Shader

// Geometry Shader

// =============================
// Rasterizer
// =============================

// =============================
// Pixel Shader
// =============================
// 픽셀 당 호출되는 함수
// 각 픽셀의 색상을 지정해서 랜더타겟에 출력

// =============================
// Output Merge Stage
// =============================
// DepthStencil State 체크
// BlendState

// 최종 출력
// RenderTargetTexture
// DepthStencilTexture

// 정점 정보를 저장하는 버퍼
ComPtr<ID3D11Buffer> g_VB; // VertexBuffer

// 정점 하나를 구성하는 Layout 정보	// VertexShader에서 어떻게 데이터를 받을지.
ComPtr<ID3D11InputLayout> g_Layout;

// System Memory 정점 정보
Vtx g_arrVtx[3] = {};

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
	//   0
	//  / \
	// 2---1

	// Viewport에 0~1 까지 Z 뎁스를 설정했으므로, Z값은 0에서 1 사이여야함
	// 아래 코드 참조
	//viewport.MinDepth = 0;
	//viewport.MaxDepth = 1;

	g_arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	// 정점 버퍼 생성
	D3D11_BUFFER_DESC VBDesc = {};
	VBDesc.ByteWidth = sizeof(Vtx) * 3;
	VBDesc.MiscFlags = 0;

	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// 버퍼가 생성된 이후에 CPU에서 접근해서 GPU에 있는 데이터를
	// 덮어쓰기가 가능하게 설정 - TempTick에서 Map/Unmap을 사용하기 위함.
	// 설정이 안되어있으면 Map/Unmap 실패함
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 버텍스 쉐이더 만들기
	wchar_t szBuffer[255] = {};
	GetCurrentDirectory(255, szBuffer);
	size_t len = wcslen(szBuffer);

	// 하나의 디렉토리 앞 폴더로 이동
	for (int i = len - 1; i > 0; --i)
	{
		if (szBuffer[i] == '\\')
		{
			szBuffer[i] = '\0';
			break;
		}
	}

	wcscat_s(szBuffer, L"\\content\\shader\\std2d.fx");

	if (FAILED(D3DCompileFromFile(
		szBuffer,
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
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;// Vec3과 맞는 사이즈 강제로 맞춤;;; (픽셀 포멧)
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;

	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;// Vec3과 맞는 사이즈 강제로 맞춤;;; (픽셀 포멧)
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
		szBuffer,
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
}

void TempTick()
{
	const float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		for (Vtx& vertex : g_arrVtx)
		{
			vertex.vPos.y += 1.f * DT;
		}
	}
	if (KEY_PRESSED(KEY::S))
	{
		for (Vtx& vertex : g_arrVtx)
		{
			vertex.vPos.y -= 1.f * DT;
		}
	}
	if (KEY_PRESSED(KEY::A))
	{
		for (Vtx& vertex : g_arrVtx)
		{
			vertex.vPos.x -= 1.f * DT;
		}
	}
	if (KEY_PRESSED(KEY::D))
	{
		for (Vtx& vertex : g_arrVtx)
		{
			vertex.vPos.x += 1.f * DT;
		}
	}

	// System Memory에 있던 내용을 GPU로 갱신필요
	// 즉 VertexBuffer에 반영 필요
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	// CPU - GPU 연결
	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, g_arrVtx, sizeof(Vtx) * 3);
	// CPU - GPU 연결 해제
	CONTEXT->Unmap(g_VB.Get(), 0);
}

void TempRender()
{
	const UINT Stride = sizeof(Vtx);
	const UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(
		0,
		1,
		g_VB.GetAddressOf(),
		&Stride,
		&Offset);
	CONTEXT->IASetInputLayout(g_Layout.Get());

	// IA에 보낸 버텍스는 삼각형단위로 묶어서 내부를 칠해라 라는 뜻
	CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	// Draw 하기 전에 세팅만 되면
	// 위에 저 세팅 순서는 상관없다!!
	CONTEXT->Draw(3, 0);
}
