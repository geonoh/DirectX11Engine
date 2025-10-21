#pragma once

class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine);

private:
	HWND m_hMainHwnd;
	POINT m_Resolution;

public:
	HWND GetMainWnd() { return m_hMainHwnd; }
	int Init(HWND _hWnd, POINT _Resolution);
	void Progress();
};