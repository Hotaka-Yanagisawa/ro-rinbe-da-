//--- インクルード
#include "ResultScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "Defines.h"
#include "Keyboard.h"
#include "Vitality.h"
#include "State//EnemyPlayer.h"
#include <string>
#include "Controller.h"

//==================================================
// 初期化
//==================================================
void ResultScene::Init()
{
	m_Step = RESULT_STEP_BEGIN;
	m_nWait = 5;
	m_nAdd = 0;

	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/Result.mp3", true);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(1.5f, 1.5f);

	
	m_SE2.m_pBuffer = m_SE2.CreateSound("Assets/Sound/SE/Point.mp3", false);
	m_SE2.m_pSpeaker = m_SE2.PlaySound(m_SE2.m_pBuffer);
	m_SE2.m_pSpeaker->SetVolume(0.0f);
	m_SE2.m_bFade = false;
	m_SE2.m_bFade = m_SE2.Fade(0.0f, 0.1f);
	m_SE2.Update();

	// ゲームの結果を保存
	m_nScore = 0;
	m_nType = GameScene::m_Step;
	m_nTotalScore = Score::GetInstance()->m_TotalScore;
	m_nTime = Timer::GetInstance()->GetTime() / 60;
	m_nMaxCombo = Score::GetInstance()->m_MaxCombo;
	m_nHp = UI2D::m_nResultHP;
	m_nEnemyNum = EnemyPlayer::m_TotalSucksNum;

	// 背景
	Pol2D* tmp = m_PolList.Add(new Pol2D, "Back");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("ResultBack"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { SCREEN_WIDTH * 2, SCREEN_HEIGHT, 0 };
	tmp->m_Transform.Position.x = -SCREEN_WIDTH / 2;

	// 下のやつ
	tmp = m_PolList.Add(new Pol2D, "Frame");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("ResultFrame"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { 1408, 352, 0 };
	tmp->m_Transform.Position.y = -260;

	// 枠
	tmp = m_PolList.Add(new Pol2D, "Window");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("ResultWindow"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = -50;
	tmp->m_Transform.Position.y = -70;
	tmp->m_Transform.Size = 1100;

	// 数字
	for (int i = 0; i < 6; ++i)
	{
		tmp = m_PolList.Add(new Pol2D, "Number" + std::to_string(i));
		tmp->Init();
		tmp->SetTexture(TEX_PNG("Number2"));
		tmp->m_bParallel = true;
		tmp->m_Transform.Size.x = 80;
		tmp->m_Transform.Size.y = 90;
		tmp->m_Transform.Position = { -130 + i * 80.0f, 195, 0 };
		tmp->m_fSplitX = 5; tmp->m_fSplitY = 2;
	}

	// ボタン
	tmp = m_PolList.Add(new Pol2D, "Button");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("Button"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = SCREEN_WIDTH / 2 - 100;
	tmp->m_Transform.Position.y = -SCREEN_HEIGHT / 2 + 100;
	tmp->m_Transform.Size = { 320, 180, 0 };
	tmp->m_r = tmp->m_g = tmp->m_b = 0.7f;

	// 濃いとこ
	tmp = m_Result.Add(new Pol2D, "Range");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("SandWatch"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.y = 100;
	tmp->m_Transform.Size = 3000;
	// 敵アイコン
	tmp = m_Result.Add(new Pol2D, "Enemy");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("IconEnemy"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = -220;
	tmp->m_Transform.Position.y = -10;
	tmp->m_Transform.Size = 100;
	// 時間アイコン
	tmp = m_Result.Add(new Pol2D, "Time");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("IconTime"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = -220;
	tmp->m_Transform.Position.y = -140;
	tmp->m_Transform.Size = 100;
	// 体力アイコン
	tmp = m_Result.Add(new Pol2D, "Life");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("IconCore"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = -220;
	tmp->m_Transform.Position.y = -270;
	tmp->m_Transform.Size.x = 100;
	tmp->m_Transform.Size.y = 170;
	// ボスアイコン
	tmp = m_Result.Add(new Pol2D, "Boss");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("UFO"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = -220;
	tmp->m_Transform.Position.y = -420;
	tmp->m_Transform.Size.x = 180;
	tmp->m_Transform.Size.y = 150;
	// ミッション
	tmp = m_Result.Add(new Pol2D, "Mission");
	tmp->Init();
	tmp->SetTexture(TEX_PNG("Mission"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Position.x = -220;
	tmp->m_Transform.Position.y = -560;
	tmp->m_Transform.Size.x = 250;
	tmp->m_Transform.Size.y = 90;
	tmp->m_fSplitY = 3;
	tmp->m_fTexCoordY = SelectScene::m_nSelect - 1;

	// 各スコア数字
	for (int i = 0; i < RESULT_STEP_MAX; ++i)
	{
		m_Number[i].Init(6);
		m_Number[i].SetSize(50);
		m_Number[i].SetDist(50);
		m_Number[i].SetPos(-230, i * -130 - 20);
		m_Number[i].DrawZero(false);
	}
	m_Number[RESULT_STEP_MAX - 1].SetPos(-230, 4 * -130 - 40);
}

//==================================================
// 終了
//==================================================
void ResultScene::Uninit()
{
	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	m_Sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上ならストップ
	if (state.BuffersQueued > 0)
	{
		m_Sound.m_pSpeaker->Stop();
	}

	m_PolList.Uninit();
	m_Result.Uninit();
	for (int i = 0; i < RESULT_STEP_MAX; ++i)
		m_Number[i].Uninit();
}

//==================================================
// 更新
//==================================================
SCENE::TYPE ResultScene::Update()
{
	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	m_SE.Update();
	m_SE2.Update();
	// 背景スクロール
	if ((m_PolList.Get("Back")->m_Transform.Position.x += 0.5f) > SCREEN_WIDTH / 2)
		m_PolList.Get("Back")->m_Transform.Position.x = -SCREEN_WIDTH / 2;

	// 数字更新
	for (int i = 0; i < 6; ++i)
	{
		Pol2D* tmp = m_PolList.Get("Number" + std::to_string(i));
		// 桁抽出
		int nNum = m_nScore;
		for (int j = 0; j < (6 - i) - 1; ++j) nNum /= 10; nNum %= 10;
		// UV設定
		tmp->m_fTexCoordX = float(nNum % (int)tmp->m_fSplitX);
		tmp->m_fTexCoordY = (float)int(nNum / tmp->m_fSplitX);
	}
	for (int i = 0; i < RESULT_STEP_MAX; ++i)
		m_Number[i].Update();
	m_PolList.Update();
	m_Result.Update();

	// スコア順番に表示
	if (m_Step < RESULT_STEP_MAX)
	{
		// 早送り
		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))
		{
			m_nWait = 1;
		}
		// 待ち
		if (--m_nWait > 0)
		{
			// スクロール
			if ((m_nWait < 25) && (m_Step < ADD_SCORE_CLEAR))
			{
				m_Result.SetMove(Float3(0, 5.0f, 0));
				for (int i = 0; i < 5; ++i) m_Number[i].SetMove(0, 5.0f);
			}
			return SCENE::NO;
		}
		else
		{
			//m_SE2.m_pBuffer = m_SE2.CreateSound("Assets/Sound/SE/Point.mp3", false);
			m_SE2.m_pSpeaker = m_SE2.PlaySound(m_SE2.m_pBuffer);
			m_SE2.m_pSpeaker->SetVolume(0.0f);
			m_SE2.m_bFade = false;
			m_SE2.m_bFade = m_SE2.Fade(1.0f, 0.1f);
			m_SE2.Update();
			m_nScore += m_nAdd;
			m_Step = RESULT_STEP((int)m_Step + 1);
		}
		switch (m_Step)
		{
		case ADD_SCORE_ENEMY:
			m_nAdd = m_nEnemyNum * 1200;
			break;
		case ADD_SCORE_TIME:
			m_nAdd = m_nTime * 2500;
			break;
		case ADD_SCORE_LIFE:
			m_nAdd = m_nHp * 5000;
			break;
		case ADD_SCORE_CLEAR:
			m_nAdd = (m_nType == GAMESCENE::CLEAR) ? 100000 : 0;
			break;
		case ADD_SCORE_MISSION:
			switch (SelectScene::m_nSelect)
			{
			case 0: m_nAdd = (m_nMaxCombo > 50) ? 50000 : 0; break;
			case 1: m_nAdd = (m_nTime >= 30) ? 50000 : 0; break;
			case 2: m_nAdd = (m_nHp >= 15) ? 50000 : 0; break;
			default: break;
			}
			break;
		default:
			break;
		}
		m_Number[m_Step].SetNumStep(m_nAdd, 10);
		if(m_Step != ADD_SCORE_MISSION) m_nWait = 100;
		return SCENE::NO;
	}

	//--- 演出終わり後
	// セレクト画面へ
	if (IsKeyTrigger(VK_RETURN) ||  PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))
	{
		m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
		// ランキング反映
		int Stage = SelectScene::m_nSelect;
		SelectScene::m_Ranking.SetScore(m_nScore, Stage);
		SelectScene::m_Ranking.Save(SCORE_FILE);

		m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Decision.mp3", false);
		m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
		m_SE.m_pSpeaker->SetVolume(0.0f);
		m_SE.m_bFade = false;
		m_SE.m_bFade = m_SE.Fade(1.0f, 0.1f);
		m_SE.Update();

		return SCENE::SELECT;
	}

	// スクロール
	if ((IsKeyPress(VK_UP) || PAD->IsButtonsPress(XINPUT_GAMEPAD_DPAD_UP))
		&& (m_Result.Get("Enemy")->m_Transform.Position.y > -10.0f))
	{
		m_Result.SetMove(Float3(0, -10, 0));
		for (int i = 0; i < RESULT_STEP_MAX; ++i) m_Number[i].SetMove(0, -10);
	}
	if ((IsKeyPress(VK_DOWN) || PAD->IsButtonsPress(XINPUT_GAMEPAD_DPAD_DOWN))
		&& (m_Result.Get("Enemy")->m_Transform.Position.y < 410.0f))
	{
		m_Result.SetMove(Float3(0, 10, 0));
		for (int i = 0; i < RESULT_STEP_MAX; ++i) m_Number[i].SetMove(0, 10);
	}

	// ちかちか
	static float a;
	a += 5 * 3.1415f / 180.0f;
	m_PolList.Get("Button")->m_a = (sinf(a) < 0.4f) ? 1.0f : sinf(a);

	return SCENE::NO;
}

//==================================================
// 描画
//==================================================
void ResultScene::Draw()
{
	m_PolList.Draw();

	GET_DX->SetRasterizer(RASTERIZE::SCISSOR);
	m_Result.Draw();
	for (int i = 0; i < RESULT_STEP_MAX; ++i)
		m_Number[i].Draw();

	GET_DX->SetRasterizer(RASTERIZE::NORMAL);
}
