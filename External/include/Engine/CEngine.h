#pragma once

class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine);

private:
	HWND MainHwnd;
	Vec2 Resolution;

public:
	HWND GetMainWnd() const { return MainHwnd; }
	int Init(HWND InHwnd, Vec2 InResolution);
	static void Progress();
};
