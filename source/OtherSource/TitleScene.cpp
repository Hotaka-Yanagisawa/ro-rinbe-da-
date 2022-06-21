//--- インクルード
#include "TitleScene.h"
#include "Keyboard.h"
#include "Load.h"
#include "Defines.h"
#include "Controller.h"

//==================================================
// 初期化
//==================================================
void TitleScene::Init()
{
	// ポリゴン追加
	m_PolList.Add(new Pol2D, "BackGround");
	m_PolList.Add(new Pol2D, "Cloud");
	m_PolList.Add(new Pol2D, "Cloud2");
	m_PolList.Add(new Pol2D, "mountain2");
	m_PolList.Add(new Pol2D, "Cloud3");
	m_PolList.Add(new Pol2D, "mountain3");
	m_PolList.Add(new Pol2D, "Cloud4");
	m_PolList.Add(new Pol2D, "iseki1");

	m_PolList.Add(new Pol2D, "lock1");
	m_PolList.Add(new Pol2D, "lock2");
	m_PolList.Add(new Pol2D, "iseki2");
	m_PolList.Add(new Pol2D, "ground");
	m_PolList.Add(new Pol2D, "glass1");
	m_PolList.Add(new Pol2D, "hole");
	m_PolList.Add(new Pol2D, "glass2");
	m_PolList.Add(new Pol2D, "hole2");

	m_PolList.Add(new Pol2D, "around");
	m_PolList.Add(new Pol2D, "Logo");
	m_PolList.Add(new Pol2D, "Push");
	m_PolList.Add(new Pol2D, "Button");

	m_PolList.Init();

	// ロゴ
	Pol2D* tmp = m_PolList.Get("Logo");
	tmp->SetTexture(TEX_PNG("Title"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 700;
	tmp->m_Transform.Size.y = 500;
	tmp->m_Transform.Position = { 0, 100, 0 };

	m_RogoRadius = 1.0f;
	m_RogoRadian = 0.0f;
	m_RogoFlag = false;

	//around
	tmp = m_PolList.Get("around");
	tmp->SetTexture(TEX_PNG("Around"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = SCREEN_WIDTH + 40;
	tmp->m_Transform.Size.y = SCREEN_HEIGHT + 40;
	tmp->m_Transform.Position = { 0, 0, 0 };

	//BackGround
	tmp = m_PolList.Get("BackGround");
	tmp->SetTexture(TEX_PNG("BlueSky"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = SCREEN_WIDTH;
	tmp->m_Transform.Size.y = SCREEN_HEIGHT;
	tmp->m_Transform.Position = { 0, 0, 0 };

	//Croud
	tmp = m_PolList.Get("Cloud");
	tmp->SetTexture(TEX_PNG("Cloud1"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 600;
	tmp->m_Transform.Size.y = 400;
	tmp->m_Transform.Position = { -200.0f,200.0f, 0 };

	tmp = m_PolList.Get("Cloud2");
	tmp->SetTexture(TEX_PNG("Cloud2"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 600;
	tmp->m_Transform.Size.y = 400;
	tmp->m_Transform.Position = { 200.0f,400.0f, 0 };

	tmp = m_PolList.Get("Cloud3");
	tmp->SetTexture(TEX_PNG("Cloud3"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 800;
	tmp->m_Transform.Size.y = 600;
	tmp->m_Transform.Position = { 700.0f, 250.0f, 0 };

	tmp = m_PolList.Get("Cloud4");
	tmp->SetTexture(TEX_PNG("Cloud4"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 800;
	tmp->m_Transform.Size.y = 600;
	tmp->m_Transform.Position = { 400.0f,0.0f, 0 };

	//Ground
	tmp = m_PolList.Get("ground");
	tmp->SetTexture(TEX_PNG("GroundBase"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = SCREEN_WIDTH;
	tmp->m_Transform.Size.y = SCREEN_HEIGHT + 30;
	tmp->m_Transform.Position = { 0, 20.0f, 0 };

	//mountain2,3
	tmp = m_PolList.Get("mountain2");
	tmp->SetTexture(TEX_PNG("Mountain2"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 1200;
	tmp->m_Transform.Size.y = 700;
	tmp->m_Transform.Position = { 260.0f, 10.0f, 0 };

	tmp = m_PolList.Get("mountain3");
	tmp->SetTexture(TEX_PNG("Mountain3"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 1200;
	tmp->m_Transform.Size.y = 800;
	tmp->m_Transform.Position = { -300.0f, 10.0f, 0 };

	//iseki1,2
	tmp = m_PolList.Get("iseki1");
	tmp->SetTexture(TEX_PNG("Iseki1"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 900;
	tmp->m_Transform.Size.y = 700;
	tmp->m_Transform.Position = { -300.0f, -60.0f, 0 };

	tmp = m_PolList.Get("iseki2");
	tmp->SetTexture(TEX_PNG("Iseki2"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 900;
	tmp->m_Transform.Size.y = 700;
	tmp->m_Transform.Position = { 400.0f, -10.0f, 0 };

	// rock1,2
	tmp = m_PolList.Get("lock1");
	tmp->SetTexture(TEX_PNG("Rock1"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 800;
	tmp->m_Transform.Size.y = 800;
	tmp->m_Transform.Position = { -400.0f,-140.0f, 0 };

	tmp = m_PolList.Get("lock2");
	tmp->SetTexture(TEX_PNG("Rock2"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 800;
	tmp->m_Transform.Size.y = 800;
	tmp->m_Transform.Position = { 200.0f,-190.0f, 0 };

	//grass,hole
	tmp = m_PolList.Get("glass1");
	tmp->SetTexture(TEX_PNG("Grass1"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 400;
	tmp->m_Transform.Size.y = 400;
	tmp->m_Transform.Position = { -320.0f,-220.0f, 0 };

	tmp = m_PolList.Get("glass2");
	tmp->SetTexture(TEX_PNG("Grass2"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 600;
	tmp->m_Transform.Size.y = 600;
	tmp->m_Transform.Position = { 250.0f,-220.0f, 0 };

	tmp = m_PolList.Get("hole");
	tmp->SetTexture(TEX_PNG("Hole1"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 400;
	tmp->m_Transform.Size.y = 400;
	tmp->m_Transform.Position = { 350.0f, -300.0f, 0 };

	tmp = m_PolList.Get("hole2");
	tmp->SetTexture(TEX_PNG("Hole2"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 500;
	tmp->m_Transform.Size.y = 500;
	tmp->m_Transform.Position = { -280.0f, -300.0f, 0 };

	// PushEnter
	tmp = m_PolList.Get("Push");
	tmp->SetTexture(TEX_PNG("PressButton"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 350;
	tmp->m_Transform.Size.y = 80;
	tmp->m_Transform.Position = { 0, -250, 0 };

	// Button
	tmp = m_PolList.Get("Button");
	tmp->SetTexture(TEX_PNG("Button"));
	tmp->m_bParallel = true;
	tmp->m_Transform.Size.x = 320;
	tmp->m_Transform.Size.y = 180;
	tmp->m_Transform.Position = { 230, -250, 0 };

	m_timer = 0.0f;
	m_Color = true;
	m_ColorA = 0.0f;
	m_AlphaFlag = false;

	m_Sound.m_pBuffer = m_Sound.CreateSound("Assets/Sound/BGM/Title.mp3", true);
	m_Sound.m_pSpeaker = m_Sound.PlaySound(m_Sound.m_pBuffer);
	m_Sound.m_pSpeaker->SetVolume(0.0f);
	m_Sound.m_bFade = false;
	m_Sound.m_bFade = m_Sound.Fade(0.5f, 3.f);
}

//==================================================
// 終了
//==================================================
void TitleScene::Uninit()
{
	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	m_Sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上かつフェードしてなかったらストップ
	if (state.BuffersQueued > 0)
	{
		m_Sound.m_pSpeaker->Stop();
	}

	//m_SE.m_pSpeaker->GetState(&state);
	////なってる音が一つ以上かつフェードしてなかったらストップ
	//if (state.BuffersQueued > 0)
	//{
	//	m_SE.m_pSpeaker->Stop();
	//}
	m_PolList.Uninit();
}

//==================================================
// 更新
//==================================================
SCENE::TYPE TitleScene::Update()
{
	//Fadeが呼ばれたら機能する
	m_Sound.Update();
	m_SE.Update();

	//Cloud
	m_PolList.Get("Cloud")->m_Transform.Position.x -= 1.0f;

	if ((m_PolList.Get("Cloud")->m_Transform.Position.x) < -800)
	{

		m_PolList.Get("Cloud")->m_Transform.Position.x = 800;
	}

	//Cloud2
	m_PolList.Get("Cloud2")->m_Transform.Position.x -= 1.0f;

	if ((m_PolList.Get("Cloud2")->m_Transform.Position.x) < -800)
	{

		m_PolList.Get("Cloud2")->m_Transform.Position.x = 800;
	}

	//Cloud3
	m_PolList.Get("Cloud3")->m_Transform.Position.x -= 1.0f;

	if ((m_PolList.Get("Cloud3")->m_Transform.Position.x) < -800)
	{

		m_PolList.Get("Cloud3")->m_Transform.Position.x = 800;
	}

	//Cloud3
	m_PolList.Get("Cloud4")->m_Transform.Position.x -= 1.0f;

	if ((m_PolList.Get("Cloud4")->m_Transform.Position.x) < -800)
	{

		m_PolList.Get("Cloud4")->m_Transform.Position.x = 800;
	}

	//grass
	m_PolList.Get("glass1")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("glass1")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("glass1")->m_Transform.Position.x = 800;
	}

	//hole
	m_PolList.Get("hole")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("hole")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("hole")->m_Transform.Position.x = 800;
	}

	//grass2
	m_PolList.Get("glass2")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("glass2")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("glass2")->m_Transform.Position.x = 800;
	}

	//hole2
	m_PolList.Get("hole2")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("hole2")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("hole2")->m_Transform.Position.x = 800;
	}

	//mountain
	m_PolList.Get("mountain2")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("mountain2")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("mountain2")->m_Transform.Position.x = 800;
	}

	//mountain
	m_PolList.Get("mountain3")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("mountain3")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("mountain3")->m_Transform.Position.x = 800;
	}

	//rock
	m_PolList.Get("lock1")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("lock1")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("lock1")->m_Transform.Position.x = 800;
	}

	//rock
	m_PolList.Get("lock2")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("lock2")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("lock2")->m_Transform.Position.x = 800;
	}

	//iseki2
	m_PolList.Get("iseki2")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("iseki2")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("iseki2")->m_Transform.Position.x = 800;
	}

	//iseki1
	m_PolList.Get("iseki1")->m_Transform.Position.x -= 0.5f;

	if ((m_PolList.Get("iseki1")->m_Transform.Position.x) < -900)
	{

		m_PolList.Get("iseki1")->m_Transform.Position.x = 800;
	}

	//----------------Logo---------------------------
	float Rad = 3.1415f / 180.0f;

	if (m_RogoRadius > 90.0f * Rad)
	{
		m_RogoFlag = false;
	}

	if (m_RogoRadius < 45.0f*Rad)
	{
		m_RogoFlag = true;
	}

	if (m_RogoFlag == false)
	{
		m_RogoRadius -= 0.5f * Rad;
	}

	if (m_RogoFlag == true)
	{
		m_RogoRadius += 0.5f * Rad;
	}

	m_RogoRadian = sinf(m_RogoRadius);
	m_PolList.Get("Logo")->m_Transform.Size.x = m_RogoRadian * 700;
	m_PolList.Get("Logo")->m_Transform.Size.y = m_RogoRadian * 500;

	//------------------PressButton---------------
	if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B) && m_timer == 0)
	{
		m_Sound.m_bFade = m_Sound.Fade(0.0f, 15.0f);
		m_SE.m_pBuffer = m_SE.CreateSound("Assets/Sound/SE/Press.mp3", false);
		m_SE.m_pSpeaker = m_SE.PlaySound(m_SE.m_pBuffer);
		m_SE.m_pSpeaker->SetVolume(0.0f);
		m_SE.m_bFade = false;
		m_SE.m_bFade = m_SE.Fade(1.5f, 0.1f);
		m_timer++;
	}
	else
	{
		if (m_ColorA > 1.0f)
		{
			m_AlphaFlag = true;

		}
		if (m_ColorA < 0.0f)
		{
			m_AlphaFlag = false;
		}

		if (m_AlphaFlag == true)
		{
			m_ColorA -= 0.02f;
		}
		else
		{
			m_ColorA += 0.02f;
		}

		m_PolList.Get("Push")->m_a = m_ColorA;
		m_PolList.Get("Button")->m_a = m_ColorA;

	}

	if (m_timer > 0.0f)
	{
		m_timer++;

		if ((int)m_timer % 3 == 0)
		{
			m_Color ^= 1;

		}

		if (m_timer >= 60.0f)
		{
			return SCENE::SELECT;
		}
		m_PolList.Get("Push")->m_a = m_Color;
		m_PolList.Get("Button")->m_a = m_Color;
	}
	//------------------------------------------

	m_PolList.Update();

	return SCENE::NO;
}

//==================================================
// 描画
//==================================================
void TitleScene::Draw()
{
	m_PolList.Draw();
}
