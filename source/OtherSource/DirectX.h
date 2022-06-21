//=======================================================================
// DirectX.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// DirectXの処理
//-----------------------------------------------------------------------
// 更新履歴
//	2021/01/02	作成
//			04	ラスタライザ処理追加
//			
//=======================================================================
#pragma once

//--- インクルード
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

//--- マクロ
#define GET_DX	(CDirectX::GetInstance())
#define SAFE_RELEASE(p) {if(p) p->Release(); p = NULL;}

//--- 列挙体
// ラスタライザ設定
namespace RASTERIZE
{
	enum STATE
	{
		NORMAL,		// 通常
		WIREFRAME,	// ワイヤーフレーム
		DEPTHBIAS,	// 深度バイアスあり
		ZCLIP_OFF,	// 深度クリップなし
		SCISSOR,	// シザー矩形

		MAX
	};
}
// ブレンドステート設定
namespace BLEND
{
	enum MODE
	{
		ALPHA,
		ADD,
		MAX
	};
}

//--- クラス
class CDirectX
{
	CDirectX() {}
	~CDirectX() {}
public:
	inline static CDirectX* GetInstance()
	{
		static CDirectX instance;
		return &instance;
	}

	HRESULT Init(HWND hWnd, UINT width, UINT height);
	void Uninit();

	void ClearRenderTarget();
	void DrawBuffer();

	void SetRenderTarget(bool Depth, ID3D11RenderTargetView* pTarget = NULL);
	void SetViewport(int num = 0);
	void SetRasterizer(RASTERIZE::STATE type = RASTERIZE::NORMAL);
	void SetBlendState(BLEND::MODE mode);
	HRESULT SetGamma(bool inv);

	bool IsStandby();
	bool CheckDeviceError();

	inline ID3D11Device*		GetDevice() { return m_pDevice; }
	inline ID3D11DeviceContext*	GetContext() { return m_pContext; }

	ID3D11ShaderResourceView* CreateTexture(D3D11_TEXTURE2D_DESC Desc, D3D11_SUBRESOURCE_DATA Sub, D3D11_SHADER_RESOURCE_VIEW_DESC ViewDesc);

private:

	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTarget;
	ID3D11DepthStencilView*	m_pDepth;
	ID3D11RasterizerState*	m_pRasterizer[RASTERIZE::MAX];
	ID3D11BlendState*		m_pBlendState[BLEND::MAX];
	D3D11_VIEWPORT			m_ViewPort[2];

	bool m_bWindowed;
};
