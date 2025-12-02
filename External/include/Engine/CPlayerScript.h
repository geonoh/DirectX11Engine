#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
private:
    float Speed = 1.f;

public:
	CPlayerScript();
    virtual ~CPlayerScript() override;
    virtual void Tick() override;
};

