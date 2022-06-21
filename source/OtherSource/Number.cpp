//--- インクルード
#include "Number.h"

//==================================================
// 初期化
//--------------------------------------------------
// 引数1	: 最大桁
// 引数2	: 初期値 デフォルト0
//==================================================
void Number::Init(int MaxRank, int Num /*= 0*/)
{
	//m_NumPol = new Pol2D[MaxRank];

	// 初期設定
	if (MaxRank > MAX_NUMBER_RANK) MaxRank = MAX_NUMBER_RANK;
	//m_nMaxRank = MaxRank;
	m_nMaxRank = 9;
	m_nNumber = Num;
	m_nTime = 1;
	m_nAddScore = 0;
	SetPos(0, 0);
	SetSize(20.0f);
	SetDist(30.0f);
	m_bDrawZero = true;
	for (int i = 0; i < m_nMaxRank; ++i)
	{
		m_NumPol[i].Init();
		m_NumPol[i].m_bParallel = true;
		m_NumPol[i].SetTexture(TEX_PNG("Number2"));
		m_NumPol[i].m_fSplitX = 5;
		m_NumPol[i].m_fSplitY = 2;
	}

	m_bUpdate = true;
	Update();
}

//==================================================
// 終了
//==================================================
void Number::Uninit()
{
	//if (!m_NumPol) return;

	for (int i = 0; i < m_nMaxRank; ++i) m_NumPol[i].Uninit();

//	delete[] m_NumPol;
}

//==================================================
// 更新
//==================================================
void Number::Update()
{
	// 座標
	for (int i = 0; i < m_nMaxRank; ++i)
	{
		m_NumPol[i].m_Transform.Position.x = i * m_fDist + m_fPosX;
		m_NumPol[i].m_Transform.Position.y = m_fPosY;
	}

	// カウント
	if(m_nAddScore > 0)
	{
		if (m_nAddScore > m_nTime)
		{
			m_nNumber += m_nAddScore / m_nTime;
			m_nAddScore -= m_nAddScore / m_nTime;
		}
		else
		{
			m_nNumber += m_nAddScore;
			m_nAddScore = 0;
		}

		m_bUpdate = true;
	}

	// UV座標
	if (m_bUpdate)
	{
		int nNum = m_nNumber;
		for (int i = m_nMaxRank - 1; i > -1; --i)
		{
			int num = nNum % 10;
			// UV設定
			m_NumPol[i].m_fTexCoordX = float(num % (int)m_NumPol[i].m_fSplitX);
			m_NumPol[i].m_fTexCoordY = (float)int(num / m_NumPol[i].m_fSplitX);
			m_NumPol[i].Update();

			nNum /= 10;
		}

		m_bUpdate = false;
	}
}

//==================================================
// 描画
//==================================================
void Number::Draw()
{
	bool zero = false;
	for (int i = 0; i < m_nMaxRank; ++i)
	{
		// 0描画しないフラグ
		if ((i != m_nMaxRank - 1) && (!m_bDrawZero))
			if (m_NumPol[i].m_fTexCoordX == 0 && m_NumPol[i].m_fTexCoordY == 0)
			{
				if (!zero) continue;
			}
			else
			{
				zero = true;
			}

		m_NumPol[i].Draw();
	}
}

//==================================================
// セッター
//==================================================
void Number::SetNumStep(int Num, int Time /* = 1*/)
{
	// 最大桁チェック
	int max = (int)pow(10, m_nMaxRank) - 1;
	if (Num > max) Num = max;

	// カウントなし
	if (Time == 1)
	{
		m_nNumber = Num;
		m_bUpdate = true;
	}
	// カウントあり
	else
	{
		m_nAddScore = Num;
		m_nTime = Time;
	}
}
void Number::SetNum(int Num)
{
	m_nNumber = Num;
	m_nAddScore = 0;
	m_nTime = 1;
}
void Number::SetPos(float x, float y)
{
	m_fPosX = x; m_fPosY = y;
}
void Number::SetSize(float x, float y /*= -1.0f*/)
{
	for (int i = 0; i < m_nMaxRank; ++i)
	{
		m_NumPol[i].m_Transform.Size.x = x;
		// Y省略時、Xに合わせる
		if (y == -1.0f)
			m_NumPol[i].m_Transform.Size.y = x;
		else
			m_NumPol[i].m_Transform.Size.y = y;
	}
}
void Number::SetDist(float d)
{
	m_fDist = d;
}
void Number::SetMove(float x, float y)
{
	m_fPosX += x;
	m_fPosY += y;
}
void Number::SetColor(float r, float g, float b, float a)
{
	for (int i = 0; i < m_nMaxRank; ++i)
	{
		m_NumPol[i].m_r = r;
		m_NumPol[i].m_g = g;
		m_NumPol[i].m_b = b;
		m_NumPol[i].m_a = a;
	}
}
void Number::DrawZero(bool flg)
{
	m_bDrawZero = flg;
}
