#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer : public CEntity
{
public:
	CLayer();
	virtual ~CLayer() override;
	void AddObject(CGameObject* Object);

	void Begin();
	void Tick();
	void FinalTick();
	void Render();

private:
	vector<CGameObject*> Objects;
};

