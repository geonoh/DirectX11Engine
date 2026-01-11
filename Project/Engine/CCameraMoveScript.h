#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
private:
    float Speed = 1.f;

public:
    CCameraMoveScript();
    virtual ~CCameraMoveScript() override;
    virtual void Tick() override;
};

