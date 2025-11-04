#include "pch.h"
#include "CAsset.h"

void CAsset::AddRef()
{
	m_RefCount++;
}

void CAsset::Release()
{
	m_RefCount--;
	if (m_RefCount <= 0)
	{
		delete this;
	}
}

CAsset::CAsset(ASSET_TYPE _Type) : m_Type(_Type), m_RefCount(0)
{
}

CAsset::~CAsset()
{
}
