#include "pch.h"
#include "CTexture.h"

#include "CDevice.h"

int CTexture::Load(const wstring& FilePath)
{
	wchar_t Ext[50] = {};
	_wsplitpath_s(FilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, Ext, 50);

	const wstring StrExt = Ext;

	HRESULT Result = E_FAIL;
	if (StrExt == L".dds" || StrExt == L".DDS")
	{
		Result = LoadFromDDSFile(FilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, Image);
	}
	else if (StrExt == L".tga" || StrExt == L".TGA")
	{
		Result = LoadFromTGAFile(FilePath.c_str(), nullptr, Image);;
	}
	else
	{
		Result = LoadFromWICFile(FilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, Image);
	}

	if (FAILED(Result))
	{
		MessageBox(nullptr, FilePath.c_str(), L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	// Texture2D Description 작성해서 Texture2D 객체 생성
	// Texture2D 객체를 이용해서 ShaderResourceView 생성

	Result = CreateShaderResourceView(
		DEVICE, 
		Image.GetImages(), 
		Image.GetImageCount(), 
		Image.GetMetadata(), 
		SRV.GetAddressOf()
	);

	if (FAILED(Result))
	{
		MessageBox(nullptr, FilePath.c_str(), L"Shader Resource View 생성 실패", MB_OK);
		return E_FAIL;
	}

	SRV->GetResource(reinterpret_cast<ID3D11Resource**>(Texture2D.GetAddressOf()));

	return Result;
}

int CTexture::Save(const wstring& FilePath)
{
	return 0;
}

CTexture::CTexture() : CAsset(EAssetType::Texture)
{
}

CTexture::~CTexture()
{
}

void CTexture::Binding(const int RegisterNum)
{
	CONTEXT->PSSetShaderResources(RegisterNum, 1, SRV.GetAddressOf());
}
