#pragma once
#include "CShader.h"
class CGraphicShader :
    public CShader
{
public:
    CGraphicShader();
    ~CGraphicShader() override;

    int CreateVertexShader(const wstring& _strFilePath, const string& _VSFuncName);
    int CreatePixelShader(const wstring& _strFilePath, const string& _PSFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
    virtual void Binding() override;

private:
    ComPtr<ID3DBlob> m_VSBlob;
    ComPtr<ID3DBlob> m_PSBlob;

    ComPtr<ID3D11VertexShader> m_VS;
    ComPtr<ID3D11PixelShader> m_PS;

    ComPtr<ID3D11InputLayout> m_Layout;

    D3D11_PRIMITIVE_TOPOLOGY m_Topology;
};

