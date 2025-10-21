#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"
#include "CTimeMgr.h"

#include "Temp.h"

CEngine::~CEngine()
{
	TempRelease();
}

CEngine::CEngine()
	: m_hMainHwnd(nullptr)
	  , m_Resolution{}
{
}

int CEngine::Init(const HWND _hWnd, const POINT _Resolution)
{
	m_hMainHwnd = _hWnd;
	m_Resolution = _Resolution;

	// ������ ũ�� ����
	RECT rt = {0, 0, m_Resolution.x, m_Resolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DirectX11
	if (FAILED(CDevice::GetInst()->Init(_hWnd, _Resolution)))
	{
		MessageBox(m_hMainHwnd, L"Device �ʱ�ȭ ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Manager Init
	CTimeMgr::GetInst()->init();

	if (FAILED(TempInit()))
	{
		MessageBox(m_hMainHwnd, L"Device �ʱ�ȭ ����", L"TempInit �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CEngine::Progress()
{
	// Manager Tick
	CTimeMgr::GetInst()->tick();

	// Object Tick
	TempTick();

	// Rendering
	// Target Clear
	float ClearColor[4] = {0.3f, 0.3f, 0.3f, 1.f};
	CDevice::GetInst()->ClearTarget(ClearColor);

	// Object Render
	TempRender();

	CDevice::GetInst()->Present();
}
