#include "Direct3D.h"
#include "framework.h"
#include <windows.h>

bool Direct3D::Initialize(HWND hWnd, int width, int height) {

	ComPtr<IDXGIFactory> factory;

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory)))) {
		return false;
	}

	UINT createFlags = 0;

#ifdef _DEBUG
	createFlags != D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	D3D_FEATURE_LEVEL featureLevel;
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_divice,
		&featureLevel,
		&m_deviceContext
	))) {
		return false;
	}
	
	/// <summary>
	/// スワップチェーン設定データ
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	DXGI_SWAP_CHAIN_DESC scDesc = {};

	scDesc.BufferDesc.Width = width; // 画面幅
	scDesc.BufferDesc.Height = height; // 画面高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // バッファ形式
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.RefreshRate.Numerator = 0;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.SampleDesc.Count = 1; // MSAA 不使用
	scDesc.SampleDesc.Quality = 0; // MSAA 不使用
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // バッファ使用方法
	scDesc.BufferCount = 2; // バッファ数
	scDesc.OutputWindow = hWnd;
	scDesc.Windowed = true; // ウィンドウモード
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// スワップチェーンの作成
	if (FAILED(factory->CreateSwapChain(m_divice.Get(), &scDesc, &m_swapChain))) {
		return false;
	}

	// スワップチェーンからバックバッファリソースの取得
	ComPtr<ID3D11Texture2D> pBackBuffer;
	if (FAILED(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)))) {
		return false;
	}

	// バックバッファリソース用のRTVを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = scDesc.BufferDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	if (FAILED(m_divice->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, &m_backBufferView))) {
		return false;
	}

	m_deviceContext->OMSetRenderTargets(1, m_backBufferView.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f };
	m_deviceContext->RSSetViewports(1, &vp);

	// シェーダー作成 =============================================================================
	//頂点シェーダーの読み込みとコンパイル
	ComPtr<ID3DBlob> compiledVS;
	if (FAILED(D3DCompileFromFile(L"Shader/SampleShader.hlsl", nullptr, nullptr, "VT", "vs_5_0", 0, 0, &compiledVS, nullptr))) {
		return false;
	}

	//ピクセルシェーダーの読み込みとコンパイル
	ComPtr<ID3DBlob> compiledPS;
	if (FAILED(D3DCompileFromFile(L"Shader/SampleShader.hlsl", nullptr, nullptr, "PixcelShader", "ps_5_0", 0, 0, &compiledPS, nullptr))) {
		return false;
	}

	//頂点シェーダー作成
	if (FAILED(m_divice->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_VS))) {
		return false;
	}

	//ピクセルシェーダー作成
	if (FAILED(m_divice->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_PS))) {
		return false;
	}

	/// <summary>
	/// 頂点毎の詳細な情報
	/// </summary>
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0
		},
	};

	// 頂点インプットレイアウト作成
	if (FAILED(m_divice->CreateInputLayout(&layout[0], layout.size(), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_InputLayout))) {
		return false;
	}


	return true;
}