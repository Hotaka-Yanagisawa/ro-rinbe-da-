#include "Score.h"
#include "Defines.h"

//--- 定数定義 
#define COMBO_TIME (300)	//コンボの途切れる間隔

void Score::Init()
{
	m_MaxCombo = m_DrawScore = m_TotalDigits = m_curIdx = m_curCombo = m_oldCombo = m_TotalScore = 0;
	
	m_DrawCnt = 300;
	m_Digits = 0;
	m_comboCnt = COMBO_TIME;

	m_Frme.Init();
	m_Frme.m_bParallel = true;
	m_Frme.SetTexture(TEX_PNG("Combo"));
	m_Frme.m_Transform.Position = { SCREEN_WIDTH / 2 - 130, 120, 0 };
	m_Frme.m_Transform.Size = 300;
	//m_Frme.m_a = 0;
	//獲得スコア
	for (int i = 0; i < 10; i++)
	{
		m_Pol[i].Init();
		m_Pol[i].m_bParallel = true;
		m_Pol[i].SetTexture(TEX_PNG("Number2"));
		m_Pol[i].m_Transform.Position = { 0, 10, 0 };
		m_Pol[i].m_Transform.Size = 60;
		m_Pol[i].m_fSplitX = 5;
		m_Pol[i].m_fSplitY = 2;
		m_Pol[i].m_fTexCoordX = -1;
		m_Pol[i].m_fTexCoordY = -1;
		//m_Pol[i].m_r = 0;
	}

	for (int i = 0; i < 3; i++)
	{	
		//コンボ数
		m_ComboPoly[i].Init();
		m_ComboPoly[i].m_bParallel = true;
		m_ComboPoly[i].SetTexture(TEX_PNG("Number2"));
		m_ComboPoly[i].m_Transform.Position = { -9999, -9999, -9999 };
		m_ComboPoly[i].m_Transform.Size = 150;
		m_ComboPoly[i].m_fSplitX = 5;
		m_ComboPoly[i].m_fSplitY = 2;
		m_ComboPoly[i].m_g = 0;
	}


	for (int i = 0; i < 10; i++)
	{
		//トータルスコア
		m_TotalPol[i].Init();
		m_TotalPol[i].m_bParallel = true;
		m_TotalPol[i].SetTexture(TEX_PNG("Number2"));
		m_TotalPol[i].m_Transform.Position = { -9999, -9999, -9999 };
		m_TotalPol[i].m_Transform.Size = 30;
		m_TotalPol[i].m_fSplitX = 5;
		m_TotalPol[i].m_fSplitY = 2;
		//m_TotalPol[i].m_fTexCoordX = -1;
		//m_TotalPol[i].m_fTexCoordY = -1;
		m_TotalPol[i].m_r = 0;
	}
}

