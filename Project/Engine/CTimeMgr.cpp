#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr() : Frequency(), CurrentCount(), PrevCount(), DeltaTime(0), Time(0), AccTime(0), FrameCount(0)
{
}

CTimeMgr::~CTimeMgr()
{
}


void CTimeMgr::Init()
{
	// 초당 카운트 수
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&CurrentCount);
	PrevCount = CurrentCount;
}

void CTimeMgr::Tick()
{
	QueryPerformanceCounter(&CurrentCount);

	DeltaTime = static_cast<float>(CurrentCount.QuadPart - PrevCount.QuadPart) / static_cast<float>(Frequency.QuadPart);
	PrevCount = CurrentCount;

	// 누적 시간
	Time += DeltaTime;

	AccTime += DeltaTime;
	++FrameCount;

	if (1.f < AccTime)
	{
		const HWND HMainWnd = CEngine::GetInst()->GetMainWnd();
		wchar_t Text[255] = {};
		swprintf_s(Text, L"FPS : %d, DeltaTime : %f", FrameCount, DeltaTime);
		SetWindowText(HMainWnd, Text);

		AccTime -= 1.f;
		FrameCount = 0;
	}
}

float CTimeMgr::GetDeltaTime() const
{
	return DeltaTime;
}
