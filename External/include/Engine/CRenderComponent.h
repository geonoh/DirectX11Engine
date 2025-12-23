#pragma once
#include "CComponent.h"

class CTexture;
class CGraphicShader;
class CMesh;

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh> Mesh;
	Ptr<CGraphicShader> Shader;
	Ptr<CTexture> Texture;

public:
	virtual void Render() = 0;

public:
	void SetMesh(Ptr<CMesh> InMesh);
	void SetShader(Ptr<CGraphicShader> InShader);
	void SetTexture(Ptr<CTexture> InTexture);

	Ptr<CMesh> GetMesh();
	Ptr<CGraphicShader> GetShader();
	Ptr<CTexture> GetTexture();

public:
	CRenderComponent(EComponentType Type);
	virtual ~CRenderComponent() override;
};

