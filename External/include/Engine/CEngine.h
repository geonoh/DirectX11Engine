#pragma once

class CEngine
{
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