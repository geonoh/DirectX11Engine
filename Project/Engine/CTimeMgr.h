#pragma once
#include "singleton.h"

class CTimeMgr :
    public CSingleton<CTimeMgr>
{
    SINGLE(CTimeMgr)
private:
    LARGE_INTEGER m_llFrequency; // �ʴ� ī��Ʈ ��
    LARGE_INTEGER m_llCurCount; // ���� ī��Ʈ ��
    LARGE_INTEGER m_llPrevCount; // ���� ������ ī��Ʈ ��

    float m_DT; // Delta Time : 1������ �����ϴµ� �ɸ� �ð�
    float m_Time; // ���μ��� ���� ������ ���� �ð�
    float m_AccTime; // 1�� üũ�ϱ� ���� �ð� ��������

    UINT m_FrmCount;

public:
    void init();
    void tick();
};

