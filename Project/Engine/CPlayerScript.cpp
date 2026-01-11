#include "pch.h"
#include "CPlayerScript.h"

#include "CGameObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CPlayerScript::CPlayerScript()
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Tick()
{
	// 키 입력에 따른 위치이동
	Vec3 CurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(EKey::UP))
	{
		CurPos.y += DT * Speed;
	}
	if (KEY_PRESSED(EKey::DOWN))
	{
		CurPos.y -= DT * Speed;
	}
	if (KEY_PRESSED(EKey::LEFT))
	{
		CurPos.x -= DT * Speed;
	}
	if (KEY_PRESSED(EKey::RIGHT))
	{
		CurPos.x += DT * Speed;
	}

	if (KEY_PRESSED(EKey::Z))
	{
		Vec3 Rotation = GetOwner()->Transform()->GetRelativeRotation();
		Rotation.z += DT * XM_PI;

		GetOwner()->Transform()->SetRelativeRotation(Rotation);
	}

	GetOwner()->Transform()->SetRelativePos(CurPos);
}
