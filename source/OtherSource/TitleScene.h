//=======================================================================
// TitleScene.h
//-----------------------------------------------------------------------
// 作成者 : 藤田拓也
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/01	作成
//			10	PUSHENTER
//			23	背景スクロール
//
//=======================================================================
#pragma once

//--- インクルード
#include "Scene.h"
#include "PolygonList.h"
#include "MySound.h"

//--- クラス
class TitleScene : public Scene
{
public:
	TitleScene() {}
	~TitleScene() {}

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

private:
	CSound m_Sound;
	CSound m_SE;
	PolygonList m_PolList;

	//----------------
	float m_timer;
	//--------------
	bool m_Color;
	float m_ColorA;
	bool m_AlphaFlag;

	//--------------
	float m_RogoRadian;//角度
	float m_RogoRadius;//半径

	bool m_RogoFlag;

};
