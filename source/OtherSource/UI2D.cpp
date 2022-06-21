//--- インクルード
#include "UI2D.h"
#include "Shader.h"
#include "Camera.h"
#include "Defines.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Vitality.h"
#include "Keyboard.h"
#include "State/StartState.h"
#include "State/GameState.h"
#include "State/EnemyPlayer.h"

int g_nInterval;

//--- 静的メンバ変数
int UI2D::m_nResultHP;
bool UI2D::m_bTmplHPFrag;

//==================================================
// 初期化
//==================================================
void UI2D::Init()
{
	// スタート
	m_Start.Init();
	m_Start.m_bParallel = true;
	m_Start.SetTexture(TEX_PNG("Start"));
	m_Start.m_Transform.Position = { 0, 0, 0 };
	m_Start.m_Transform.Size = { 400, 400, 0 };
	// クリア
	m_Clear.Init();
	m_Clear.m_bParallel = true;
	m_Clear.SetTexture(TEX_PNG("Clear"));
	m_Clear.m_Transform.Position = { 0, -200, 0 };
	m_Clear.m_Transform.Size = { 500, 500, 0 };
	// ゲームオーバー
	m_GOver.Init();
	m_GOver.m_bParallel = true;
	m_GOver.SetTexture(TEX_PNG("GOver"));
	m_GOver.m_Transform.Position = { 0, 0, 0 };
	m_GOver.m_Transform.Size = { 700, 550, 0 };

	// カウントダウン
	m_Number.Init();
	m_Number.m_bParallel = true;
	m_Number.SetTexture(TEX_PNG("Count"));
	m_Number.m_Transform.Position = { 0, 0, 0 };
	m_Number.m_Transform.Size = { 500, 520, 0 };
	m_Number.m_fSplitX = 3;
	m_Number.m_fSplitY = 1;
	m_Number.m_fTexCoordX = 3;
	m_Number.m_fTexCoordY = 0;

	m_Number.m_r = m_Number.m_g = m_Number.m_b = m_Number.m_a = 1;
	m_nCount = 179;
	m_nSECnt = -1;

	// タイマー
	Timer::GetInstance()->Init();

	// 体力バー
	m_nBasePos = 0; 
	m_nBaseSize = 0;
	// ボス
	m_BossHP.Init();
	m_BossHP.m_bParallel = true;
	m_BossHP.SetTexture(TEX_PNG("BossBar"));
	m_BossHP.m_Transform.Position = { 0, SCREEN_HEIGHT / 2 - 83, 0 };
	m_BossHP.m_Transform.Size = { 250, 20, 0 };
	m_BossGa.Init();
	m_BossGa.m_bParallel = true;
	m_BossGa.SetTexture(TEX_PNG("BossGage"));
	m_BossGa.m_Transform.Position = { 2, SCREEN_HEIGHT / 2 - 60, 0 };
	m_BossGa.m_Transform.Size = { 380, 160, 0 };
	// 神殿
	m_TmplHP.Init();
	m_TmplHP.m_bParallel = true;
	m_TmplHP.SetTexture(NULL);
	m_TmplHP.m_Transform.Position = { -SCREEN_WIDTH / 2 + 130, SCREEN_HEIGHT / 2 - 30, 0 };
	m_TmplHP.m_Transform.Size = { 180, 40, 0 };
	m_TmplGa.Init();
	m_TmplGa.m_bParallel = true;
	m_TmplGa.SetTexture(TEX_PNG("TmplGage"));
	m_TmplGa.m_Transform.Position = { -SCREEN_WIDTH / 2 + 130, SCREEN_HEIGHT / 2 - 30, 0 };
	m_TmplGa.m_Transform.Size = { 250, 60, 0 };

	// 容量ゲージ
	m_Gage.Init();
	Pol2D* pPol = m_Gage.Add(new Pol2D, "GageFrame");
	pPol->Init();
	pPol->SetTexture(TEX_PNG("Gage/Frame"));
	pPol->m_bParallel = true;
	pPol->m_Transform.Position = { -565, -5, 0 };
	pPol->m_Transform.Size = { 200, 420, 0 };
	for (int i = 0; i < 12; ++i)
	{
		m_fileName[i] = "Gage" + std::to_string(i);
		std::string file = "Assets/Texture/Gage/Gage" + std::to_string(i + 1) + ".png";
		pPol = m_Gage.Add(new Pol2D, m_fileName[i]);
		pPol->Init();
		pPol->SetTexture(file.c_str());
		pPol->m_bParallel = true;
		pPol->m_Transform.Position = { -SCREEN_WIDTH / 2 + 73, -150 + i * 20.0f, 0 };
		pPol->m_Transform.Size = { 80, 40, 0 };
	}

	// ポーズ画面フラグ
	m_bPause = false;
	m_bCntDown = true;

	m_nResultHP = 0;
	m_bTmplHPFrag = false;
}

