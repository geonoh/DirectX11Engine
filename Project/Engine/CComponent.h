#pragma once
#include "CEntity.h"
class CGameObject;

class CComponent :
    public CEntity
{
private:
	CGameObject* m_Owner; // 해당 컴포넌트를 소유한 게임 오브젝트
	const COMPONENT_TYPE m_Type; // 컴포넌트 타입

public:
	virtual void begin() {}
	virtual void tick() {}
	virtual void finaltick() = 0;

public:
    COMPONENT_TYPE GetComponentType() const;
	CGameObject* GetOwner() const { return m_Owner; }

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();

	friend class CGameObject;
};

