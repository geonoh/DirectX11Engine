#pragma once
#include "CAsset.h"

class CTexture : public CAsset
{
private:
	virtual int Load(const wstring& FilePath) override;
	virtual int Save(const wstring& FilePath) override;

public:
	CTexture();
	~CTexture();

	void Binding(int RegisterNum);
	static void Clear(int RegisterNum);

private:
	ScratchImage Image;
	ComPtr<ID3D11Texture2D> Texture2D; // GPU에 보내기 위함
	ComPtr<ID3D11ShaderResourceView> SRV;
};

