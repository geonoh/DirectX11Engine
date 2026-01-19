#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
private:
    float Speed = 100.f;
    static constexpr float ROTATION_SPEED = 20.f;

public:
    CCameraMoveScript();
    virtual ~CCameraMoveScript() override;
    virtual void Tick() override;
};

