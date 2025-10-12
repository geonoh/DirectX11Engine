#pragma once

class CDevice
{
private:
	HWND m_hMainWnd;
	POINT m_RenderResolution;

	ComPtr<ID3D11Device> m_Device;	// GPU �޸� �Ҵ�, Dx11 ���� ��ü ����
	ComPtr<ID3D11DeviceContext> m_Context; // GPU ������ ���� ���

	ComPtr<IDXGISwapChain> m_SwapChain; // ����Ÿ�� ���� ����, ȭ�鿡 ���� ����� �Խ�
	ComPtr<ID3D11Texture2D> m_RenderTargetTex;
	ComPtr<ID3D11RenderTargetView> m_RTV;

	ComPtr<ID3D11Texture2D> m_DepthStencilTex;
	ComPtr<ID3D11DepthStencilView> m_DSV;

public:
	static CDevice* GetInst()
	{
		static CDevice device;
		return &device;
	}

public:
	~CDevice();
	int Init(HWND _hWnd, POINT _Resolution);
	void ClearTarget(float(&_arrColor)[4]);
	void Present();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

private:
	int CreateSwapChain();
	int CreateView();

private:
	CDevice();
	CDevice(const CDevice& other) = delete;
};