void Score::Update()
{
	if (m_curCombo > m_MaxCombo) m_MaxCombo = m_curCombo;
	//コンボ数が増えているか調べる
	//増えてたらカウントリセット、増えていないならカウント減らす
	if (m_curCombo != m_oldCombo)	m_comboCnt = COMBO_TIME;
	else if (m_curCombo > 0)		m_comboCnt--;

	//300フレームコンボが途切れたら０コンボにする
	if (m_comboCnt < 1)
	{
		m_comboCnt = COMBO_TIME;
		m_curCombo = 0;
	}
	//過去のコンボ更新
	m_oldCombo = m_curCombo;
	
	//コンボの桁数チェック
	m_ComboDigits = GetDigit(m_curCombo);
	int tempCombo = m_curCombo;
	int Rank = 0;
	while (tempCombo> 0)
	{
		int num = tempCombo % 10;
		//画像のuv設定
		m_ComboPoly[Rank].m_fTexCoordX = num % 5;
		m_ComboPoly[Rank].m_fTexCoordY = num / 5;
		//次の文字にするため添え字の値増やす
		++Rank;
		//桁減らし
		tempCombo /= 10;
	}


	//巻込んでいなかったらm_DrawScoreの値は０のままなのでコンテニューする
	if (m_DrawScore != 0)
	{
		if (m_DrawScore > 9000)m_DrawScore = 9000;
		//獲得したスコアの桁数チェック
		m_Digits = GetDigit(m_DrawScore);
		int tempScore = m_DrawScore;
		int Rank = 0;
		while (tempScore > 0)
		{
			int num = tempScore % 10;
			//画像のuv設定
			m_Pol[Rank].m_fTexCoordX = num % 5;
			m_Pol[Rank].m_fTexCoordY = num / 5;
			//次の文字にするため添え字の値増やす
			++Rank;
			//桁減らし
			tempScore /= 10;
		}
	}

	m_TotalDigits = 0;
	int tempScore = m_TotalScore;
	int index = 0;
	if (tempScore == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			m_TotalPol[index].m_fTexCoordX = 0;
			m_TotalPol[index].m_fTexCoordY = 0;
			++index;
			++m_TotalDigits;
		}
	}
	while (tempScore > 0)
	{
		int num = tempScore % 10;
		//画像のuv設定
		m_TotalPol[index].m_fTexCoordX = num % 5;
		m_TotalPol[index].m_fTexCoordY = num / 5;
		//次の文字にするため添え字の値増やす
		++index;

		++m_TotalDigits;
		//桁減らし
		tempScore /= 10;
	}

	//コンボ数のポリゴンの更新
	//桁数分ループを行う
	for (int i = 0; i < m_ComboDigits; i++)
	{
		//m_ComboPoly[i].m_Transform.Position = m_Pos;
		m_ComboPoly[i].Update();
	}

	//獲得スコアのポリゴンの更新
		//桁数分ループを行う
	for (int i = 0; i < m_Digits; i++)
	{
		//m_Pol[i].m_Transform.Position = m_Pos;
		m_Pol[i].m_Transform.Position.x = SCREEN_WIDTH / 2 -40 - i * 60.0f;
		m_Pol[i].m_Transform.Position.y += m_Pol[i].m_Transform.Move.y;
		m_Pol[i].m_Transform.Move.y -= 2.0f / 300.0f;
		m_Pol[i].Update();
	}

	//トータルスコアのポリゴンの更新
	for (int j = 0; j < 6; j++)
	{
		m_TotalPol[j].m_Transform.Position.x = -SCREEN_WIDTH / 2 + 170 - j * 30.0f;
		m_TotalPol[j].m_Transform.Position.y = 270;
		m_TotalPol[j].Update();
	}
	m_Frme.Update();
}

void Score::Draw()
{
	m_Frme.Draw();
	//トータルスコアのポリゴンの更新
	for (int i = 0; i < 6; i++)
	{
		m_TotalPol[i].Draw();
	}

	float AddX;
	for (int i = 0; i < m_ComboDigits; i++)
	{
		if (m_ComboDigits == 1)	AddX = 100.0f;
		if (m_ComboDigits == 2) AddX = 75.0f;
		if (m_ComboDigits == 3) AddX = 50.0f;
		//if (m_curCombo % 10 == 0)
		//{
		//	AddX = 500.0f;
		//}
		m_ComboPoly[i].m_Transform.Size = AddX;
		m_ComboPoly[i].m_Transform.Position.x = 550.0f - i * AddX;
		if (m_ComboDigits == 1)	m_ComboPoly[i].m_Transform.Position.x = 500.0f - i * AddX;
		if (m_ComboDigits == 3) m_ComboPoly[i].m_Transform.Position.x = 560.0f - i * AddX;
		m_ComboPoly[i].m_Transform.Position.y = 110;
		m_ComboPoly[i].Draw();
	}
	//巻込んでいなかったらm_DrawScoreの値は０のままなのでコンテニューする
	if (m_DrawScore != 0)
	{
		//獲得したスコアの桁数チェック
		m_Digits = GetDigit(m_DrawScore);
		//桁数分Drawする
		for (int i = 0; i < m_Digits; i++)
		{
			if (m_Pol[i].m_fTexCoordX == -1) continue;
			m_Pol[i].Draw();
		}
		//Draw時間カウント
		m_DrawCnt--;
		//Draw時間カウントが0になると値初期化
		if (m_DrawCnt < 1)
		{
			m_DrawCnt = 300;
			m_DrawScore = 0;
			//m_Frme.m_a = 0;
			for (int i = 0; i < m_Digits; i++)
			{
				m_Pol[i].m_a = 0;
			}
		}
		else
		{
			for (int i = 0; i < m_Digits; i++)
			{
				m_Pol[i].m_a -= 1.0f / 300.0f;
			}
			for (int i = 0; i < 3; i++)
			{
				m_ComboPoly[i].m_a -= 1.0f / 300.0f;
			}
		}
	}
}

//桁数チェック
unsigned int GetDigit(unsigned int num)
{
	unsigned int digit = 0;
	while (num != 0)
	{
		num /= 10;
		digit++;
	}
	return digit;
}
