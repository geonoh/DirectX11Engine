#include "pch.h"
#include "CCamera.h"

#include "CGameObject.h"
#include "CLayer.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CRenderMgr.h"
#include "CTransform.h"

CCamera::CCamera() : CComponent(EComponentType::Camera)
{
}

CCamera::~CCamera()
{
}

void CCamera::FinalTick()
{
	// View 행결 계산
	const Vec3 CameraWorldPosition = GetOwner()->Transform()->GetRelativePos();
	ViewMatrix = XMMatrixTranslation(-CameraWorldPosition.x, -CameraWorldPosition.y, -CameraWorldPosition.z);


	// Projection 행렬 계산
}

void CCamera::Render()
{
	GlobalTransform.ViewMatrix = ViewMatrix;

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
