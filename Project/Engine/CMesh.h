#pragma once
#include "CAsset.h"

class CMesh :
    public CAsset
{
private:
    ComPtr<ID3D11Buffer> m_VB;
    D3D11_BUFFER_DESC m_VBDesc;
    UINT m_VtxCount;
    Vtx* m_VtxSysMem;

    ComPtr<ID3D11Buffer> m_IB;
    D3D11_BUFFER_DESC m_IBDesc;
    UINT m_IdxCount;
    UINT* m_IdxSysMem;

    void Binding(); //IA에 바인딩

public:
    int Create(const Vtx* _VtxSysMem, size_t _VtxCount, const UINT* _IdxSysMem, size_t _IdxCount);
    void Render();

public:
    CMesh();
    ~CMesh();
};

