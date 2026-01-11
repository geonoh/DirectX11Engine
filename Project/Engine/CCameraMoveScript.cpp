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
	Vec3 CurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(EKey::W))
	{
		CurPos.y += DT * Speed;
	}
	if (KEY_PRESSED(EKey::S))
	{
		CurPos.y -= DT * Speed;
	}
	if (KEY_PRESSED(EKey::A))
	{
		CurPos.x -= DT * Speed;
	}
	if (KEY_PRESSED(EKey::D))
	{
		CurPos.x += DT * Speed;
	}

	GetOwner()->Transform()->SetRelativePos(CurPos);
}
