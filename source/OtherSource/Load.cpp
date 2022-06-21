//--- インクルード
#include "Load.h"
#include "Texture.h"
#include "ModelManager.h"
#include <thread>
#include "Shader.h"

void Texture();
void Model();
void Count();

Pol2D m_Number[2];

//==================================================
// 全読み込み
//==================================================
void Load::All()
{
	if (m_bEnd) return;

	// カウント準備
	for (int i = 0; i < 2; i++)
	{
		m_Number[i].Init();
		m_Number[i].m_bParallel = true;
		m_Number[i].SetTexture(TEX_PNG("Number"));
		m_Number[i].m_Transform.Position = { 0 - i * 40.0f, 0, 0 };
		m_Number[i].m_Transform.Size = { 70, 80, 0 };
		m_Number[i].m_fSplitX = 5; m_Number[i].m_fSplitY = 2;
		m_Number[i].m_r = 0.1f;
	}
	// スレッド生成
	std::thread th_a(Texture);
	std::thread th_b(Model);
	std::thread th_c(Count);
	// 待機
	th_a.join();
	th_b.join();
	th_c.join();
	// カウント終了
	for (int i = 0; i < 2; i++) m_Number[i].Uninit();
	m_bEnd = true;
}

//==================================================
// テクスチャ全読み込み
//==================================================
void Texture()
{
	if (false) return;

	TEXTURE->Load(TEX_PNG("BlueSky"));
	TEXTURE->Load(TEX_PNG("BossBar"));
	TEXTURE->Load(TEX_PNG("Clear"));
	TEXTURE->Load(TEX_PNG("Cloud1"));
	TEXTURE->Load(TEX_PNG("Count"));
	TEXTURE->Load(TEX_PNG("Cursor"));
	TEXTURE->Load(TEX_PNG("GOver"));
	TEXTURE->Load(TEX_PNG("Mark"));
	TEXTURE->Load(TEX_PNG("Modoru"));
	TEXTURE->Load(TEX_PNG("Number"));
	TEXTURE->Load(TEX_PNG("Number2"));
	TEXTURE->Load(TEX_PNG("PressButton"));
	TEXTURE->Load(TEX_PNG("Ranking"));
	TEXTURE->Load(TEX_PNG("ResultBack"));
	TEXTURE->Load(TEX_PNG("ResultWindow"));
	TEXTURE->Load(TEX_PNG("SandWatch"));
	TEXTURE->Load(TEX_PNG("Shadow"));
	TEXTURE->Load(TEX_PNG("Smoke"));
	TEXTURE->Load(TEX_PNG("StageImage"));
	TEXTURE->Load(TEX_PNG("Star"));
	TEXTURE->Load(TEX_PNG("Start"));
	TEXTURE->Load(TEX_PNG("Susumu"));
	TEXTURE->Load(TEX_PNG("Title"));
	TEXTURE->Load(TEX_PNG("TmplBar"));
	TEXTURE->Load(TEX_PNG("Tuti"));

}

//==================================================
// モデル全読み込み
//==================================================
void Model()
{
	if (false) return;

	MODEL->Load(FILE_MODEL("Field/Steppe"));

	MODEL->Load(FILE_MODEL("Temple/Base"));
	MODEL->Load(FILE_MODEL("Temple/Core"));
	MODEL->Load(FILE_MODEL("Temple/Floor1"));
	MODEL->Load(FILE_MODEL("Temple/Floor2"));
	MODEL->Load(FILE_MODEL("Temple/Floor3"));
	MODEL->Load(FILE_MODEL("Temple/Pillar"));

	MODEL->Load(FILE_MODEL("Tornado/Tornado"));

	MODEL->Load(FILE_MODEL("Enemy/Mappie"));
	MODEL->Load(FILE_MODEL("Enemy/Gotudan"));
	MODEL->Load(FILE_MODEL("Enemy/Ship"));

	MODEL->Load(FILE_MODEL("Gimmick/Tree"));
	MODEL->Load(FILE_MODEL("Gimmick/Rock"));
}

//==================================================
//	カウント描画
//==================================================
void Count()
{
	static int i;
	while (i < 99)
	{
		// カウント
		++i;

		// UV計算
		int Rank = 0;
		int Num = i;
		while (Num > 0)
		{
			int a = Num % 10;
			m_Number[Rank].m_fTexCoordX = a % 5;
			m_Number[Rank].m_fTexCoordY = a / 5;
			++Rank;
			Num /= 10;
		}

		// 描画
		//m_Number[0].Update();
		//m_Number[1].Update();
		//BeginDrawDX();
		//m_Number[0].Draw();
		//m_Number[1].Draw();
		//EndDrawDX();
	}
}
