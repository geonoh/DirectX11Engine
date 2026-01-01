#include "pch.h"
#include "CEngine.h"

#include "CAssetMgr.h"
#include "CDevice.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"

CEngine::~CEngine()
{
}

CEngine::CEngine()
	: MainHwnd(nullptr)
	  , Resolution{}
{
}

int CEngine::Init(const HWND InHwnd, const POINT InResolution)
{
	MainHwnd = InHwnd;
	Resolution = InResolution;

	// 윈도우 크기 설정
	RECT Rect = {0, 0, Resolution.x, Resolution.y};
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(MainHwnd, nullptr, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, 0);

	// DirectX11
	if (FAILED(CDevice::GetInst()->Init(InHwnd, InResolution)))
	{
		MessageBox(MainHwnd, L"Device 초기화 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager Init
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CAssetMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();

	return S_OK;
}

void CEngine::Progress()
{
	// Manager Tick
	CTimeMgr::GetInst()->Tick();
	CKeyMgr::GetInst()->Tick();

	// Object Tick
	CLevelMgr::GetInst()->Tick();

	// Rendering
	// Target Clear
	constexpr float ClearColor[4] = {0.3f, 0.3f, 0.3f, 1.f};
	CDevice::GetInst()->ClearTarget(ClearColor);

	// Object Render
	CLevelMgr::GetInst()->Render();

	CDevice::GetInst()->Present();
}
