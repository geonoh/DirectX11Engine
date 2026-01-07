#include "pch.h"
#include "CLevel.h"
#include "CLayer.h"

CLevel::CLevel()
{
	for (size_t i = 0; i < MAX_LAYER; ++i)
	{
		Layers[i] = new CLayer();
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(Layers);
}

void CLevel::AddObject(const UINT LayerIndex, CGameObject* Object)
{
	if (LayerIndex >= MAX_LAYER)
	{
		return;
	}

	Layers[LayerIndex]->AddObject(Object);
}

void CLevel::Begin()
{
	for (CLayer* Layer : Layers)
	{
		Layer->Begin();
	}
}

void CLevel::Tick()
{
	for (CLayer* Layer : Layers)
	{
		Layer->Tick();
	}
}

void CLevel::FinalTick()
{
	for (CLayer* Layer : Layers)
	{
		Layer->FinalTick();
	}
}

void CLevel::Render()
{
	for (CLayer* Layer : Layers)
	{
		Layer->Render();
	}
}

CLayer* CLevel::GetLayer(const int LayerIndex) const
{
	if (LayerIndex < 0 || LayerIndex >= MAX_LAYER)
	{
		return nullptr;
	}
	return Layers[LayerIndex];
}
