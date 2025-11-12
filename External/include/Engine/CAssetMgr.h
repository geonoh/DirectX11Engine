#pragma once
#include "CAsset.h"
#include "assets.h"

class CAssetMgr :
    public CSingleton<CAssetMgr>
{
    SINGLE(CAssetMgr)
private:
	map<wstring, Ptr<CAsset>> m_mapAsset[static_cast<UINT>(ASSET_TYPE::END)];

public:
    void init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputeShader();

public:
    template<typename T>
    Ptr<T> FindAsset(const wstring& _strKey);

    template<typename T>
    void AddAsset(const wstring& _strKey, T* pAsset);
};

// 변수 템플릿
template<typename T1, typename T2>
constexpr bool myBool = false;
template<typename T1> // 부분 특수화;;
constexpr bool myBool<T1, T1> = true; // 템플릿 변수 두개 받으면 무조건 false인데, 그 둘이 같으면 true

template<typename T>
ASSET_TYPE GetAssetType()
{
	if constexpr (myBool<T, CMesh>)
    {
        return ASSET_TYPE::MESH;
    }
    if constexpr (myBool<T, CComputeShader>)
    {
        return ASSET_TYPE::COMPUTE_SHADER;
    }
    if constexpr (myBool<T, CGraphicShader>)
    {
        return ASSET_TYPE::GRAPHICS_SHADER;
    }
}

template <typename T>
Ptr<T> CAssetMgr::FindAsset(const wstring& _strKey)
{
    const ASSET_TYPE type = GetAssetType<T>();
    auto iter = m_mapAsset[static_cast<UINT>(type)].find(_strKey);
    if (iter == m_mapAsset[static_cast<UINT>(type)].cend())
    {
        return nullptr;
    }

#ifdef _DEBUG
    T* pAsset = dynamic_cast<T*>(iter->second.Get());
    return pAsset;
#else 
    return (T*)iter->second.Get();
#endif
}

template <typename T>
void CAssetMgr::AddAsset(const wstring& _strKey, T* _pAsset)
{
    Ptr<T> pFoundAsset = FindAsset<T>(_strKey);
    assert(pFoundAsset.Get() == nullptr);

    const ASSET_TYPE type = GetAssetType<T>();
    m_mapAsset[static_cast<UINT>(type)].insert(make_pair(_strKey, _pAsset));
    _pAsset->m_Key = _strKey;
}
