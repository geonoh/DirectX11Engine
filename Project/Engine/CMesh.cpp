#include "pch.h"
#include "CMesh.h"
#include "CDevice.h"

int CMesh::Create(const Vtx* InVertexSystemMemory, const size_t InVertexCount, const UINT* InIndexSystemMemory,
                  const size_t InIndexCount)
{
	VertexCount = InVertexCount;
	// Create Vertex Buffer
	VertexBufferDesc.ByteWidth = sizeof(Vtx) * InVertexCount;
	VertexBufferDesc.MiscFlags = 0;

	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = InVertexSystemMemory;

	if (FAILED(DEVICE->CreateBuffer(&VertexBufferDesc, &SubDesc, VertexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	IndexCount = InIndexCount;
	// Create Index Buffer
	IndexBufferDesc.ByteWidth = sizeof(UINT) * InIndexCount;
	IndexBufferDesc.MiscFlags = 0;

	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA IbSubDesc = {};
	IbSubDesc.pSysMem = InIndexSystemMemory;

	if (FAILED(DEVICE->CreateBuffer(&IndexBufferDesc, &IbSubDesc, IndexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SysMem 유지
	VertexSystemMemory = new Vtx[VertexCount];
	memcpy(VertexSystemMemory, InVertexSystemMemory, sizeof(Vtx) * VertexCount);
	IndexSystemMemory = new UINT[IndexCount];
	memcpy(IndexSystemMemory, InIndexSystemMemory, sizeof(UINT) * IndexCount);

	return S_OK;
}

void CMesh::Binding()
{
	constexpr UINT Stride = sizeof(Vtx);
	constexpr UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(
		0,
		1,
		VertexBuffer.GetAddressOf(),
		&Stride,
		&Offset);
	CONTEXT->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT/*4바이트 포멧*/, 0);
}

void CMesh::Render()
{
	Binding();
	CONTEXT->DrawIndexed(IndexCount, 0, 0);
}

CMesh::CMesh()
	: CAsset(EAssetType::Mesh), VertexBufferDesc(), VertexCount(0), VertexSystemMemory(nullptr), IndexBufferDesc(),
	  IndexCount(0),
	  IndexSystemMemory(nullptr)
{
}

CMesh::~CMesh()
{
	if (VertexSystemMemory)
	{
		delete[] VertexSystemMemory;
		VertexSystemMemory = nullptr;
	}

	if (IndexSystemMemory)
	{
		delete[] IndexSystemMemory;
		IndexSystemMemory = nullptr;
	}
}
