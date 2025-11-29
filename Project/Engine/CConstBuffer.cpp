#include "pch.h"
#include "CConstBuffer.h"

#include "CDevice.h"

CConstBuffer::CConstBuffer() : Desc(), ConstantBufferType(EConstantBufferType::End)
{
}

CConstBuffer::~CConstBuffer()
{
}

int CConstBuffer::Create(const size_t BufferSize, const EConstantBufferType Type)
{
	ConstantBufferType = Type;

	Desc.ByteWidth = BufferSize;
	Desc.MiscFlags = 0;

	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&Desc, nullptr, ConstantBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CConstBuffer::SetData(const void* Data) const
{
	D3D11_MAPPED_SUBRESOURCE SubResource = {};

	CONTEXT->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
	memcpy(SubResource.pData, Data, Desc.ByteWidth);
	CONTEXT->Unmap(ConstantBuffer.Get(), 0);
}

void CConstBuffer::Binding()
{
	CONTEXT->VSSetConstantBuffers(static_cast<UINT>(ConstantBufferType), 1, ConstantBuffer.GetAddressOf());
}
