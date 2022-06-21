//=======================================================================
// SelectScene.h
//-----------------------------------------------------------------------
// 作成者 : 中村洸介
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/04	タイトル後のステージ選択画面実装のため作成
//			11	一応基盤となる所はできたと思う。かなり時間がかかってしまった。反省
//				ステージの画像を増やしても問題なく動作するようにしてあるつもり。
//				回転に遅れ表現を実装。
//			13	ランキングのとこ追加(水野)
//			16	ランキングと選択ステージ静的にした(水野)
//
//=======================================================================
#pragma once

//--- インクルード
#include "Scene.h"
#include "PolygonList.h"
#include "Ranking.h"
#include <array>
#include "MySound.h"

//--- 定数
#define SCORE_FILE	("Data/Ranking.txt")

//--- 列挙体
namespace SELECTSCENE
{
	enum STEP
	{
		SELECT,
		STANDBY,

		MAX
	};
}

//--- クラス
class SelectScene : public Scene
{
public:
	SelectScene() {}
	~SelectScene() {}

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

	static Ranking m_Ranking;

	static int m_nSelect;

private:

	float m_radius;
	int m_nTexNum;
	float m_fDistanceAngle;

	float m_fpLatePositonY;
	float *m_fpPersonalAngle;
	float *m_fpLatePersonalAngle;
	Pol2D *m_pSelectSceneImage;

	int m_nTimer;
	int m_nReturnTime;

	std::array<Pol2D, 2> m_Cursor;

	PolygonList m_PolList;
	PolygonList m_SelectList;
	PolygonList m_ScorePol[STAGE_NUM];
	PolygonList m_Star;
	PolygonList m_Plate;

	SELECTSCENE::STEP m_Step;

	CSound m_Sound;
	CSound m_SE;
};
