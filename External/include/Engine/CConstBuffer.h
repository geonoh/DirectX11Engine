#pragma once
#include "CEntity.h"

class CConstBuffer :
    public CEntity
{
public:
	CConstBuffer();
    ~CConstBuffer();

    int Create(size_t _bufferSize, CB_TYPE _Type);
    void SetData(void* _pData);
    void Binding();

private:
    ComPtr<ID3D11Buffer> m_CB;
    D3D11_BUFFER_DESC m_Desc;
    CB_TYPE m_Type;
};
