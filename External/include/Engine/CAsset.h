#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring Key; // 본인이 로딩된 키 값
    wstring RelativePath; // 상대경로
    const EAssetType Type;
    int ReferenceCount;

    void AddRef();
    void Release();

public:
    const wstring& GetKey() const { return Key; }
    const wstring& GetRelativePath() const { return RelativePath; }
	EAssetType GetAssetType() const { return Type; }

    CAsset(EAssetType Type);
    CAsset(const CAsset& Other) = delete;
    virtual ~CAsset() override;

    template<typename T>
    friend class Ptr;

    friend class CAssetMgr;
};

