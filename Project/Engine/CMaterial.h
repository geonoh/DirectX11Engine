#pragma once
#include "CAsset.h"
#include "assets.h"
#include "enum.h"

class CTexture;

class CMaterial final : public CAsset
{
public:
	CMaterial();
	virtual ~CMaterial() override;

	void SetShader(Ptr<CGraphicShader> InShader);
	Ptr<CGraphicShader> GetShader();

	template <typename T>
	void SetScalarParam(ScalarParam Param, const T& Value);

	void SetTexParam(TextureParam Param, const Ptr<CTexture>& InTexture);
	;

	void Binding();

	virtual int Load(const wstring& FilePath) override;
	virtual int Save(const wstring& FilePath) override;

private:
	Ptr<CGraphicShader> Shader;
	Ptr<CTexture> Texture[static_cast<int>(TextureParam::End)];
	tMaterialConst MaterialConst;
};

template <typename T>
void CMaterial::SetScalarParam(const ScalarParam Param, const T& Value)
{
	void* ptr = (void*)(&Value);

	switch (Param)
	{
	case ScalarParam::Int_0:
	case ScalarParam::Int_1:
	case ScalarParam::Int_2:
	case ScalarParam::Int_3:
		{
			MaterialConst.IntArray[static_cast<int>(Param)] = *static_cast<int*>(ptr);
		}
		break;

	case ScalarParam::Float_0:
	case ScalarParam::Float_1:
	case ScalarParam::Float_2:
	case ScalarParam::Float_3:
		{
			const int Index = static_cast<int>(Param) - static_cast<int>(ScalarParam::Float_0);
			MaterialConst.FloatArray[Index] = *static_cast<float*>(ptr);
		}
		break;

	case ScalarParam::Vec2_0:
	case ScalarParam::Vec2_1:
	case ScalarParam::Vec2_2:
	case ScalarParam::Vec2_3:
		{
			const int Index = static_cast<int>(Param) - static_cast<int>(ScalarParam::Vec2_0);
			MaterialConst.Vec2Array[Index] = *static_cast<Vec2*>(ptr);
		}
		break;

	case ScalarParam::Vec4_0:
	case ScalarParam::Vec4_1:
	case ScalarParam::Vec4_2:
	case ScalarParam::Vec4_3:
		{
			const int Index = static_cast<int>(Param) - static_cast<int>(ScalarParam::Vec4_0);
			MaterialConst.Vec4Array[Index] = *static_cast<Vec4*>(ptr);
		}
		break;

	case ScalarParam::Mat_0:
	case ScalarParam::Mat_1:
	case ScalarParam::Mat_2:
	case ScalarParam::Mat_3:
		{
			const int Index = static_cast<int>(Param) - static_cast<int>(ScalarParam::Mat_0);
			MaterialConst.MatrixArray[Index] = *static_cast<Matrix*>(ptr);
		}
		break;

	case ScalarParam::End:
		break;
	default:
		break;
	}
}
