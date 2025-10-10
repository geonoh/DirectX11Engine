#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"

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

	return S_OK;
}

void CEngine::Progress()
{
	// Level->Tick();

	// Clear
	float ClearColor[4] = {0.3f, 0.3f, 0.3f, 1.f};
	CDevice::GetInst()->ClearTarget(ClearColor);

	// Level->Render();

	// SwapChain->Present();
	CDevice::GetInst()->Present();
}
