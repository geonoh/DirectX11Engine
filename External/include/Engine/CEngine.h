#pragma once

class CEngine
{
private:
	HWND m_hMainHwnd;
	POINT m_Resolution;

public:
	int Init(HWND _hWnd, POINT _Resolution);
	static void Progress();

public:
	static CEngine* GetInst()
	{
		static CEngine engine;
		return &engine;
	}

	CEngine(const CEngine& engine) = delete;

private:
	CEngine();
};