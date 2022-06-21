//=======================================================================
// Ranking.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/13	作成
//			
//=======================================================================
#pragma once

//--- 定数
#define MAX_RANK	(6)	// 最大桁
#define SAVE_NUM	(3)	// 保存する数
#define STAGE_NUM	(3)	// ステージの数

//--- 構造体
struct RANKING_DATA
{
	int Score[SAVE_NUM];
};

//--- クラス
class Ranking
{
public:
	Ranking() {}
	~Ranking() {}

	void Load(const char* FileName);
	void Save(const char* FileName);

	void SetScore(int Value, int StageNum);

	RANKING_DATA m_Data[STAGE_NUM];

private:
	void Swap(int&, int&);
};
