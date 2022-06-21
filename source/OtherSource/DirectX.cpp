//--- インクルード
#include "DirectX.h"

//==================================================
// 初期化
//--------------------------------------------------
// 引数1	: ウィンドウハンドル
// 引数2	: 描画縦幅
// 引数3	: 横幅
//==================================================
HRESULT CDirectX::Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT	hr = E_FAIL;

	// スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Width = width;
	SwapChainDesc.BufferDesc.Height = height;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = hWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = m_bWindowed = false;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// ドライバ
	D3D_DRIVER_TYPE DriverType;
	D3D_DRIVER_TYPE DriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPU
		D3D_DRIVER_TYPE_WARP,		// WARP
		D3D_DRIVER_TYPE_REFERENCE,	// CPU
	};
	UINT DriverTypeNum = ARRAYSIZE(DriverTypes);

	// 機能レベル
	D3D_FEATURE_LEVEL FeatureLevel;
	D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	UINT FeatureLevelNum = ARRAYSIZE(FeatureLevels);

	// デバイスとスワップチェインの作成
#ifdef _DEBUG
	UINT CreateDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT CreateDeviceFlag = 0;
#endif
	for (UINT i = 0; i < DriverTypeNum; ++i)
	{
		DriverType = DriverTypes[i];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,				// DXGIアダプタ
			DriverType,			// デバイスドライバのタイプ
			NULL,
			CreateDeviceFlag,	// APIレイヤー
			FeatureLevels,		// 機能レベル
			FeatureLevelNum,	// 機能レベル数
			D3D11_SDK_VERSION,	// SDKのバージョン
			&SwapChainDesc,		// スワップチェインの設定
			&m_pSwapChain,		// IDXGISwapChainインターフェイス	
			&m_pDevice,			// ID3D11Deviceインターフェイス
			&FeatureLevel,		// サポートされている機能レベル
			&m_pContext);		// ID3D11DeviceContextインターフェイス
		if (SUCCEEDED(hr)) break;
	}
	if (FAILED(hr)) return hr;

	//--- レンダーターゲット
	// バックバッファ取得
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) return hr;
	// レンダーターゲットビュー作成
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTarget);
	// バックバッファ解放
	SAFE_RELEASE(pBackBuffer);
	if (FAILED(hr)) return hr;
	//--- 深度バッファの作成
	// テクスチャ作成
	ID3D11Texture2D* pDepthTexture;
	D3D11_TEXTURE2D_DESC DepthTextureDesc = {};
	DepthTextureDesc.Width = width;
	DepthTextureDesc.Height = height;
	DepthTextureDesc.MipLevels = 1;
	DepthTextureDesc.ArraySize = 1;
	DepthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthTextureDesc.SampleDesc = SwapChainDesc.SampleDesc;
	DepthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthTextureDesc.CPUAccessFlags = 0;
	DepthTextureDesc.MiscFlags = 0;
	hr = m_pDevice->CreateTexture2D(&DepthTextureDesc, NULL, &pDepthTexture);
	if (FAILED(hr)) return hr;
	// 深度バッファ作成
	D3D11_DEPTH_STENCIL_VIEW_DESC DepthDesc = {};
	DepthDesc.Format = DepthTextureDesc.Format;
	DepthDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthDesc.Flags = 0;
	DepthDesc.Texture2D.MipSlice = 0;
	hr = m_pDevice->CreateDepthStencilView(pDepthTexture, &DepthDesc, &m_pDepth);
	if (FAILED(hr)) return hr;
	// レンダーターゲットに設定
	m_pContext->OMSetRenderTargets(1, &m_pRenderTarget, m_pDepth);

	// サンプラーの設定
	D3D11_SAMPLER_DESC smpDesc;
	ID3D11SamplerState *pSampler;
	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = m_pDevice->CreateSamplerState(&smpDesc, &pSampler);
	if (FAILED(hr)) return hr;
	m_pContext->PSSetSamplers(0, 1, &pSampler);
	SAFE_RELEASE(pSampler);

	//--- ビューポートの設定
	// メイン
	m_ViewPort[0].TopLeftX = 0;
	m_ViewPort[0].TopLeftY = 0;
	m_ViewPort[0].Width = (FLOAT)width;
	m_ViewPort[0].Height = (FLOAT)height;
	m_ViewPort[0].MinDepth = 0.0f;
	m_ViewPort[0].MaxDepth = 0.5f;
	// サブ
	m_ViewPort[1].TopLeftX = width - 100.0f;
	m_ViewPort[1].TopLeftY = 0;
	m_ViewPort[1].Width = (FLOAT)width;
	m_ViewPort[1].Height = (FLOAT)height;
	m_ViewPort[1].MinDepth = 0.5f;
	m_ViewPort[1].MaxDepth = 1.0f;

	//--- ラスタライザの設定
	// 通常
	D3D11_RASTERIZER_DESC RasteDesc = {};
	RasteDesc.FillMode = D3D11_FILL_SOLID;
	RasteDesc.CullMode = D3D11_CULL_NONE;
	RasteDesc.FrontCounterClockwise = false;
	RasteDesc.DepthBias = 0;
	RasteDesc.DepthBiasClamp = 0;
	RasteDesc.SlopeScaledDepthBias = 0;
	RasteDesc.DepthClipEnable = true;
	RasteDesc.ScissorEnable = false;
	hr = m_pDevice->CreateRasterizerState(&RasteDesc, &m_pRasterizer[RASTERIZE::NORMAL]);
	if (FAILED(hr)) return hr;
	// ワイヤーフレーム
	RasteDesc.FillMode = D3D11_FILL_WIREFRAME;
	RasteDesc.CullMode = D3D11_CULL_NONE;
	hr = m_pDevice->CreateRasterizerState(&RasteDesc, &m_pRasterizer[RASTERIZE::WIREFRAME]);
	if (FAILED(hr)) return hr;
	RasteDesc.FillMode = D3D11_FILL_SOLID;
	RasteDesc.CullMode = D3D11_CULL_BACK;
	// 深度バイアス
	RasteDesc.DepthBias = 1;
	RasteDesc.DepthBiasClamp = 1;
	RasteDesc.SlopeScaledDepthBias = 1;
	hr = m_pDevice->CreateRasterizerState(&RasteDesc, &m_pRasterizer[RASTERIZE::DEPTHBIAS]);
	if (FAILED(hr)) return hr;
	RasteDesc.DepthBias = 0;
	RasteDesc.DepthBiasClamp = RasteDesc.SlopeScaledDepthBias = 0;
	// 深度クリップなし
	RasteDesc.DepthClipEnable = false;
	RasteDesc.CullMode = D3D11_CULL_BACK;
	hr = m_pDevice->CreateRasterizerState(&RasteDesc, &m_pRasterizer[RASTERIZE::ZCLIP_OFF]);
	if (FAILED(hr)) return hr;
	RasteDesc.DepthClipEnable = true;
	// シザー矩形
	RasteDesc.ScissorEnable = true;
	D3D10_RECT Rect;
	Rect.top = height * 2 / 5;
	Rect.bottom = height * 4 / 5;
	Rect.left = width * 1 / 5;
	Rect.right = width * 4 / 5 - 30;
	m_pContext->RSSetScissorRects(1, &Rect);
	hr = m_pDevice->CreateRasterizerState(&RasteDesc, &m_pRasterizer[RASTERIZE::SCISSOR]);
	if (FAILED(hr)) return hr;

	// ブレンドステート
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = false;
	BlendState.IndependentBlendEnable = false;
	BlendState.RenderTarget[0].BlendEnable = true;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_BLEND BlendSet[][4] = {
	{
		D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_ONE, D3D11_BLEND_ZERO
		},{
			D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE,
			D3D11_BLEND_ONE, D3D11_BLEND_ZERO
		},
	};
	D3D11_BLEND_OP BlendOp[][2] = {
		{ D3D11_BLEND_OP_ADD, D3D11_BLEND_OP_ADD },
		{ D3D11_BLEND_OP_ADD, D3D11_BLEND_OP_ADD },
	};
	for (int i = 0; i < BLEND::MAX; ++i)
	{
		BlendState.RenderTarget[0].SrcBlend = BlendSet[i][0];
		BlendState.RenderTarget[0].DestBlend = BlendSet[i][1];
		BlendState.RenderTarget[0].BlendOp = BlendOp[i][0];
		BlendState.RenderTarget[0].SrcBlendAlpha = BlendSet[i][2];
		BlendState.RenderTarget[0].DestBlendAlpha = BlendSet[i][3];
		BlendState.RenderTarget[0].BlendOpAlpha = BlendOp[i][1];
		hr = m_pDevice->CreateBlendState(&BlendState, &m_pBlendState[i]);
		if (FAILED(hr)) return hr;
	}
	float Factor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pContext->OMSetBlendState(m_pBlendState[BLEND::ALPHA], Factor, 0xffffffff);

	//// 画面モード切替機能の設定
	//IDXGIFactory* pFactory = NULL;
	//hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
	//if (FAILED(hr)) return hr;
	//hr = pFactory->MakeWindowAssociation(hWnd, 0);
	//if (FAILED(hr)) return hr;

	// トーンカーブ
	SetGamma(false);

	return S_OK;
}

