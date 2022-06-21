//--- インクルード
#include "SelectScene.h"
#include "Defines.h"
#include "Controller.h"
#include "Keyboard.h"

#define STR_TEX_PNG(STR) ("Assets/Texture/" + STR + ".png").c_str()
#define STR_TEX_JPG(STR) ("Assets/Texture/" + STR + ".jpg").c_str()
#define SET_Y	(-4)
#define CURSOR_POS_Y (-50)

//--- 静的メンバ変数
int SelectScene::m_nSelect;
Ranking SelectScene::m_Ranking;

//==================================================
// 初期化
//==================================================
void SelectScene::Init()
{
	m_Step = SELECTSCENE::SELECT;

	m_nTexNum = 0;
	m_radius = 30.0f;

	std::string str; //

	// ステージの画像をセット
	const char *pTexture[] =
	{
		TEX_PNG("scr1"),	// st1
		TEX_PNG("scr2"),	// st2
		TEX_PNG("scr3"),	// st3
	};

	// 画像の枚数分メモリを確保
	m_nTexNum = _countof(pTexture);
	m_pSelectSceneImage = new Pol2D[m_nTexNum];
	m_fpPersonalAngle = new float[m_nTexNum];
	m_fpLatePersonalAngle = new float[m_nTexNum];

	// 各ステージのイメージテクスチャを初期化
	for (int i = 0; i < m_nTexNum; i++)
	{
		const float RAD(3.141592f / 180.0f);

		m_pSelectSceneImage[i].Init();
		m_pSelectSceneImage[i].m_bBillboard = true;
		m_pSelectSceneImage[i].SetTexture(pTexture[i]);

		float deg = ((180.0f / m_nTexNum * 2) * i);

		if (i == 1) m_fDistanceAngle = deg * RAD;	// イメージ同士の間のラジアン角を一旦保存

		deg = (RAD * deg) + (-90 * RAD);			// -90ずらして正面に来るように
		m_fpPersonalAngle[i] = deg;
		m_fpLatePersonalAngle[i] = deg;

		m_pSelectSceneImage[i].m_Transform.Position =
		{
			cosf(m_fpPersonalAngle[i]) * m_radius,		// x
			SET_Y,										// y
			sinf(m_fpPersonalAngle[i]) * m_radius		// z
		};
		m_pSelectSceneImage[i].m_Transform.Position.z -= 30.0f;
		m_pSelectSceneImage[i].m_Transform.Size =
		{
			45,		// x
			30,		// y
			0		// z
		};

	};

	for (int i = 0; i < m_Cursor.size(); i++)
	{
		float posx(400);
		m_Cursor[i].Init();
		m_Cursor[i].m_bParallel = true;
		m_Cursor[i].SetTexture(TEX_PNG("Cursor"));
		m_Cursor[i].m_Transform.Position = { posx + posx * (i * -2), CURSOR_POS_Y,0 };
		m_Cursor[i].m_Transform.Size = { posx * 0.5f, posx * 0.5f, 0 };
		m_Cursor[i].m_fSplitX = 2;
		m_Cursor[i].m_fTexCoordX = 1 - i;
	}

	m_nTimer = 0;
	m_nReturnTime = -1;

	// 選んだステージ
	m_nSelect = 0;

	// ポリゴン追加
	m_SelectList.Add(m_PolList.Add(new Pol2D, "Back"));

	for (int i = 0; i < 4; i++)
		m_SelectList.Add(m_PolList.Add(new Pol2D, "Cloud" + std::to_string(i + 1)));

	m_SelectList.Add(m_PolList.Add(new Pol2D, "UFO"));
	m_SelectList.Add(m_PolList.Add(new Pol2D, "Start"));
	m_SelectList.Add(m_PolList.Add(new Pol2D, "Cancel"));


	for (int i = 0; i < m_nTexNum; i++) // ステージ数の数分用意
	{
		// 各ステージの名前のやつをAdd
		str = "Stage" + std::to_string(i + 1);
		m_Plate.Add(new Pol2D, str);

		// スタンバイ画面の画像をAdd
		m_PolList.Add(new Pol2D, str);

		for (int j = 0; j < 1 + i; j++)		// 各ステージにレベル表記の☆を指定数用意
		{
			str = "Level" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
			m_Star.Add(new Pol2D, str);
		}
	}

	m_PolList.Add(new Pol2D, "Ranking");
	m_PolList.Add(new Pol2D, "Mission");

	m_Plate.Init();

	m_Star.Init();

	m_PolList.Init();

	m_SelectList.Init();

	// 背景
	Pol2D* tmp = m_PolList.Get("Back");
	tmp->SetTexture(TEX_PNG("BlueSky"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { SCREEN_WIDTH, SCREEN_HEIGHT, 0 };
	// 雲
	for (int i = 0; i < 4; i++)
	{
		str = "Cloud" + std::to_string(i + 1);
		tmp = m_PolList.Get(str);
		tmp->SetTexture(STR_TEX_PNG(str));
		tmp->m_bParallel = true;
		tmp->m_Transform.Size = { 400, 130, 0 };
		tmp->m_Transform.Position.x = -500.0f + (rand() % 100 + 400 * i + 1);
		m_PolList.Get(str)->m_Transform.Position.y =
			-SCREEN_HEIGHT * 0.2f + (rand() % int(SCREEN_HEIGHT * 0.6f));
	}
	// UFO
	tmp = m_PolList.Get("UFO");
	tmp->SetTexture(TEX_PNG("UFO"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { 230,160,0 };
	tmp->m_Transform.Position = { -1000, 250,0 };
	// ランキング
	tmp = m_PolList.Get("Ranking");
	tmp->SetTexture(TEX_PNG("Ranking"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { 800, 650, 0 };
	tmp->m_Transform.Position = { 420, 10, 0 };
	// ミッション
	tmp = m_PolList.Get("Mission");
	tmp->SetTexture(TEX_PNG("Mission"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { 300, 100, 0 };
	tmp->m_Transform.Position = { 410, 150, 0 };
	tmp->m_fSplitY = 3;
	// 進む
	tmp = m_PolList.Get("Start");
	tmp->SetTexture(TEX_PNG("Susumu"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { 480, 270, 0 };
	tmp->m_Transform.Position = { -50, -290, 0 };
	// 戻る
	tmp = m_PolList.Get("Cancel");
	tmp->SetTexture(TEX_PNG("Modoru"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size = { 320, 180, 0 };
	tmp->m_Transform.Position = { -470, -310, 0 };

	for (int i = 0; i < m_nTexNum; i++) // ステージ数の数分用意
	{
		for (int j = 0; j < 1 + i; j++)		// 各ステージにレベル表記の☆を指定数用意
		{
			str = "Level" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
			tmp = m_Star.Get(str);
			tmp->SetTexture(TEX_PNG("Star"));
			tmp->m_bBillboard = true;
			tmp->m_Transform.Size = 450 + (i + j == 3 ? 20 : 0);
			tmp->m_Transform.Size *= 0.015f;
			tmp->m_Transform.Position =
			{
				((cosf(m_fpPersonalAngle[i]) * m_radius)) + (tmp->m_Transform.Size.x * j),
				SET_Y,
				sinf(m_fpPersonalAngle[i]) * m_radius + -30
			};

			//tmp->m_Transform.Position = 9999;
		}

		// 各ステージの名前のやつをGet
		str = "Stage" + std::to_string(i + 1);
		tmp = m_Plate.Get(str);
		tmp->SetTexture(STR_TEX_PNG(str));
		tmp->m_bBillboard = true;
		tmp->m_Transform.Size = { 1395,390,1395 };
		tmp->m_Transform.Size *= 0.055f;
		tmp->m_Transform.Position =
		{
			cosf(m_fpPersonalAngle[i]) * m_radius + (-tmp->m_Transform.Size.x),
			SET_Y,
			sinf(m_fpPersonalAngle[i]) * m_radius + -30
		};

		// ステージ画像
		tmp = m_PolList.Get(str);
		tmp->SetTexture(pTexture[i]);
		tmp->m_bParallel = true;
		tmp->m_Transform.Size = { 600, 400, 0 };
		tmp->m_Transform.Position = { -220, 10, 0 };

	}

	// スコア読み込み
	m_Ranking.Load(SCORE_FILE);
	// ランキング数字
	for (int stage = 0; stage < STAGE_NUM; ++stage)		// ステージ数
		for (int rank = 0; rank < SAVE_NUM; ++rank)		// スコア数
			for (int num = 0; num < MAX_RANK; ++num)	// 桁数
			{
				Pol2D* tmp = m_ScorePol[stage].Add(new Pol2D);
				tmp->Init();
				tmp->SetTexture(TEX_PNG("Number2"));
				tmp->m_bParallel = true;
				tmp->m_Transform.Size.x = 35;
				tmp->m_Transform.Size.y = 50;
				tmp->m_Transform.Position = { 350 + num * 35.0f, -45 - rank * 60.0f, 0 };
				// 桁抽出
				int nNum = m_Ranking.m_Data[stage].Score[rank];
				for (int i = 0; i < MAX_RANK - num - 1; ++i) nNum /= 10; nNum %= 10;
				// UV設定
				tmp->m_fSplitX = 5; tmp->m_fSplitY = 2;
				tmp->m_fTexCoordX = float(nNum % (int)tmp->m_fSplitX);
				tmp->m_fTexCoordY = (float)int(nNum / tmp->m_fSplitX);
			}
	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/Title.mp3", true);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.5f, 5.f);

	m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Decision.mp3", false);
	m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
	m_SE.m_pSpeaker->SetVolume(0.0f);
	m_SE.m_bFade = false;
	m_SE.m_bFade = m_SE.Fade(0.0f, 0.1f);
}

//==================================================
// 終了
//==================================================
void SelectScene::Uninit()
{
	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	m_Sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上ならストップ
	if (state.BuffersQueued > 0)
	{
		m_Sound.m_pSpeaker->Stop();
	}
	m_SE.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上ならストップ
	if (state.BuffersQueued > 0)
	{
		m_SE.m_pSpeaker->Stop();
	}
	if (m_pSelectSceneImage != nullptr)
	{
		for (int i = 0; i < m_nTexNum; i++)
		{
			m_pSelectSceneImage[i].Uninit();
		}
		delete[] m_pSelectSceneImage;
		delete[] m_fpPersonalAngle;
	}

	// スコア保存
	m_Ranking.Save(SCORE_FILE);
	// ポリゴンの終了
	m_PolList.Uninit();
	// スターの終了
	m_PolList.Uninit();
	// ステージの名前終了
	m_Plate.Uninit();
	for (int i = 0; i < STAGE_NUM; ++i) m_ScorePol[i].Uninit();
}

//==================================================
// 更新
//==================================================
SCENE::TYPE SelectScene::Update()
{
	static float a;
	a += 0.1f; if (a == 90) a = 0;

	std::string str; // ループによるポリゴンGet用
	Pol2D* tmp;

	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	m_SE.Update();
	// 決定
	if (m_nTimer < 1) // タイマーが０を下回るまで入力を受け付けない
	{
		if (IsKeyPress(VK_RETURN) || PAD->IsButtonsPress(XINPUT_GAMEPAD_B))
			m_PolList.Get("Start")->m_g = 0.6f;
		else
		{
			m_PolList.Get("Start")->m_g = 1.0f;
			// ちかちか
			m_PolList.Get("Start")->m_a = (int(a * 10) % 80) / 10.0f;
		}
		if (IsKeyRelease(VK_RETURN) || PAD->IsButtonsRelease(XINPUT_GAMEPAD_B))
		{
			m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Decision.mp3", false);
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(2.0f, 0.1f);

			if (m_Step == SELECTSCENE::STANDBY)
			{
				m_nTimer = 30;
			}
			else m_nTimer = 20;
		}
	}
	// 戻る
	if (m_nReturnTime < 1)
	{
		if (IsKeyPress(VK_BACK) || PAD->IsButtonsPress(XINPUT_GAMEPAD_A)) m_PolList.Get("Cancel")->m_g = 0.6f;
		else m_PolList.Get("Cancel")->m_g = 1.0f;
		if (IsKeyRelease(VK_BACK) || PAD->IsButtonsRelease(XINPUT_GAMEPAD_A))
		{
			m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Cancel.mp3", false);
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(2.0f, 0.1f);
			if (m_Step == SELECTSCENE::SELECT)
			{
				m_nReturnTime = 30;
			}
			m_Step = SELECTSCENE::SELECT;
		}
	}

	switch (m_Step)
	{
	case SELECTSCENE::SELECT:
	{
		if (m_nReturnTime > 0)
		{
			--m_nReturnTime;

			if (m_nReturnTime == 0)
			{
				m_nReturnTime = -1;
				return SCENE::TITLE;
			}
			break;
		}
		if (m_nTimer > 0)
		{
			--m_nTimer;

			m_pSelectSceneImage[m_nSelect].m_Transform.Position.y += 2;

			if (m_nTimer == 0)
			{
				m_nTimer = -1;
				m_Step = SELECTSCENE::STANDBY;
			}

			break;
		}

		bool KeyRight = IsKeyTrigger(VK_RIGHT) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_DPAD_RIGHT);
		bool KeyLeft = IsKeyTrigger(VK_LEFT) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_DPAD_LEFT);
		const float RAD(3.141592f / 180.0f);
		float fLate = 0.1f;
		float Move;

		if (KeyRight)
		{
			m_nSelect++;
			if (m_nSelect > m_nTexNum - 1) m_nSelect = 0;
			if (m_Cursor[0].m_Transform.Position.y < 0) m_Cursor[0].m_Transform.Position.y += 20;
			m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/CursorMove.mp3", false);
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(1.5f, 0.1f);
		}

		if (KeyLeft)
		{
			m_nSelect--;
			if (m_nSelect < 0) m_nSelect = m_nTexNum - 1;
			if (m_Cursor[1].m_Transform.Position.y < 0) m_Cursor[1].m_Transform.Position.y += 20;
			m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/CursorMove.mp3", false);
			m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
			m_SE.m_pSpeaker->SetVolume(0.0f);
			m_SE.m_bFade = false;
			m_SE.m_bFade = m_SE.Fade(1.5f, 0.1f);
		}

		m_Cursor[0].m_Transform.Position.y = (m_Cursor[0].m_Transform.Position.y + -CURSOR_POS_Y) * 0.9 + CURSOR_POS_Y;
		m_Cursor[1].m_Transform.Position.y = (m_Cursor[1].m_Transform.Position.y + -CURSOR_POS_Y) * 0.9 + CURSOR_POS_Y;

		for (int i = 0; i < m_nTexNum; i++)
		{
			if (KeyRight)
			{
				m_fpPersonalAngle[i] += -m_fDistanceAngle;
			}
			if (KeyLeft)
			{
				m_fpPersonalAngle[i] += m_fDistanceAngle;
			}

			Move = m_fpPersonalAngle[i] - m_fpLatePersonalAngle[i];
			Move *= fLate;
			m_fpLatePersonalAngle[i] += Move;

			m_pSelectSceneImage[i].m_Transform.Position =
			{
				cosf(m_fpLatePersonalAngle[i]) * m_radius,	// x
				SET_Y,											// y
				sinf(m_fpLatePersonalAngle[i]) * m_radius	// z
			};
			m_pSelectSceneImage[i].m_Transform.Position.z -= 30.0f;

			for (int j = 0; j < 1 + i; j++)		// ステージレベル指標
			{
				str = "Level" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
				m_Star.Get(str)->m_Transform.Position =
				{
					(cosf(m_fpLatePersonalAngle[i]) * m_radius) +
					((m_Star.Get(str)->m_Transform.Size.x * 0.5f) * j + ((-m_Star.Get(str)->m_Transform.Size.x * 0.25f) * i)),
					SET_Y + 16.6f + (i + j == 3 ? 1 : 0),
					sinf(m_fpLatePersonalAngle[i]) * m_radius + -30 //32
				};
			}

			str = "Stage" + std::to_string(i + 1); // 各ステージの名前Plateの更新
			m_Plate.Get(str)->m_Transform.Position =
			{
				cosf(m_fpLatePersonalAngle[i]) * m_radius,
				//m_pSelectSceneImage[i].m_Transform.Size.y * 0.1f,
				12.0f + SET_Y,
				sinf(m_fpLatePersonalAngle[i]) * m_radius + -30 // 31
			};
		}

		m_Star.Update();
		m_Plate.Update();

		m_Cursor[0].Update();
		m_Cursor[1].Update();
		break;
	}
	case SELECTSCENE::STANDBY:
		m_nTimer--;
		if (m_nTimer == 10)
		{
			m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
			m_SE.m_bFade = m_SE.Fade(0.0f, 0.1f);
		}
		if (m_nTimer == 0)
		{
			return SCENE::GAME;
		}
		// ふわふわ (スタンバイ)
		for (int i = 0; i < m_nTexNum; i++)
		{
			str = "Stage" + std::to_string(i + 1);
			tmp = m_PolList.Get(str);
			tmp->m_Transform.Position = { -220, 10, 0 };
			i == m_nSelect ?
				tmp->m_Transform.Position.y = sinf(a) * 2 - 25 : 
				tmp->m_Transform.Position = 9999;
		}
		// スコア数字更新
		m_ScorePol[m_nSelect].Update();
		// ミッション
		m_PolList.Get("Mission")->m_fTexCoordY = m_nSelect;
		// ステージ名
		m_Plate.Get("Stage" + std::to_string(m_nSelect + 1))->m_Transform.Position = { -10.2 , 12, -30 + -m_radius };

		break;

	default:
		break;
	}

	// 雲
	tmp = m_PolList.Get(str);
	for (int i = 0; i < 4; i++)
	{
		str = "Cloud" + std::to_string(i + 1);
		tmp = m_PolList.Get(str);
		if ((tmp->m_Transform.Position.x -= 1.0f) < -SCREEN_WIDTH / 2 - 200)
		{
			tmp->m_Transform.Position.x = SCREEN_WIDTH / 2 + 200;
			tmp->m_Transform.Position.y =
				-SCREEN_HEIGHT * 0.2f + (rand() % int(SCREEN_HEIGHT * 0.6f));
		}
	}

	tmp = m_PolList.Get("UFO");
	tmp->m_Transform.Position.y += sin(a * 0.5f);
	if ((tmp->m_Transform.Position.x -= 2.0f) < -SCREEN_WIDTH / 2 - 200)
	{
		tmp->m_Transform.Position.x = SCREEN_WIDTH / 2 + 200;
		tmp->m_Transform.Position.y =
			-SCREEN_HEIGHT * 0.3f + (rand() % int(SCREEN_HEIGHT * 0.7f));
	}

	// ポリゴン更新
	m_PolList.Update();
	m_SelectList.Update();

	return SCENE::NO;
}

//==================================================
// 描画
//==================================================
void SelectScene::Draw()
{
	switch (m_Step)
	{
	case SELECTSCENE::SELECT:
		m_SelectList.Draw();

		for (int i = 0; i < m_nTexNum; i++)
			m_pSelectSceneImage[i].Draw();


		m_Plate.Draw();
		m_Star.Draw();
		m_Cursor[0].Draw();
		m_Cursor[1].Draw();
		break;

	case SELECTSCENE::STANDBY:
		m_PolList.Draw();
		m_ScorePol[m_nSelect].Draw();
		m_Plate.Get("Stage" + std::to_string(m_nSelect + 1))->Draw();
		// ポリゴン描画
		break;

	default:
		break;
	}
}
