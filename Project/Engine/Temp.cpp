#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

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

	// 버퍼가 생성된 이후에 CPU에서 접근해서 GPU에 있는 데이터를
	// 덮어쓰기가 가능하게 설정
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 버텍스 쉐이더 만들기

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
	LayoutDesc[1].SemanticIndex = 1;


	//DEVICE->CreateInputLayout(LayoutDesc, 2, );

	return S_OK;
}

void TempRelease()
{
}

void TempTick()
{
}

void TempRender()
{
}
