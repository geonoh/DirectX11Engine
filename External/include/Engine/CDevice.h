#pragma once

class CDevice
{
private:
	HWND m_hMainWnd;
	POINT m_RenderResolution;

	ID3D11Device* m_Device;	// GPU �޸� �Ҵ�, Dx11 ���� ��ü ����
	ID3D11DeviceContext* m_Context; // GPU ������ ���� ���

	IDXGISwapChain* m_SwapChain; // ����Ÿ�� ���� ����, ȭ�鿡 ���� ����� �Խ�
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

