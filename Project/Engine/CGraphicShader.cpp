#include "pch.h"
#include "CGraphicShader.h"

#include "CDevice.h"

CGraphicShader::CGraphicShader() : CShader(EAssetType::GraphicsShader), Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CGraphicShader::~CGraphicShader()
{
}

int CGraphicShader::CreateVertexShader(const wstring& StrFilePath, const string& VsFuncName)
{
	if (FAILED(D3DCompileFromFile(
		StrFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		VsFuncName.c_str(),
		"vs_5_0",
		D3DCOMPILE_DEBUG,
		0,
		VertexShaderBlob.GetAddressOf(),
		ErrorBlob.GetAddressOf())))
	{
		if (nullptr != ErrorBlob)
		{
			// 문법 오류
			MessageBoxA(nullptr, static_cast<char*>(ErrorBlob->GetBufferPointer()), "버텍스 쉐이더 컴파일 오류", MB_OK);
			return E_FAIL;
		}
		// 경로 오류
		MessageBox(nullptr, L"파일을 찾을 수 없습니다.", L"버텍스 쉐이더 컴파일 오류", MB_OK);
		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		nullptr,
		VertexShader.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Layout 생성
	// 정점 레이아웃 정보 만들기 (즉, Vtx의 구조)
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[3] = {};

	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT; // Vec3과 맞는 사이즈 강제로 맞춤;;; Vtx::vPos
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;

	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // Vec4과 맞는 사이즈 강제로 맞춤, Vtx::vColor
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;
	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;

	LayoutDesc[2].AlignedByteOffset = 28;
	LayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT; // Vec4과 맞는 사이즈 강제로 맞춤, Vtx::vColor
	LayoutDesc[2].InputSlot = 0;
	LayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[2].InstanceDataStepRate = 0;
	LayoutDesc[2].SemanticName = "TEXCOORD";
	LayoutDesc[2].SemanticIndex = 0;

	if (FAILED(DEVICE->CreateInputLayout(
		LayoutDesc,
		3,
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		InputLayout.GetAddressOf())))
	{
		return E_FAIL;
	}


	return S_OK;
}

int CGraphicShader::CreatePixelShader(const wstring& StrFilePath, const string& PsFuncName)
{
	if (FAILED(D3DCompileFromFile(
		StrFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		PsFuncName.c_str(),
		"ps_5_0",
		D3DCOMPILE_DEBUG,
		0,
		PixelShaderBlob.GetAddressOf(),
		ErrorBlob.GetAddressOf())))
	{
		if (nullptr != ErrorBlob)
		{
			// 문법 오류
			MessageBoxA(nullptr, static_cast<char*>(ErrorBlob->GetBufferPointer()), "픽셀 쉐이더 컴파일 오류", MB_OK);
			return E_FAIL;
		}
		// 경로 오류
		MessageBox(nullptr, L"파일을 찾을 수 없습니다.", L"픽셀 쉐이더 컴파일 오류", MB_OK);
		return E_FAIL;
	}

	if (FAILED(DEVICE->CreatePixelShader(
		PixelShaderBlob->GetBufferPointer(),
		PixelShaderBlob->GetBufferSize(),
		nullptr,
		PixelShader.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicShader::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY InTopology)
{
	Topology = InTopology;
}

void CGraphicShader::Binding()
{
	CONTEXT->IASetInputLayout(InputLayout.Get());
	CONTEXT->IASetPrimitiveTopology(Topology);

	CONTEXT->VSSetShader(VertexShader.Get(), nullptr, 0);
	CONTEXT->PSSetShader(PixelShader.Get(), nullptr, 0);
}
