//=======================================================================
// Control.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/17	作ってみたくて作成
//			30	移動方向をカメラの方向を基準になるようにプログラム（中村
//		/12/01	ゲームパッドとキーボード入力で移動できるように変更 (中村
//		/01/08  プレイヤーの魔法陣（symbol）の移植
//
//=======================================================================
#pragma once

//--- インクルード　
#include "Component.h"
#include "Transform.h"
#include "Pol2D.h"

//--- クラス
class Control : public Component
{
public:

	Control() {}
	~Control() {}

	void Init() override;
	void Uninit() override;

	void Update() override;
	void Draw() override;

private:

	Transform* m_Transform;
	Pol2D m_Symbol;

	Pol2D m_Aim;

};
