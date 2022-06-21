//=======================================================================
// Vitality.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/24	作成
//			26	ビルボード描画
//
//=======================================================================
#pragma once

//--- インクルード部
#include "Component.h"
#include "Transform.h"

//--- クラス
class Vitality : public Component
{
public:

	Vitality() {}
	~Vitality() {}

	void Init() override;

	void Draw() override;

	float m_fMaxHp;
	float m_fHp;

	Transform m_Transform;

	void SetHP(int, bool = true);

private:

};
