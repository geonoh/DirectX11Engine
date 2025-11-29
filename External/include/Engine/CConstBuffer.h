#pragma once
#include "CEntity.h"

class CConstBuffer final :
	public CEntity
{
public:
	CConstBuffer();
	virtual ~CConstBuffer() override;

	int Create(size_t BufferSize, EConstantBufferType Type);
	void SetData(const void* Data) const;
	void Binding();

private:
	ComPtr<ID3D11Buffer> ConstantBuffer;
	D3D11_BUFFER_DESC Desc;
	EConstantBufferType ConstantBufferType;
};
