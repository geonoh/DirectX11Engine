#include "pch.h"
#include "CCameraMoveScript.h"

#include "CGameObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CCameraMoveScript::CCameraMoveScript()
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Tick()
{
	// Shift 속도 배율
	float NewSpeed = Speed;
	if (KEY_PRESSED(EKey::LSHIFT))
	{
		NewSpeed *= 4.f;
	}

	// 키 입력에 따른 위치이동
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 Front = Transform()->GetRelativeDirection(EDirectionType::Front);
	Vec3 Right = Transform()->GetRelativeDirection(EDirectionType::Right);

	if (KEY_PRESSED(EKey::W))
	{
		CurPos += DT * Front * NewSpeed;
	}
	if (KEY_PRESSED(EKey::S))
	{
		CurPos += DT * (-Front) * NewSpeed;
	}
	if (KEY_PRESSED(EKey::A))
	{
		CurPos += DT * (-Right) * NewSpeed;
	}
	if (KEY_PRESSED(EKey::D))
	{
		CurPos += DT * Right * NewSpeed;
	}
	if (KEY_PRESSED(EKey::RightMouseButtonClicked))
	{
		const Vec2 DragDir = CKeyMgr::GetInst()->GetMouseDragDirection();
		Vec3 CurrentRotation = Transform()->GetRelativeRotation();
		CurrentRotation.y += DragDir.x * DT * XM_PI * ROTATION_SPEED ;
		CurrentRotation.x += -DragDir.y * DT * XM_PI * ROTATION_SPEED;
		Transform()->SetRelativeRotation(CurrentRotation);
	}

	GetOwner()->Transform()->SetRelativePos(CurPos);
}
