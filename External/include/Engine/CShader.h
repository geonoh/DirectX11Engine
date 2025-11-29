#pragma once
#include "CAsset.h"

class CShader :
    public CAsset
{
public:
    CShader(EAssetType _Type);
    virtual ~CShader();

    virtual void Binding() = 0;

protected:
    ComPtr<ID3DBlob> ErrorBlob;
};

