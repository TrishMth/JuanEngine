#include "..\include\DX11.h"

bool Rendering::DX11::Init(const HWND & hWnd)
{
	if (CreateDeviceD3D(hWnd) < 0)
	{
		CleanUpDeviceD3D();
		return false;
	}
	return true;
}

void Rendering::DX11::Run()
{
	CreateDeviceObjects();
	m_pDeviceCon->OMSetRenderTargets(1, &m_pBackBuffer, NULL);
	m_pDeviceCon->ClearRenderTargetView(m_pBackBuffer, m_clearRenderColor);
	UINT stride = sizeof(float) * 6;
	UINT offset = 0;
	m_pDeviceCon->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pDeviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_pDeviceCon->Draw(3, 0);
	m_pSwapChain->Present(0, 0);
}

//JE::Mainframework::IGraphics * Rendering::DX11::CreateGraphics(const HINSTANCE& hInstance)
//{
//	static IGraphics* pDX11 = new DX11(hInstance);
//	return pDX11;
//}

Rendering::DX11::DX11(const HINSTANCE & hInstance)
	: m_pBackBuffer(nullptr), m_pDevice(nullptr), m_pDeviceCon(nullptr), m_pSwapChain(nullptr), m_pVertexShader(nullptr), m_pInputLayout(nullptr)
{

}

Rendering::DX11::~DX11()
{
}

HRESULT Rendering::DX11::CreateDeviceD3D(const HWND & hWnd)
{
	DXGI_SWAP_CHAIN_DESC sCDesc{ 0 };
	sCDesc.BufferDesc.RefreshRate.Numerator = 60;
	sCDesc.BufferDesc.RefreshRate.Denominator = 1;
	sCDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	sCDesc.SampleDesc.Count = 1;

	sCDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sCDesc.BufferCount = 1;
	sCDesc.OutputWindow = hWnd;
	sCDesc.Windowed = true;
	sCDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	const D3D_FEATURE_LEVEL featureLvArray[2] = { D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL featureLv;

	if (D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		createDeviceFlags,
		featureLvArray,
		2,
		D3D11_SDK_VERSION,
		&sCDesc,
		&m_pSwapChain,
		&m_pDevice,
		&featureLv,
		&m_pDeviceCon) != S_OK)
		return E_FAIL;

	CreateRenderTarget();
	return S_OK;
}

void Rendering::DX11::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBuffer);
	SafeRelease(pBackBuffer);
}

void Rendering::DX11::CleanUpDeviceD3D()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pDeviceCon);
	SafeRelease(m_pSwapChain);
}

void Rendering::DX11::InvalidateDeviceObj()
{
	SafeRelease(m_pBackBuffer);
	//DepthStencil gay
}

void Rendering::DX11::CreateDeviceObjects()
{
	if (!m_pDevice)
	{
		return;
	}
	ID3D10Blob* pVShaderBlob = nullptr;
	ID3D10Blob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(L"shader\\VertexShader\\default.vshader", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_4_0", D3DCOMPILE_DEBUG, NULL, &pVShaderBlob, &pErrorBlob);
	if (Failed(hr))
	{
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		SafeRelease(pVShaderBlob);
		SafeRelease(pErrorBlob);
		return;
	}
	hr = m_pDevice->CreateVertexShader(pVShaderBlob->GetBufferPointer(), pVShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	if (Failed(hr))
	{
		SafeRelease(pVShaderBlob);
		SafeRelease(pErrorBlob);
		return;
	}

	D3D11_INPUT_ELEMENT_DESC inputEleDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	hr = m_pDevice->CreateInputLayout(inputEleDesc, ARRAYSIZE(inputEleDesc), pVShaderBlob->GetBufferPointer(), pVShaderBlob->GetBufferSize(), &m_pInputLayout);
	if (Failed(hr))
	{
		SafeRelease(pVShaderBlob);
		SafeRelease(pErrorBlob);
		return;
	}
	SafeRelease(pVShaderBlob);

	m_pDeviceCon->IASetInputLayout(m_pInputLayout);

	ID3D10Blob* pPShaderBlob = nullptr;
	hr = D3DCompileFromFile(L"shader\\PixelShader\\default.pshader", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_4_0", D3DCOMPILE_DEBUG, NULL, &pPShaderBlob, &pErrorBlob);
	if (Failed(hr))
	{
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		SafeRelease(pPShaderBlob);
		SafeRelease(pErrorBlob);
		return;
	}
	hr = m_pDevice->CreatePixelShader(pPShaderBlob->GetBufferPointer(), pPShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	if (Failed(hr))
	{
		SafeRelease(pPShaderBlob);
		SafeRelease(pErrorBlob);
		return;
	}
	SafeRelease(pPShaderBlob);
	SafeRelease(pErrorBlob);

	D3D11_VIEWPORT viewPort{ 0 };
	viewPort.Height = 200;
	viewPort.Width = 200;

	m_pDeviceCon->RSSetViewports(1, &viewPort);

	m_pDeviceCon->VSSetShader(m_pVertexShader, NULL, NULL);
	m_pDeviceCon->PSSetShader(m_pPixelShader, NULL, NULL);

	InitGraphics();
}

void Rendering::DX11::InitGraphics()
{
	float DX11Vertices[] = {
		//X, Y, RGBA
		0.9f, -0.9f, 1, 0, 1, 1,
		-0.9f, -0.9f, 0, 1, 1, 1,
		-0.9f, 0.9f, 0, 0, 1,1,
	};

	D3D11_BUFFER_DESC bufferDesc{ 0 };
	bufferDesc.ByteWidth = sizeof(DX11Vertices) * 3;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subresourceData;

	hr = m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pVertexBuffer);
	if (Failed(hr))
	{
		OutputDebugStringW(L"FailedVertexBuffer");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	hr = m_pDeviceCon->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed Mapping");
		return;
	}

	memcpy(mappedSubresource.pData, DX11Vertices, sizeof(DX11Vertices) * 3);

	m_pDeviceCon->Unmap(m_pVertexBuffer, NULL);
}

bool Rendering::DX11::Failed(HRESULT aResult)
{
	if (FAILED(aResult))
	{
		LPTSTR buffer;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)aResult, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

		MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR);
		LocalFree(buffer);
		return true;
	}
	return false;
}
