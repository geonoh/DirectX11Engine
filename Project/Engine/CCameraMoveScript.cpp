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
	// 키 입력에 따른 위치이동
	Vec3 CurPos = Transform()->GetRelativePos();
	Vec3 Front = Transform()->GetRelativeDirection(EDirectionType::Front);
	Vec3 Right = Transform()->GetRelativeDirection(EDirectionType::Right);

	if (KEY_PRESSED(EKey::W))
	{
		CurPos += DT * Front * Speed;
	}
	if (KEY_PRESSED(EKey::S))
	{
		CurPos += DT * (-Front) * Speed;
	}
	if (KEY_PRESSED(EKey::A))
	{
		CurPos += DT * (-Right) * Speed;
	}
	if (KEY_PRESSED(EKey::D))
	{
		CurPos += DT * Right * Speed;
	}
	if (KEY_PRESSED(EKey::Y))
	{
		Vec3 Rotation = Transform()->GetRelativeRotation();
		Rotation.y += DT * XM_PI;
		Transform()->SetRelativeRotation(Rotation);
	}

	GetOwner()->Transform()->SetRelativePos(CurPos);
}
