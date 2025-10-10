#pragma once

class CDevice
{
private:
	HWND m_hMainWnd;
	POINT m_RenderResolution;

	ID3D11Device* m_Device;	// GPU 메모리 할당, Dx11 관련 객체 생성
	ID3D11DeviceContext* m_Context; // GPU 랜더링 관련 명령

	IDXGISwapChain* m_SwapChain; // 렌던타켓 버퍼 소유, 화면에 최종 장면을 게시
	ID3D11Texture2D* m_RenderTargetTex;
	ID3D11RenderTargetView* m_RTV;

	ID3D11Texture2D* m_DepthStencilTex;
	ID3D11DepthStencilView* m_DSV;

public:
	static CDevice* GetInst()
	{
		static CDevice device;
		return &device;
	}

public:
	~CDevice();
	int Init(HWND _hWnd, POINT _Resolution);

private:
	int CreateSwapChain();
	int CreateView();

private:
	CDevice();
	CDevice(const CDevice& other) = delete;
};

