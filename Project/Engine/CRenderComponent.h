#pragma once
#include "CComponent.h"

class CGraphicShader;
class CMesh;

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh> Mesh;
	Ptr<CGraphicShader> Shader;

public:
	virtual void Render() = 0;

public:
	void SetMesh(const Ptr<CMesh>& InMesh);
	void SetShader(const Ptr<CGraphicShader>& InShader);

	Ptr<CMesh> GetMesh();
	Ptr<CGraphicShader> GetShader();

public:
	CRenderComponent(EComponentType Type);
	virtual ~CRenderComponent() override;
};

