//--- インクルード
#include "GameScene.h"
#include "Camera.h"
#include "Collision.h"
#include "UI2D.h"
#include "Vitality.h"
#include "Keyboard.h"
#include "ModelManager.h"
#include "Fly.h"
#include "SelectScene.h"
#include "State/GameState.h"
#include "State/StartState.h"
#include "State/GameOverState.h"
#include "State/EnemyPlayer.h"
#include "Shader.h"

//--- 静的メンバ変数
ObjectList* GameScene::m_pObjList;
GAMESCENE::STEP GameScene::m_Step;

GameScene::GameScene()
{
	//MODEL->Init();
}
GameScene::~GameScene()
{
	//MODEL->Uninit();
}

//==================================================
// 初期化
//==================================================
void GameScene::Init()
{
	nWaitResult = 0;

	// スコア
	Score::GetInstance()->Init();

	// ステップ
	m_Step = GAMESCENE::START;

	// 当たり判定管理クラス
	Collision::GetInstance()->Init();

	//--- ゲームオブジェクト
	m_pObjList = new ObjectList;
	// 背景
	m_pObjList->Create(OBJECT::BACK);
	// フィールド
	m_pObjList->Create(OBJECT::FIELD);
	// エネミー
	m_EnemyManager.Init();
	// 母船
	m_pObjList->Create(OBJECT::BOSS);
	//--- プレイヤー
	// 生成後、カメラのターゲットに設定
	Object* pPlayer = m_pObjList->Create(OBJECT::PLAYER);
	Camera::GetInstance()->SetObject(pPlayer);
	// 木
	for (int i = 0; i < 50; i++)
		m_pObjList->Create(OBJECT::TREE);
	for (int i = 0; i < 200; i++)
		m_pObjList->Create(OBJECT::BTREE);
	//--- 神殿
	// 本体
	m_pObjList->Create(OBJECT::TEMPLE);
	// 柱
	for (int i = 0; i < 4; ++i)
		m_pObjList->Create(OBJECT::PILLAR)->Get<Transform>()->Position
		= { 30 * (i % 2 * 2.0f - 1), 30, 25 * (i / 2 * 2.0f - 1) };
	// 床
	m_pObjList->Create(OBJECT::FLOOR1);
	m_pObjList->Create(OBJECT::FLOOR2);
	m_pObjList->Create(OBJECT::FLOOR3);
	// コア
	m_pObjList->Create(OBJECT::CORE);
	// UI
	m_UI.Init();
	// タイマー
	Timer::GetInstance()->SetTime(120 * 60);
	//エネミーのキューを初期化
	EnemyPlayer::QueueClear();
	//吸い込んだ数の合計を初期化
	EnemyPlayer::m_TotalSucksNum = 0;
	//吸い込める容量の初期化
	EnemyPlayer::m_fCapa = 0;

	switch (SelectScene::m_nSelect)
	{
	case 0:
		m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/Stage1.mp3", true);
		break;
	case 1:
		m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/Stage2.mp3", true);
		break;
	case 2:
		m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/Boss.mp3", true);
		break;
	}
}

//==================================================
// 終了
//==================================================
void GameScene::Uninit()
{
	XAUDIO2_VOICE_STATE state;
	if (m_Sound.m_pSpeaker)
	{
		//ソースボイスの状況を取得
		m_Sound.m_pSpeaker->GetState(&state);
		//なってる音が一つ以上ならストップ
		if (state.BuffersQueued > 0)
		{
			m_Sound.m_pSpeaker->Stop();
		}
	}

	Camera::GetInstance()->SetObject(nullptr);

	m_UI.Uninit();

	m_EnemyManager.Uninit();

	Collision::GetInstance()->Uninit();

	delete m_pObjList;
}

//==================================================
// 更新
//--------------------------------------------------
// 戻り値	: 次のシーン
//==================================================
SCENE::TYPE GameScene::Update()
{
	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	// リザルト待機時間
	if (nWaitResult > 0)
	{
		--nWaitResult;

		m_pObjList->Get(OBJECT::BOSS)->Get<Fly>()->Update();

		if (nWaitResult == 0) return SCENE::RESULT;

		return SCENE::NO;
	}

	// UIの更新
	switch (m_UI.Update())
	{
	// ポーズ画面のとき以下を実行しない
	case UISYS::PAUSE: return SCENE::NO;
	// 再スタート
	case UISYS::RETRY: return SCENE::GAME;
	// 戻る
	case UISYS::EXIT: return SCENE::SELECT;
	default:
		break;
	}

	Score::GetInstance()->Update();

	// タイマーの取得
	int nTime = Timer::GetInstance()->GetTime();

	// ゲームクリア
	if (m_pObjList->Get(OBJECT::BOSS)->Get<Vitality>()->m_fHp <= 0)
	{
		m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
		m_Step = GAMESCENE::CLEAR;
		nWaitResult = 100;
	}
	// ゲームオーバー
	if ((m_pObjList->Get(OBJECT::TEMPLE)->Get<Vitality>()->m_fHp <= 0)
		|| (nTime < 1))
	{
		m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
		m_Step = GAMESCENE::GOVER;
		nWaitResult = 100;
	}
	// ゲーム開始
	if (m_Step == GAMESCENE::START && CAMERA->m_State == GameState::GetInstance())
	{
		//サウンド
		m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
		m_Sound.m_pSpeaker->SetVolume(0.0f);
		m_Sound.m_bFade = false;
		m_Sound.m_bFade = m_Sound.Fade(0.5f, 1.f);
		m_Step = GAMESCENE::MAIN;
	}
	else if (m_Step != GAMESCENE::MAIN)
	{
		return SCENE::NO;
	}

	m_pObjList->Update();
	MODEL->Update();


	// 本編でなければ以下を行わない
	if (m_Step != GAMESCENE::MAIN) return SCENE::NO;

	// 敵の生成
	switch (SelectScene::m_nSelect)
	{
	case 0:
		if (nTime % 45 == 0) m_EnemyManager.Create();
		break;
	case 1:
		if (nTime % 45 == 0) m_EnemyManager.Create();
		break;
	case 2:
		if (nTime % 15 == 0) m_EnemyManager.Create();
		break;
	}

	// 当たり判定
	Collision::GetInstance()->Update();

	return SCENE::NO;
}

//==================================================
// 描画
//==================================================
void GameScene::Draw()
{
	m_pObjList->Draw();
	//MODEL->Draw();
	if (CAMERA->m_State == GameState::GetInstance())
	Score::GetInstance()->Draw();
	m_UI.Draw();
}