//==================================================
// 終了
//==================================================
void CDirectX::Uninit()
{
	int i;
	for (i = 0; i < BLEND::MAX; ++i)
		SAFE_RELEASE(m_pBlendState[i]);
	for (i = 0; i < RASTERIZE::MAX; ++i)
		SAFE_RELEASE(m_pRasterizer[i]);
	if (m_pContext) m_pContext->ClearState();
	SAFE_RELEASE(m_pDepth);
	SAFE_RELEASE(m_pRenderTarget);
	if (m_pSwapChain) m_pSwapChain->SetFullscreenState(false, NULL);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);
}

//==================================================
// レンダーターゲットのクリア
//==================================================
void CDirectX::ClearRenderTarget()
{
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pContext->ClearRenderTargetView(m_pRenderTarget, ClearColor);
	m_pContext->ClearDepthStencilView(m_pDepth, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

//==================================================
// バックバッファの描画
//==================================================
void CDirectX::DrawBuffer()
{
	HRESULT hr;
	hr = m_pSwapChain->Present(0, 0);
	//if (FAILED(hr)) return hr;
}

//==================================================
// レンダーターゲットの設定
//==================================================
void CDirectX::SetRenderTarget(bool Depth, ID3D11RenderTargetView* pTarget /* = NULL*/)
{
	m_pContext->OMSetRenderTargets(1, (pTarget) ? &pTarget : &m_pRenderTarget,
		(Depth) ? m_pDepth : NULL);
}

//==================================================
// ビューポートの設定
//==================================================
void CDirectX::SetViewport(int num)
{
	if (num < 0 || num > 1) return;
	m_pContext->RSSetViewports(1, &m_ViewPort[num]);
}

//==================================================
// ラスタライザの設定
//==================================================
void CDirectX::SetRasterizer(RASTERIZE::STATE type)
{
	m_pContext->RSSetState(m_pRasterizer[type]);
}

//==================================================
// ブレンドステートの設定
//==================================================
void CDirectX::SetBlendState(BLEND::MODE mode)
{
	float Factor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pContext->OMSetBlendState(m_pBlendState[mode], Factor, 0xffffffff);
}

//==================================================
// トーンカーブの設定
//==================================================
HRESULT CDirectX::SetGamma(bool inv)
{
	HRESULT hr = S_OK;

	if (m_bWindowed) return hr;

	// DXGIOutputインターフェイス取得
	IDXGIOutput* pOutPut;
	hr = m_pSwapChain->GetContainingOutput(&pOutPut);
	if (FAILED(hr)) return hr;
	// 制御点取得
	DXGI_GAMMA_CONTROL_CAPABILITIES GammaCap;
	pOutPut->GetGammaControlCapabilities(&GammaCap);
	if (FAILED(hr))
	{
		pOutPut->Release();
		return hr;
	}
	//--- トーンカーブ設定
	DXGI_GAMMA_CONTROL Gamma;
	Gamma.Offset.Red = 0.0f;
	Gamma.Offset.Green = 0.0f;
	Gamma.Offset.Blue = 0.0f;
	Gamma.Scale.Red = 1.0f;
	Gamma.Scale.Green = 1.0f;
	Gamma.Scale.Blue = 1.0f;
	for (UINT i = 0; i < GammaCap.NumGammaControlPoints; ++i)
	{
		float Point, L;
		L = Point = GammaCap.ControlPointPositions[i];
		if (inv) L = 1 - L;
		Gamma.GammaCurve[i].Red = L;
		Gamma.GammaCurve[i].Green = L;
		Gamma.GammaCurve[i].Blue = L;
	}
	pOutPut->SetGammaControl(&Gamma);
	pOutPut->Release();

	return hr;
}

//==================================================
// スタンバイ状態かどうか
//==================================================
bool CDirectX::IsStandby()
{
	HRESULT hr;

	hr = m_pSwapChain->Present(0, DXGI_PRESENT_TEST);
	if (hr == DXGI_STATUS_OCCLUDED) return true;

	return false;
}

//==================================================
// デバイスの状態チェック
//--------------------------------------------------
// 戻り値	: trueで正常
//==================================================
bool CDirectX::CheckDeviceError()
{
	HRESULT hr = m_pDevice->GetDeviceRemovedReason();
	switch (hr)
	{
		// 正常
	case S_OK: break;
		// 消失 再起動とかなんとか
	case DXGI_ERROR_DEVICE_HUNG:
	case DXGI_ERROR_DEVICE_RESET:
	case DXGI_ERROR_DEVICE_REMOVED:
	case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
	case DXGI_ERROR_INVALID_CALL:
	default:
		return false;
	}

	return true;
}

//==================================================
// テクスチャ生成
//==================================================
ID3D11ShaderResourceView * CDirectX::CreateTexture(D3D11_TEXTURE2D_DESC Desc, D3D11_SUBRESOURCE_DATA Sub, D3D11_SHADER_RESOURCE_VIEW_DESC ViewDesc)
{
	ID3D11ShaderResourceView* pResourceView;
	ID3D11Texture2D *pTex = NULL;
	m_pDevice->CreateTexture2D(&Desc, &Sub, &pTex);
	// シェーダリソースビュー作成
	m_pDevice->CreateShaderResourceView(pTex, &ViewDesc, &pResourceView);

	return pResourceView;
}
