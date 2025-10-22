#include "pch.h"
#include "CKeyMgr.h"

UINT g_keyValue[static_cast<int>(KEY::KEY_END)] = 
{
    'W',
    'S',
    'A',
    'D',

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

void CKeyMgr::init()
{
	for (int i = 0; i < static_cast<int>(KEY::KEY_END); ++i)
	{
		tKeyInfo info = {};
		info.State = KEY_STATE::NONE;
		info.PrevPressed = false;
		m_vecKey.push_back(info);
	}
}

void CKeyMgr::tick()
{
	for (size_t i = 0; i < m_vecKey.size(); ++i)
	{
        // KEY �� ���ȴ�
        if (GetAsyncKeyState(g_keyValue[i]) & 0x8001)
        {
            if (!m_vecKey[i].PrevPressed)
            {
                m_vecKey[i].State = KEY_STATE::TAP;
            }

            // �������� �����־���.
            else
            {
                m_vecKey[i].State = KEY_STATE::PRESSED;
            }

            m_vecKey[i].PrevPressed = true;
        }
        else
        {
	        // �ش� KEY�� �ȴ����ִ�.
            if (m_vecKey[i].PrevPressed)
            {
	            // ���� Frame������ �����־���.
                m_vecKey[i].State = KEY_STATE::RELEASED;
            }
            else
            {
                m_vecKey[i].State = KEY_STATE::NONE;
            }

            m_vecKey[i].PrevPressed = false;
        }
	}
}

KEY_STATE CKeyMgr::GetKeyState(const KEY _Key) const
{
    return m_vecKey[static_cast<int>(_Key)].State;
}
