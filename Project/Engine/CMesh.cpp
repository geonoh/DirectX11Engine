#include "pch.h"
#include "CMesh.h"
#include "CDevice.h"

int CMesh::Create(const Vtx* _VtxSysMem, const size_t _VtxCount, const UINT* _IdxSysMem, const size_t _IdxCount)
{
	m_VtxCount = _VtxCount;
	// Create Vertex Buffer
	m_VBDesc.ByteWidth = sizeof(Vtx) * _VtxCount;
	m_VBDesc.MiscFlags = 0;

	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = _VtxSysMem;

	if (FAILED(DEVICE->CreateBuffer(&m_VBDesc, &SubDesc, m_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	m_IdxCount = _IdxCount;
	// Create Index Buffer
	m_IBDesc.ByteWidth = sizeof(UINT) * _IdxCount;
	m_IBDesc.MiscFlags = 0;

	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA IbSubDesc = {};
	IbSubDesc.pSysMem = _IdxSysMem;

	if (FAILED(DEVICE->CreateBuffer(&m_IBDesc, &IbSubDesc, m_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SysMem 유지
	m_VtxSysMem = new Vtx[m_VtxCount];
	memcpy(m_VtxSysMem, _VtxSysMem, sizeof(Vtx) * m_VtxCount);
	m_IdxSysMem = new UINT[m_IdxCount];
	memcpy(m_IdxSysMem, _IdxSysMem, sizeof(UINT) * m_IdxCount);

	return S_OK;
}

void CMesh::Binding()
{
	constexpr UINT Stride = sizeof(Vtx);
	constexpr UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(
		0,
		1,
		m_VB.GetAddressOf(),
		&Stride,
		&Offset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT/*4바이트 포멧*/, 0);
}

void CMesh::Render()
{
	Binding();
	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}

CMesh::CMesh()
	: CAsset(ASSET_TYPE::MESH), m_VBDesc(), m_VtxCount(0), m_VtxSysMem(nullptr), m_IBDesc(), m_IdxCount(0),
	  m_IdxSysMem(nullptr)
{
}

CMesh::~CMesh()
{
	if (m_VtxSysMem)
	{
		delete[] m_VtxSysMem;
		m_VtxSysMem = nullptr;
	}

	if (m_IdxSysMem)
	{
		delete[] m_IdxSysMem;
		m_IdxSysMem = nullptr;
	}
}
