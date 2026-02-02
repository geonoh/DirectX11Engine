#include "pch.h"
#include "CMaterial.h"

#include "CConstBuffer.h"
#include "CDevice.h"

CMaterial::CMaterial() : CAsset(EAssetType::Material)
{
	MaterialConst.IntArray[0] = 1;
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetShader(Ptr<CGraphicShader> InShader)
{
	Shader = InShader;
}

Ptr<CGraphicShader> CMaterial::GetShader()
{
	return Shader;
}

void CMaterial::SetTexParam(TextureParam Param, const Ptr<CTexture>& InTexture)
{
	Texture[static_cast<int>(Param)] = InTexture;
}

void CMaterial::Binding()
{
	// 텍스쳐 바인딩
	for (int i = 0; i < static_cast<int>(TextureParam::End); ++i)
	{
		if (nullptr != Texture[i])
		{
			Texture[i]->Binding(i);
		}
		else
		{
			CTexture::Clear(i);
		}
	}

	if (Shader.Get())
	{
		Shader->Binding();
	}

	CConstBuffer* MaterialConstBuffer = CDevice::GetInst()->GetConstBuffer(EConstantBufferType::Material);
	if (MaterialConstBuffer)
	{
		MaterialConstBuffer->SetData(&MaterialConst);
		MaterialConstBuffer->Binding();
	}
}

int CMaterial::Load(const wstring& FilePath)
{
	return S_OK;
}

int CMaterial::Save(const wstring& FilePath)
{
	return S_OK;
}
