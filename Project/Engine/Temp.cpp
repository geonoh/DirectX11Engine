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

Vtx g_arrVtx[3] = {};

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
