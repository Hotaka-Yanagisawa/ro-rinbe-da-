//=======================================================================
// Fly.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/20	作成
//			23	ぶつかったら揺れる処理
//			27	影のテクスチャ描画
//		 12/16	Transformをパブリックに
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Component.h"
#include "Transform.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "Vitality.h"
#include "MySound.h"

class Fly : public Component
{
public:
	Fly() {}
	~Fly() {}

	void Init() override;

	void Update() override;
	void Draw() override;

	void OnCollisionEnter(Object* pObj) override;

	Transform* m_Transform;
private:
	Vitality *m_Vitality;

	float m_fAngle;
	float m_fRadius;
	float m_nCount;
	bool m_bFlag;


	ID3D11ShaderResourceView* m_pTexture;

	DrawBuffer m_Buffer;
	CSound m_Sound;
	CSound m_SE;
};
