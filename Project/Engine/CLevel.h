#pragma once
#include "CEntity.h"

class CGameObject;
class CLayer;

class CLevel : public CEntity
{
public:
	CLevel();
	virtual ~CLevel() override;

	void AddObject(UINT LayerIndex, CGameObject* Object);

	void Begin();
	void Tick();
	void FinalTick();
	void Render();
	CLayer* GetLayer(int LayerIndex) const;

private:
	CLayer* Layers[MAX_LAYER];
};
