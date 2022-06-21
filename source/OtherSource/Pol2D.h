//=======================================================================
// Pol2D.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/28	作成
//		 12/05	アニメの処理追加
//			24	描画方法フラグ追加
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Transform.h"
#include "Texture.h"
#include "DrawBuffer.h"

//--- 列挙体
namespace ANIME
{
	enum STATUS
	{
		NO,		// アニメなし
		PLAY,	// 再生中
		STOP,	// 停止中
		END,	// 終了した

		MAX
	};
}

//--- クラス
class Pol2D
{
public:
	Pol2D() {}
	~Pol2D() {}

	void Init();
	void Uninit();

	void Update();
	void Draw();

	// 描画情報
	Transform m_Transform;
	float m_r, m_g, m_b, m_a;
	float m_fSplitX, m_fSplitY;
	float m_fTexCoordX, m_fTexCoordY;

	// 描画方法フラグ
	bool m_bBillboard;
	bool m_bParallel;
	bool m_bZSort;

	// 設定
	void SetTexture(const char*);
	void SetAnime(int Start, int Num, int Pace, bool Loop = true);

	// アニメーション用変数
public:
	ANIME::STATUS m_AnimeStatus;
	bool m_bLoop;
private:
	int m_nCount;
	int m_nPace;
	int m_nStartX, m_nStartY;
	int m_nEndX, m_nEndY;

private:
	// 頂点情報
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
	};
	Vertex* m_Vertex;

	ID3D11ShaderResourceView* m_pTexture;
	DrawBuffer m_Buffer;
};
