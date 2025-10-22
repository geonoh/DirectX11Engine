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

ComPtr<ID3DBlob> g_ErrBlob; // ���� �޽��� �����

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

	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// ���۰� ������ ���Ŀ� CPU���� �����ؼ� GPU�� �ִ� �����͸�
	// ����Ⱑ �����ϰ� ���� - TempTick���� Map/Unmap�� ����ϱ� ����.
	// ������ �ȵǾ������� Map/Unmap ������
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ���ؽ� ���̴� �����
	wchar_t szBuffer[255] = {};
	GetCurrentDirectory(255, szBuffer);
	size_t len = wcslen(szBuffer);

	// �ϳ��� ���丮 �� ������ �̵�
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
			// ���� ����
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "���ؽ� ���̴� ������ ����", MB_OK);
			return E_FAIL;
		}
		else
		{
			// ��� ����
			MessageBox(nullptr, L"������ ã�� �� �����ϴ�.", L"���ؽ� ���̴� ������ ����", MB_OK);
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

	// �ȼ� ���̴�
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
			// ���� ����
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "�ȼ� ���̴� ������ ����", MB_OK);
			return E_FAIL;
		}
		else
		{
			// ��� ����
			MessageBox(nullptr, L"������ ã�� �� �����ϴ�.", L"�ȼ� ���̴� ������ ����", MB_OK);
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

	// System Memory�� �ִ� ������ GPU�� �����ʿ�
	// �� VertexBuffer�� �ݿ� �ʿ�
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	// CPU - GPU ����
	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, g_arrVtx, sizeof(Vtx) * 3);
	// CPU - GPU ���� ����
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

	// IA�� ���� ���ؽ��� �ﰢ�������� ��� ���θ� ĥ�ض� ��� ��
	CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	// Draw �ϱ� ���� ���ø� �Ǹ�
	// ���� �� ���� ������ �������!!
	CONTEXT->Draw(3, 0);
}
