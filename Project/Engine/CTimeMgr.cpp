#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr() : m_llFrequency(), m_llCurCount(), m_llPrevCount(), m_DT(0), m_Time(0), m_AccTime(0), m_FrmCount(0)
{
}

CTimeMgr::~CTimeMgr()
{
}


void CTimeMgr::init()
{
	// �ʴ� ī��Ʈ ��
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_DT = static_cast<float>(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / static_cast<float>(m_llFrequency.QuadPart);
	m_llPrevCount = m_llCurCount;

	// ���� �ð�
	m_Time += m_DT;

	m_AccTime += m_DT;
	++m_FrmCount;

	if (1.f < m_AccTime)
	{
		HWND hMainWnd = CEngine::GetInst()->GetMainWnd();
		wchar_t szText[255] = {};
		swprintf_s(szText, L"FPS : %d, DeltaTime : %f", m_FrmCount, m_DT);
		SetWindowText(hMainWnd, szText);

		m_AccTime -= 1.f;
		m_FrmCount = 0;
	}
}
