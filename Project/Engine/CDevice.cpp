#include "pch.h"
#include "CDevice.h"

#include "CConstBuffer.h"

CDevice::~CDevice()
{
	Safe_Del_Array(ConstantBuffer);
}

int CDevice::Init(const HWND HWnd, const POINT Resolution)
{
	MainHwnd = HWnd;
	RenderResolution = Resolution;

	UINT Flag = 0;
#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	const HRESULT Result = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		Flag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		Device.GetAddressOf(),
		&Level,
		DeviceContext.GetAddressOf());

	if (FAILED(Result))
	{
		return E_FAIL;
	}

	// Swap chain 생성
	if (FAILED(CreateSwapChain()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}

	// ViewPort 설정
	// 윈도우 화면에 보여질 영역 설정
	D3D11_VIEWPORT Viewport = {};
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = RenderResolution.x;
	Viewport.Height = RenderResolution.y;

	// DepthStencil buffer texture 깊이의 범위를 0에서 1로 한다는 의미
	Viewport.MinDepth = 0;
	Viewport.MaxDepth = MAX_DEPTH_VALUE;

	// Viewport 정보 세팅
	DeviceContext->RSSetViewports(1, &Viewport);

	// 필요한 상수버퍼 생성
	if (FAILED(CreateConstBuffer()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::ClearTarget(const float (&ArrColor)[4]) const
{
	DeviceContext->ClearRenderTargetView(RenderTargetView.Get(), ArrColor);

	// DepthStencil buffer는 가장 큰 값으로 초기화 해야한다. *MAX_DEPTH_VALUE
	// -> TempInit에서 삼각형의 Depth가 0이다.
	// 왜냐하면 더 작은 Depth에 있는것을 그리기 때문에
	DeviceContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
	                                     MAX_DEPTH_VALUE, 0.f);
}

void CDevice::Present() const
{
	SwapChain->Present(0, 0);
}

ID3D11Device* CDevice::GetDevice() const
{
	return Device.Get();
}

ID3D11DeviceContext* CDevice::GetContext() const
{
	return DeviceContext.Get();
}

CConstBuffer* CDevice::GetConstBuffer(EConstantBufferType Type) const
{
	return ConstantBuffer[static_cast<UINT>(Type)];
}

int CDevice::CreateSwapChain()
{
	// 스왑 이펙트에 따라서
	// 1. 비트 블록 전송 모델
	// DXGI_SWAP_EFFECT_DISCARD	= 0,
	// DXGI_SWAP_EFFECT_SEQUENTIAL = 1,

	// 2. 대칭 이동 프레젠테이션 모델 - 티어링을 방지하기 위함
	// 프레임에 제한을 걸어야함
	// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL	= 3,
	// DXGI_SWAP_EFFECT_FLIP_DISCARD = 4
	DXGI_SWAP_CHAIN_DESC Desc = {};

	// SwapChain이 화면을 게시(Present)할 때, 출력 목적지 윈도우
	Desc.OutputWindow = MainHwnd;
	Desc.Windowed = true;

	// SwapChain이 만들어질때 버퍼 옵션
	Desc.BufferCount = 1;
	Desc.BufferDesc.Width = RenderResolution.x;
	Desc.BufferDesc.Height = RenderResolution.y;
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	ComPtr<IDXGIDevice> DxgiDevice = nullptr;
	ComPtr<IDXGIAdapter> Adapter = nullptr;
	ComPtr<IDXGIFactory> Factory = nullptr;

	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(DxgiDevice.GetAddressOf()));
	DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(Adapter.GetAddressOf()));
	Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(Factory.GetAddressOf()));

	if (FAILED(Factory->CreateSwapChain(Device.Get(), &Desc, SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{
	// 1. RenderTarget Texture를 스왑체인으로부터 가져오기
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(RenderTargetTexture.GetAddressOf()));

	// 2. RenderTargetView를 생성한다.
	Device->CreateRenderTargetView(RenderTargetTexture.Get(), nullptr, RenderTargetView.GetAddressOf());

	// 3. Depth Stencil용 Texture를 제작
	D3D11_TEXTURE2D_DESC Desc = {};
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.Width = RenderResolution.x;
	Desc.Height = RenderResolution.y;
	Desc.ArraySize = 1;
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Device->CreateTexture2D(&Desc, nullptr, DepthStencilTexture.GetAddressOf());

	// 4. DepthStencil View 만들기
	Device->CreateDepthStencilView(DepthStencilTexture.Get(), nullptr, DepthStencilView.GetAddressOf());

	// 5. RenderTarget과 DepthStencilTarget을 출력으로 지정한다.
	DeviceContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	ConstantBuffer[static_cast<UINT>(EConstantBufferType::Transform)] = new CConstBuffer;
	ConstantBuffer[static_cast<UINT>(EConstantBufferType::Transform)]->Create(
		sizeof(tTransform), EConstantBufferType::Transform);

	return S_OK;
}

CDevice::CDevice() : MainHwnd(nullptr), RenderResolution(), ConstantBuffer{}
{
}
