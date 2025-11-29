#pragma once
#include "CAsset.h"
#include "assets.h"

class CAssetMgr :
	public CSingleton<CAssetMgr>
{
	SINGLE(CAssetMgr)

private:
	map<wstring, Ptr<CAsset>> AssetMap[static_cast<UINT>(EAssetType::End)];

public:
	void init();
	void CreateDefaultMesh();
	void CreateDefaultTexture();
	void CreateDefaultMaterial();
	void CreateDefaultGraphicShader();
	void CreateDefaultComputeShader();

	template <typename T>
	Ptr<T> FindAsset(const wstring& StrKey);

	template <typename T>
	void AddAsset(const wstring& StrKey, Ptr<T> Asset);
};

template <typename T>
EAssetType GetAssetType()
{
	if constexpr (std::is_same_v<T, CMesh>)
	{
		return EAssetType::Mesh;
	}
	if constexpr (std::is_same_v<T, CComputeShader>)
	{
		return EAssetType::ComputeShader;
	}
	if constexpr (std::is_same_v<T, CGraphicShader>)
	{
		return EAssetType::GraphicsShader;
	}
}

template <typename T>
Ptr<T> CAssetMgr::FindAsset(const wstring& StrKey)
{
	const EAssetType Type = GetAssetType<T>();
	const auto Iter = AssetMap[static_cast<UINT>(Type)].find(StrKey);
	if (Iter == AssetMap[static_cast<UINT>(Type)].cend())
	{
		return nullptr;
	}

#ifdef _DEBUG
	T* pAsset = dynamic_cast<T*>(Iter->second.Get());
	return pAsset;
#else
	return (T*)Iter->second.Get();
#endif
}

template <typename T>
void CAssetMgr::AddAsset(const wstring& StrKey, Ptr<T> Asset)
{
	Ptr<T> pFoundAsset = FindAsset<T>(StrKey);
	assert(pFoundAsset.Get() == nullptr);

	const EAssetType Type = GetAssetType<T>();
	AssetMap[static_cast<UINT>(Type)].insert(make_pair(StrKey, Asset.Get()));
	Asset->Key = StrKey;
}
