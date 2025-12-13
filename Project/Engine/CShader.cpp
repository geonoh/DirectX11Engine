#include "pch.h"
#include "CShader.h"

CShader::CShader(EAssetType _Type) : CAsset(_Type)
{
}

CShader::~CShader()
{
}

int CShader::Load(const wstring& FilePath)
{
	return 0;
}

int CShader::Save(const wstring& FilePath)
{
	return 0;
}
