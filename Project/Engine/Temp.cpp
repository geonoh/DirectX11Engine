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
// ������ 3���� �� ��ǥ�迡�� NDC 2���� ��ǥ�� ����

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
// �ȼ� �� ȣ��Ǵ� �Լ�
// �� �ȼ��� ������ �����ؼ� ����Ÿ�ٿ� ���

// =============================
// Output Merge Stage
// =============================
// DepthStencil State üũ
// BlendState

// ���� ���
// RenderTargetTexture
// DepthStencilTexture

// ���� ������ �����ϴ� ����
ComPtr<ID3D11Buffer> g_VB; // VertexBuffer

// ���� �ϳ��� �����ϴ� Layout ����	// VertexShader���� ��� �����͸� ������.
ComPtr<ID3D11InputLayout> g_Layout;

// System Memory ���� ����
Vtx g_arrVtx[3] = {};

// HLSL : ���̴� ���� C++�̶�� �����ϸ�ȴ�

// VertexShader
ComPtr<ID3DBlob> g_VSBlob; // ������ �� ���̴� �ڵ带 �����Ű�� �뵵
ComPtr<ID3D11VertexShader> g_VS; // ����� ���̴� �ڵ带 �̿��ؼ� VS����

// PixelShader
ComPtr<ID3DBlob> g_PSBlob; // ������ �� ���̴� �ڵ带 �����Ű�� �뵵
ComPtr<ID3D11PixelShader> g_PS; // ����� ���̴� �ڵ带 �̿��ؼ� PS����

int TempInit()
{
	//   0
	//  / \
	// 2---1

	// Viewport�� 0~1 ���� Z ������ ���������Ƿ�, Z���� 0���� 1 ���̿�����
	// �Ʒ� �ڵ� ����
	//viewport.MinDepth = 0;
	//viewport.MaxDepth = 1;

	g_arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	// ���� ���� ����
	D3D11_BUFFER_DESC VBDesc = {};
	VBDesc.ByteWidth = sizeof(Vtx) * 3;
	VBDesc.MiscFlags = 0;

	// ���۰� ������ ���Ŀ� CPU���� �����ؼ� GPU�� �ִ� �����͸�
	// ����Ⱑ �����ϰ� ����
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ���ؽ� ���̴� �����

	// ���� ���̾ƿ� ���� ����� (��, Vtx�� ����)
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};

	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;// Vec3�� �´� ������ ������ ����;;; (�ȼ� ����)
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;

	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;// Vec3�� �´� ������ ������ ����;;; (�ȼ� ����)
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
