#pragma once
#include "singleton.h"

enum class EKey
{
	W,
    S,
    A,
    D,

    Z,
    X,
    C,
    V,
    Y,

    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,

    LEFT,
    RIGHT,
    UP,
    DOWN,

	LeftMouseButtonClicked,
	RightMouseButtonClicked,

    ENTER,
    ESC,
    SPACE,
    LSHIFT,
    ALT,
    CTRL,

    KEY_END,
};

enum class EKeyState
{
	Tap,        // 누른 순간
    Pressed,    // 눌려진 상태
    Released,   // 뗀 순간
    None,
};

struct KeyInfo
{
    EKeyState State;
    bool PrevPressed;
};

class CKeyMgr :
    public CSingleton<CKeyMgr>
{
    SINGLE(CKeyMgr)
private:
    vector<KeyInfo> Keys;
    Vec2 CurrentMousePosition;
    Vec2 PreviousMousePosition;
    Vec2 DragDirection;

public:
    void Init();
    void Tick();

    EKeyState GetKeyState(EKey InKey) const;
	Vec2 GetMousePosition() const;
    Vec2 GetPreviousMousePosition();
	Vec2 GetMouseDragDirection() const;
};

