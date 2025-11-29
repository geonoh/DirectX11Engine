#include "pch.h"
#include "CAsset.h"

void CAsset::AddRef()
{
	ReferenceCount++;
}

void CAsset::Release()
{
	ReferenceCount--;
	if (ReferenceCount <= 0)
	{
		delete this;
	}
}

CAsset::CAsset(const EAssetType Type) : Type(Type), ReferenceCount(0)
{
}

CAsset::~CAsset()
{
}
