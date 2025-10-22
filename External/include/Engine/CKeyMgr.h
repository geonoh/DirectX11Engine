#pragma once
#include "singleton.h"

enum class KEY
{
	W,
    S,
    A,
    D,

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

    ENTER,
    ESC,
    SPACE,
    LSHIFT,
    ALT,
    CTRL,

    KEY_END,
};

enum class KEY_STATE
{
	TAP,        // 누른 순간
    PRESSED,    // 눌려진 상태
    RELEASED,   // 뗀 순간
    NONE,
};

struct tKeyInfo
{
    KEY_STATE State;
    bool PrevPressed;
};

class CKeyMgr :
    public CSingleton<CKeyMgr>
{
    SINGLE(CKeyMgr)
private:
    vector<tKeyInfo> m_vecKey;

public:
    void init();
    void tick();

    KEY_STATE GetKeyState(KEY _Key) const;
};

