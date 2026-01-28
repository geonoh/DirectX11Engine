#pragma once
#include "CAsset.h"
#include "assets.h"

class CTexture;

class CMaterial : public CAsset
{
public:
    CMaterial();
	virtual ~CMaterial() override;

	void SetShader(Ptr<CGraphicShader> InShader);
    Ptr<CGraphicShader> GetShader();

    void Binding();

	virtual int Load(const wstring& FilePath) override;
	virtual int Save(const wstring& FilePath) override;

private:
	Ptr<CGraphicShader> Shader;
	tMaterialConst MaterialConst;
};

