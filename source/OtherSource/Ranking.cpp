//--- インクルード
#include "Ranking.h"
#include <fstream>

//==================================================
// データ読み込み
//--------------------------------------------------
// 引数		: ファイル名
//==================================================
void Ranking::Load(const char* FileName)
{
	std::ifstream file(FileName);
	// エラー
	if (!file) return;

	// ステージ×データ数分読み込み
	for (int j = 0; j < STAGE_NUM; ++j)
		for (int i = 0; i < SAVE_NUM; ++i)
			file >> m_Data[j].Score[i];
}

//==================================================
// データ保存
//--------------------------------------------------
// 引数		: ファイル名
//==================================================
void Ranking::Save(const char* FileName)
{
	std::ofstream file(FileName);
	// エラー
	if (!file) return;

	// ステージ×データ数分書き込み
	for (int j = 0; j < STAGE_NUM; ++j)
		for (int i = 0; i < SAVE_NUM; ++i)
			file << m_Data[j].Score[i] << std::endl;
}

//==================================================
// スコアを反映
//--------------------------------------------------
// 引数		: スコア
//==================================================
void Ranking::SetScore(int Value, int StageNum)
{
	// 三位に入るかチェック
	if (Value > m_Data[StageNum].Score[2])
		m_Data[StageNum].Score[2] = Value;

	// 降順ソート
	for (int i = SAVE_NUM - 1; i > 0; --i)
	{
		if (m_Data[StageNum].Score[i] > m_Data[StageNum].Score[i - 1])
			Swap(m_Data[StageNum].Score[i], m_Data[StageNum].Score[i - 1]);
	}

}

//==================================================
// 値入れ替え
//--------------------------------------------------
// 引数1, 2	: 値
//==================================================
void Ranking::Swap(int& a, int& b)
{
	int Tmp = a;
	a = b;
	b = Tmp;
}

