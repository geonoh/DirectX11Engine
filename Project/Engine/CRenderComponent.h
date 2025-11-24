#pragma once
#include "CComponent.h"

class CGraphicShader;
class CMesh;

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh> m_Mesh;
	Ptr<CGraphicShader> m_Shader;

public:
	virtual void render() = 0;

public:
	void SetMesh(Ptr<CMesh> _Mesh);
	void SetShader(Ptr<CGraphicShader> _Shader);

	Ptr<CMesh> GetMesh();
	Ptr<CGraphicShader> GetShader();

public:
	CRenderComponent(COMPONENT_TYPE _Type);
	virtual ~CRenderComponent() override;
};

