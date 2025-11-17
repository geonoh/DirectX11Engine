#pragma once
#include "CEntity.h"

class CComponent;

class CGameObject : public CEntity
{
private:
	CComponent* m_arrCom[static_cast<UINT>(COMPONENT_TYPE::END)];

public:

};