//==================================================
// 終了
//==================================================
void UI2D::Uninit()
{
	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	m_Sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上ならストップ
	if (state.BuffersQueued > 0)
	{
		m_Sound.m_pSpeaker->Stop();
	}
	m_Start.Uninit();
	m_Clear.Uninit();
	m_GOver.Uninit();

	Timer::GetInstance()->Uninit();
	m_Number.Uninit();

	m_BossHP.Uninit();
	m_TmplHP.Uninit();

	m_Gage.Uninit();
}

//==================================================
// 更新
//==================================================
UISYS::STATUS UI2D::Update()
{
	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	if (CAMERA->m_State == GameState::GetInstance())
	{
		// ポーズ画面切り替え
		if (IsKeyTrigger('O'))
		{
			if (m_bPause ^= 1) SceneManager::GetInstance()->m_Fade.SetFade(0.1f);
			else SceneManager::GetInstance()->m_Fade.SetFade(0);
		}
		// ポーズ画面の処理
		if (m_bPause)
		{
			// 戻る
			if (IsKeyTrigger(VK_BACK)) return UISYS::EXIT;
			// リスタート
			if (IsKeyTrigger('P')) return UISYS::RETRY;

			return UISYS::PAUSE;
		}


		// タイマー
		Timer::GetInstance()->Update();
		//ボスHP
		float max = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Vitality>()->m_fMaxHp;
		float now = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Vitality>()->m_fHp;
		m_BossHP.m_Transform.Size.x = now / max * 250;
		m_nBasePos = 0; m_nBaseSize = 250;
		m_BossHP.m_Transform.Position.x = (m_BossHP.m_Transform.Size.x - m_nBaseSize) / 2 - m_nBasePos;
		//神殿HP
		if (m_bTmplHPFrag)
		{
			static unsigned int Cnt;
			++Cnt;
			if (Cnt % 10 < 5)
			{
				m_TmplGa.m_r = 1;
				m_TmplGa.m_g = 0;
				m_TmplGa.m_b = 1;
				m_TmplGa.m_a = 0.3f;
			}
			else
			{
				m_TmplGa.m_r = 1;
				m_TmplGa.m_g = 1;
				m_TmplGa.m_b = 1;
				m_TmplGa.m_a = 1;
			}
		}
		else
		{
			m_TmplGa.m_r = 1;
			m_TmplGa.m_g = 1;
			m_TmplGa.m_b = 1;
			m_TmplGa.m_a = 1;
		}
		m_bTmplHPFrag = false;
		max = GameScene::GetObjectList()->Get(OBJECT::TEMPLE)->Get<Vitality>()->m_fMaxHp;
		now = GameScene::GetObjectList()->Get(OBJECT::TEMPLE)->Get<Vitality>()->m_fHp;
		m_nResultHP = now;

		if ((max * 0.5f) > now)
		{
			m_TmplHP.m_r = 1.0f;
			m_TmplHP.m_g = 0.8f;
			m_TmplHP.m_b = 0.1f;
		}
		else
		{
			m_TmplHP.m_r = 0.0f;
			m_TmplHP.m_g = 1.0f;
			m_TmplHP.m_b = 0.3f;
		}
		m_TmplHP.m_Transform.Size.x = now / max * 180;
		m_nBasePos = SCREEN_WIDTH / 2 - 130; m_nBaseSize = 180;
		m_TmplHP.m_Transform.Position.x = (m_TmplHP.m_Transform.Size.x - m_nBaseSize) / 2 - m_nBasePos;

		Pol2D* pPol = m_Gage.Get("GageFrame");
		//if (EnemyPlayer::m_nLoadingNum < 2)
		//{
		//	pPol->m_r = 1.0f;
		//	pPol->m_g = 1.0f;
		//	pPol->m_b = 1.0f;
		//}
		//else if (EnemyPlayer::m_nLoadingNum < 4)
		//{
		//	pPol->m_r = 0.0f;
		//	pPol->m_g = 0.0f;
		//	pPol->m_b = 1.0f;
		//}
		//else if (EnemyPlayer::m_nLoadingNum < 7) 
		//{
		//	pPol->m_r = 0.5f;
		//	pPol->m_g = 1.0f;
		//	pPol->m_b = 0.0f;
		//}
		//else if (EnemyPlayer::m_nLoadingNum < 10) 
		//{
		//	pPol->m_r = 1.0f;
		//	pPol->m_g = 1.0f;
		//	pPol->m_b = 0.0f;
		//}
		//else if (EnemyPlayer::m_nLoadingNum == 10)
		//{
		//	pPol->m_r = 1.0f;
		//	pPol->m_g = 0.0f;
		//	pPol->m_b = 0.0f;
		//}
		m_BossHP.Update();
		m_TmplHP.Update();
		m_TmplGa.Update();
		for (int i = 0; i < 12; i++)
		{
			m_Gage.Get(m_fileName[i])->m_a = 0;
		}
		for (int i = 0; i < (int)EnemyPlayer::m_fCapa / 10; i++)
		{
			pPol = m_Gage.Get(m_fileName[i]);
			pPol->m_a = 1;
		}
		m_Gage.Update();
		return UISYS::NO;
	}
	else
	{
		if (StartState::GetInstance()->m_Phase == StartState::END)
		{
			if (m_nSECnt == -1) m_nSECnt = 20;
			if (m_nSECnt > 0)
			{
				--m_nSECnt;
				if (m_nSECnt == 0)
				{
					m_nSECnt = -2;
					m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/Start.mp3", false);
					m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
					m_Sound.m_pSpeaker->SetVolume(0.0f);
					m_Sound.m_bFade = false;
					m_Sound.m_bFade = m_Sound.Fade(0.5f, 0.1f);
				}
			}
		}
		if (StartState::GetInstance()->m_Phase == StartState::CNT_DOWN)
		{
			if (m_bCntDown)
			{
				m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/SE/Countdown03-6.mp3", false);
				m_Sound.m_pBuffer->LoopCount = 2;
				m_Sound.m_pBuffer->PlayBegin = 128 * 180;
				m_Sound.m_pBuffer->LoopBegin = 128 * 180;
				//m_Sound.m_pBuffer->LoopLength = 128*2;
				m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
				m_Sound.m_pSpeaker->SetVolume(0.0f);
				m_Sound.m_bFade = false;
				m_Sound.m_bFade = m_Sound.Fade(1.0f, 0.1f);
				m_bCntDown = false;
			}
			int Num = m_nCount / 60 + 1;
			while (Num > 0)
			{
				m_Number.m_fTexCoordX = Num - 1;
				m_Number.m_fTexCoordY = 0;

				Num /= 10;
			}

			m_Number.Update();

			// カウント
			if (m_nCount > 0) --m_nCount;
		}
		return UISYS::NO;

	}
}

//==================================================
// 描画
//==================================================
void UI2D::Draw()
{
	if (CAMERA->m_State == GameState::GetInstance())
	{
		m_BossGa.Draw();
		m_BossHP.Draw();
		m_TmplGa.Draw();
		m_TmplHP.Draw();

		Timer::GetInstance()->Draw();

		m_Gage.Draw();
	}
	if (StartState::GetInstance()->m_Phase == StartState::CNT_DOWN)
	{
		if (g_nInterval < 5) g_nInterval++;
		else
			m_Number.Draw();
	}
	else
	{
		g_nInterval = 0;
	}
	switch (GameScene::m_Step)
	{
	case GAMESCENE::START:
		if (StartState::GetInstance()->m_Phase == StartState::END)
		m_Start.Draw();
		break;
	case GAMESCENE::CLEAR:
		m_Clear.Draw();
		break;
	case GAMESCENE::GOVER:
		m_GOver.Draw();
		break;
	}

	// ポーズ画面の描画
	if (m_bPause)
	{
		

	}

}
