#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"

UINT KeyValues[static_cast<int>(EKey::KEY_END)] =
{
	'W',
	'S',
	'A',
	'D',

	'Z',
	'X',
	'C',
	'V',
	'Y',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_RETURN,
	VK_ESCAPE,
	VK_SPACE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,

	//KEY_END,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Init()
{
	for (int i = 0; i < static_cast<int>(EKey::KEY_END); ++i)
	{
		KeyInfo info = {};
		info.State = EKeyState::None;
		info.PrevPressed = false;
		Keys.push_back(info);
	}
}

void CKeyMgr::Tick()
{
	for (size_t i = 0; i < Keys.size(); ++i)
	{
		// EKey 가 눌렸다
		if (GetAsyncKeyState(KeyValues[i]) & 0x8001)
		{
			if (!Keys[i].PrevPressed)
			{
				Keys[i].State = EKeyState::Tap;
			}

			// 이전에도 눌려있었다.
			else
			{
				Keys[i].State = EKeyState::Pressed;
			}

			Keys[i].PrevPressed = true;
		}
		else
		{
			// 해당 KEY가 안눌려있다.
			if (Keys[i].PrevPressed)
			{
				// 이전 Frame에서는 눌려있었다.
				Keys[i].State = EKeyState::Released;
			}
			else
			{
				Keys[i].State = EKeyState::None;
			}

			Keys[i].PrevPressed = false;
		}
	}

	// 마우스 좌표 갱신
	PreviousMousePosition = CurrentMousePosition;

	POINT NewMousePosition{ };
	GetCursorPos(&NewMousePosition);
	ScreenToClient(CEngine::GetInst()->GetMainWnd(), &NewMousePosition);
	CurrentMousePosition = Vec2(static_cast<float>(NewMousePosition.x), static_cast<float>(NewMousePosition.y));
	DragDirection = CurrentMousePosition - PreviousMousePosition;
	DragDirection.y *= -1.0f; // 윈도우는 아래방향이 +y 이므로 반대로 바꿔줌
	DragDirection.Normalize();
}

EKeyState CKeyMgr::GetKeyState(const EKey InKey) const
{
	return Keys[static_cast<int>(InKey)].State;
}

Vec2 CKeyMgr::GetMousePosition() const
{
	return CurrentMousePosition;
}

Vec2 CKeyMgr::GetPreviousMousePosition()
{
	return PreviousMousePosition;
}

Vec2 CKeyMgr::GetMouseDragDirection() const
{
	return DragDirection;
}
