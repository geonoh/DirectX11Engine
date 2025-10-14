#pragma once

class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine);

private:
	HWND m_hMainHwnd;
	POINT m_Resolution;

public:
	int Init(HWND _hWnd, POINT _Resolution);
	void Progress();
};