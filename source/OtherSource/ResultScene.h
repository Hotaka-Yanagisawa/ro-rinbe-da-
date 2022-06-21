//=======================================================================
// ResultScene.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/11	作成
//
//=======================================================================
#pragma once

//--- インクルード
#include "Scene.h"
#include "PolygonList.h"
#include "Number.h"
#include "MySound.h"

//--- 列挙体
enum RESULT_STEP
{
	RESULT_STEP_BEGIN = -1,
	// スコアの加算
	ADD_SCORE_ENEMY,
	ADD_SCORE_TIME,
	ADD_SCORE_LIFE,
	ADD_SCORE_CLEAR,
	ADD_SCORE_MISSION,

	RESULT_STEP_MAX
};

//--- クラス
class ResultScene : public Scene
{
public:
	ResultScene() {}
	~ResultScene() {}

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

private:
	int m_nType;

	int m_nScore;
	int m_nTotalScore;
	int m_nTime;		//残り時間
	int m_nMaxCombo;	//最大コンボ数
	int m_nHp;			//残りHP
	int m_nEnemyNum;	//巻込んだ数の合計

	RESULT_STEP m_Step;
	int m_nWait;
	int m_nAdd;

	PolygonList m_PolList;
	PolygonList m_Result;
	Number m_Number[RESULT_STEP_MAX];

	CSound m_Sound;
	CSound m_SE;
	CSound m_SE2;

};
