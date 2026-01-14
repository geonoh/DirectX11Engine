#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
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
	const Matrix ViewTranslate = XMMatrixTranslation(-CameraWorldPosition.x, -CameraWorldPosition.y, -CameraWorldPosition.z);;

	const Vec3 Right = Transform()->GetRelativeDirection(EDirectionType::Right);
	const Vec3 Up = Transform()->GetRelativeDirection(EDirectionType::Up);
	const Vec3 Front = Transform()->GetRelativeDirection(EDirectionType::Front);

	Matrix ViewRotation = XMMatrixIdentity();
	ViewRotation._11 = Right.x;	ViewRotation._12 = Up.x;	ViewRotation._13 = Front.x;
	ViewRotation._21 = Right.y;	ViewRotation._22 = Up.y;	ViewRotation._23 = Front.y;
	ViewRotation._31 = Right.z;	ViewRotation._32 = Up.z;	ViewRotation._33 = Front.z;

	// 이동 먼저하는게 중요하다
	ViewMatrix = ViewTranslate * ViewRotation;

	// Projection 행렬 계산
	constexpr float Fov = (XM_PI / 3.f); // Fov 60도
	const Vec2 RenderResolution =	CDevice::GetInst()->GetRenderResolution();
	const float AspectRatio = RenderResolution.x / RenderResolution.y;
	ProjectionMatrix = XMMatrixPerspectiveFovLH(Fov, AspectRatio, 1.f, FarValue);
}

void CCamera::Render()
{
	GlobalTransform.ViewMatrix = ViewMatrix;
	GlobalTransform.ProjectionMatrix = ProjectionMatrix;

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
