#include "pch.h"
#include "CDevice.h"

CDevice::~CDevice()
{
}

int CDevice::Init(const HWND _hWnd, const POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_RenderResolution = _Resolution;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	const HRESULT result = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		m_Device.GetAddressOf(),
		&level,
		m_Context.GetAddressOf());

	if (FAILED(result))
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
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_RenderResolution.x;
	viewport.Height = m_RenderResolution.y;

	// DepthStencil buffer texture 깊이의 범위를 0에서 1로 한다는 의미
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	// Viewport 정보 세팅
	m_Context->RSSetViewports(1, &viewport);

	return S_OK;
}

void CDevice::ClearTarget(float(& _arrColor)[4])
{
	m_Context->ClearRenderTargetView(m_RTV.Get(), _arrColor);
}

void CDevice::Present()
{
	m_SwapChain->Present(0, 0);
}

ID3D11Device* CDevice::GetDevice()
{
	return m_Device.Get();
}

ID3D11DeviceContext* CDevice::GetContext()
{
	return m_Context.Get();
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
	Desc.OutputWindow = m_hMainWnd;
	Desc.Windowed = true;

	// SwapChain이 만들어질때 버퍼 옵션
	Desc.BufferCount = 1;
	Desc.BufferDesc.Width = m_RenderResolution.x;
	Desc.BufferDesc.Height = m_RenderResolution.y;
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	ComPtr<IDXGIFactory> pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &Desc, m_SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{
	// 1. RenderTarget Texture를 스왑체인으로부터 가져오기
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RenderTargetTex.GetAddressOf());

	// 2. RenderTargetView를 생성한다.
	m_Device->CreateRenderTargetView(m_RenderTargetTex.Get(), nullptr, m_RTV.GetAddressOf());

	// 3. Depth Stencil용 Texture를 제작
	D3D11_TEXTURE2D_DESC Desc = {};
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.Width = m_RenderResolution.x;
	Desc.Height = m_RenderResolution.y;
	Desc.ArraySize = 1;
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_Device->CreateTexture2D(&Desc, nullptr, m_DepthStencilTex.GetAddressOf());

	// 4. DepthStencil View 만들기
	m_Device->CreateDepthStencilView(m_DepthStencilTex.Get(), nullptr, m_DSV.GetAddressOf());

	// 5. RenderTarget과 DepthStencilTarget을 출력으로 지정한다.
	m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

	return S_OK;
}

CDevice::CDevice() : m_hMainWnd(nullptr), m_RenderResolution()
{
}
