#include "pch.h"
#include "CCamera.h"

#include "CLayer.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CRenderMgr.h"

CCamera::CCamera() : CComponent(EComponentType::Camera)
{
}

CCamera::~CCamera()
{
}

void CCamera::FinalTick()
{
	
}

void CCamera::Render()
{
	const CLevel* CurrentLevel = CLevelMgr::GetInst()->GetCurrentLevel();;
	if (!CurrentLevel)
	{
		return;
	}

	for (int i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* Layer = CurrentLevel->GetLayer(i);
		if (!Layer)
		{
			continue;
		}
		Layer->Render();
	}
}

void CCamera::SetPriority(const int InPriority)
{
	Priority = InPriority;

	if (Priority != INVALID_CAMERA_PRIORITY)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, Priority);
	}
}
