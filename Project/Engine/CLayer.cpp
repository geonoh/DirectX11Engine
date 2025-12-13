#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	Safe_Del_Vector(Objects);
}

void CLayer::AddObject(CGameObject* Object)
{
	Objects.push_back(Object);
}

void CLayer::Begin()
{
	for (CGameObject* Object : Objects)
	{
		Object->Begin();
	}
}

void CLayer::Tick()
{
	for (CGameObject* Object : Objects)
	{
		Object->Tick();
	}
}

void CLayer::FinalTick()
{
	for (CGameObject* Object : Objects)
	{
		Object->FinalTick();
	}
}

void CLayer::Render()
{
	for (CGameObject* Object : Objects)
	{
		Object->Render();
	}
}
