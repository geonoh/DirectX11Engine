#pragma once
#include "singleton.h"

class CCamera;

class CRenderMgr : public CSingleton<CRenderMgr>
{
	SINGLE(CRenderMgr)
public:
	void Init();
	void Tick();
	void Render();
	void RegisterCamera(CCamera* InCamera, int Priority);

private:
	vector<CCamera*> Cameras; // 0번 카메라를 메인으로 할 것
};

