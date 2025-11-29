#pragma once

class CConstBuffer;

class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice);

private:
	HWND MainHwnd;
	POINT RenderResolution;

	ComPtr<ID3D11Device> Device;	// GPU 메모리 할당, Dx11 관련 객체 생성
	ComPtr<ID3D11DeviceContext> DeviceContext; // GPU 랜더링 관련 명령

	ComPtr<IDXGISwapChain> SwapChain; // 렌던타켓 버퍼 소유, 화면에 최종 장면을 게시
	ComPtr<ID3D11Texture2D> RenderTargetTexture;
	ComPtr<ID3D11RenderTargetView> RenderTargetView;

	ComPtr<ID3D11Texture2D> DepthStencilTexture;
	ComPtr<ID3D11DepthStencilView> DepthStencilView;

	CConstBuffer* ConstantBuffer[static_cast<UINT>(EConstantBufferType::End)];

public:
	static CDevice* GetInst()
	{
		static CDevice Device;
		return &Device;
	}

public:
	int Init(HWND HWnd, POINT Resolution);
	void ClearTarget(const float(&ArrColor)[4]) const;
	void Present() const;

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;
	CConstBuffer* GetConstBuffer(EConstantBufferType Type) const;

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();

	static constexpr float MAX_DEPTH_VALUE = 1.f;
};

