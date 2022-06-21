//=======================================================================
// Score.h
//-----------------------------------------------------------------------
// 作成者 : 柳沢帆貴
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/06	作成
//			
//
//=======================================================================
#pragma once

//--- インクルード部
#include "Transform.h"
#include "Pol2D.h"

//--- クラス
class Score
{
public:
	static Score *GetInstance()
	{
		static Score instance;
		return &instance;
	}

	void Init();
	void Update();
	void Draw();

	void SetA()
	{
		for (int i = 0; i < 4; i++)
		{
			m_DrawCnt = 300;
			m_Pol[i].m_a = 1;
			m_Pol[i].m_Transform.Move.y = 1.0f;
			m_Pol[i].m_Transform.Position.y = -100;
			m_Frme.m_a = 1;
		}
		for (int i = 0; i < 3; i++)
		{
			m_ComboPoly[i].m_a = 1;
		}
	}

	Float3 m_Pos;
	int m_DrawScore;		//描画する獲得スコアの値
	Pol2D m_ComboPoly[3];	//コンボ数描画
	Pol2D m_Pol[4];			//獲得したスコアの描画用
	Pol2D m_TotalPol[10];	//合計スコアの描画用
	Pol2D m_Frme;			//描画スコアのフレーム
	int m_TotalScore;		//現在の獲得しているスコアの合計
	int m_curCombo;			//現在のコンボ数
	int m_oldCombo;			//1フレーム前のコンボ数
	int m_MaxCombo;			//最大コンボ数
	int m_comboCnt;			//コンボの途切れる間隔のカウント
	int m_curIdx;			//添え字用

private:
	Score() {}
	~Score() {}
	unsigned int m_ComboDigits;	//描画するコンボの桁数
	unsigned int m_Digits;		//描画するスコアの桁数
	int m_TotalDigits;			//描画するトータルスコアの桁数
	int m_DrawCnt;				//描画する時間
};
//桁数チェック
unsigned int GetDigit(unsigned int num);
