#pragma once
#include "singleton.h"

class CLevel;

class CLevelMgr : public CSingleton<CLevelMgr>
{
	SINGLE(CLevelMgr)

private:
	CLevel* CurrentLevel;

public:
	void Init();
	void Tick();
	void Render();
	CLevel* GetCurrentLevel() const;
};
