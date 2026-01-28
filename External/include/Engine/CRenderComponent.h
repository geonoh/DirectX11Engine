#pragma once
#include "CComponent.h"

#include "assets.h"

class CTexture;
class CMesh;

class CRenderComponent : public CComponent
{
private:
	Ptr<CMesh> Mesh;
	Ptr<CMaterial> Material;

public:
	virtual void Render() = 0;

public:
	void SetMesh(Ptr<CMesh> InMesh);
	void SetMaterial(Ptr<CMaterial> InMaterial);

	Ptr<CMesh> GetMesh();
	Ptr<CMaterial> GetMaterial();

public:
	CRenderComponent(EComponentType Type);
	virtual ~CRenderComponent() override;
};

