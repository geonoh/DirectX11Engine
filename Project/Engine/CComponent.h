#pragma once
#include "CEntity.h"
class CGameObject;

class CComponent :
    public CEntity
{
private:
	CGameObject* Owner; // 해당 컴포넌트를 소유한 게임 오브젝트
	const EComponentType Type; // 컴포넌트 타입

public:
	virtual void Begin() {}
	virtual void Tick() {}
	virtual void FinalTick() = 0;

public:
    EComponentType GetComponentType() const;
	CGameObject* GetOwner() const { return Owner; }

public:
    CComponent(EComponentType InType);
    ~CComponent();

	friend class CGameObject;
};

