#pragma once

class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine);

private:
	HWND MainHwnd;
	POINT Resolution;

public:
	HWND GetMainWnd() const { return MainHwnd; }
	int Init(HWND InHwnd, POINT InResolution);
	static void Progress();
};
