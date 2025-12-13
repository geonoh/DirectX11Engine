#pragma once
#include "CAsset.h"

class CShader :
    public CAsset
{
public:
    CShader(EAssetType _Type);
    virtual ~CShader();

    virtual void Binding() = 0;
    virtual int Load(const wstring& FilePath) override;
    virtual int Save(const wstring& FilePath) override;

protected:
    ComPtr<ID3DBlob> ErrorBlob;
};

