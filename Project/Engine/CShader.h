#pragma once
#include "CAsset.h"

class CShader :
    public CAsset
{
public:
    CShader(ASSET_TYPE _Type);
    virtual ~CShader();

    virtual void Binding() = 0;

protected:
    ComPtr<ID3DBlob> m_ErrBlob;
};

