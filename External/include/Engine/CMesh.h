#pragma once
#include "CAsset.h"

class CMesh :
    public CAsset
{
private:
    ComPtr<ID3D11Buffer> VertexBuffer;
    D3D11_BUFFER_DESC VertexBufferDesc;
    UINT VertexCount;
    Vtx* VertexSystemMemory;

    ComPtr<ID3D11Buffer> IndexBuffer;
    D3D11_BUFFER_DESC IndexBufferDesc;
    UINT IndexCount;
    UINT* IndexSystemMemory;

    void Binding(); //IA에 바인딩

public:
    int Create(const Vtx* InVertexSystemMemory, size_t InVertexCount, const UINT* InIndexSystemMemory, size_t InIndexCount);
    void Render();

public:
    CMesh();
    ~CMesh();
};

