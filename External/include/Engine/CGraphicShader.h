#pragma once
#include "CShader.h"
class CGraphicShader :
    public CShader
{
public:
    CGraphicShader();
    ~CGraphicShader() override;

    int CreateVertexShader(const wstring& StrFilePath, const string& VsFuncName);
    int CreatePixelShader(const wstring& StrFilePath, const string& PsFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY InTopology);
	void SetRasterizerType(ERasterizerType InType);
    virtual void Binding() override;

private:
    ComPtr<ID3DBlob> VertexShaderBlob;
    ComPtr<ID3DBlob> PixelShaderBlob;

    ComPtr<ID3D11VertexShader> VertexShader;
    ComPtr<ID3D11PixelShader> PixelShader;

    ComPtr<ID3D11InputLayout> InputLayout;

    D3D11_PRIMITIVE_TOPOLOGY Topology;

	ERasterizerType RasterizerType;
};

