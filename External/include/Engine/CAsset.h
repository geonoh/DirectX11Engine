#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring m_Key; // 본인이 로딩된 키 값
    wstring m_RelativePath; // 상대경로
    const ASSET_TYPE m_Type;

public:
    const wstring& GetKey() const { return m_Key; }
	const wstring& GetRelativePath() const { return m_RelativePath; }
	ASSET_TYPE GetAssetType() const { return m_Type; }

    CAsset(ASSET_TYPE _Type);
    virtual ~CAsset();
};

