#include "pch.h"
#include "CRenderMgr.h"

#include "CCamera.h"
#include "CDevice.h"

CRenderMgr::CRenderMgr()
{
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::Init()
{
}

void CRenderMgr::Tick()
{
}

void CRenderMgr::Render()
{
	// Target Clear
	constexpr float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearTarget(ClearColor);

	// 각 카메라가 보고있는 장면을 렌더타겟에 그린다.
	for (CCamera* Camera : Cameras)
	{
		if (!Camera)
		{
			continue;
		}

		Camera->Render();
	}

	// Present
	CDevice::GetInst()->Present();
}

void CRenderMgr::RegisterCamera(CCamera* InCamera, const int Priority)
{
	for (int i = 0; i < Cameras.size(); ++i)
	{
		if (Cameras[i] == InCamera)
		{
			if (Priority == i)
			{
				return;
			}
			else
			{
				Cameras[i] = nullptr;
			}
		}
	}

	if (Cameras.size() <= Priority)
	{
		Cameras.resize(Priority + 1);
	}

	Cameras[Priority] = InCamera;
}
