//--- インクルード
#include "SceneManager.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Camera.h"
#include "Light.h"
#include "Load.h"

//==================================================
// コンストラクタ
//==================================================
SceneManager::SceneManager()
{
	CAMERA->Init();
	LIGHT->Init();
	m_Fade.Init();
	m_Effect.Init();

	m_Scene[SCENE::TITLE] =	new TitleScene();
	m_Scene[SCENE::SELECT] = new SelectScene();
	m_Scene[SCENE::GAME] = new GameScene();
	m_Scene[SCENE::RESULT] = new ResultScene();

}

//==================================================
// デストラクタ
//==================================================
SceneManager::~SceneManager()
{
	m_Effect.Uninit();
	m_Fade.Uninit();
	CAMERA->Uninit();
	LIGHT->Uninit();

	for (int i = SCENE::TITLE; i < SCENE::MAX; ++i)
		delete m_Scene[i];
}

//==================================================
// 初期化
//==================================================
void SceneManager::Init(SCENE::TYPE Type)
{
	m_CurrentScene = Type;
	m_NextScene = SCENE::NO;
	m_Scene[m_CurrentScene]->Init();
}

//==================================================
// 終了
//==================================================
void SceneManager::Uninit()
{
	m_Scene[m_CurrentScene]->Uninit();
}

//==================================================
// 更新
//==================================================
void SceneManager::Update()
{
	// 遷移情報取得
	SCENE::TYPE Next =
		m_Scene[m_CurrentScene]->Update();

	//--- シーン遷移
	// フェードアウト完了
	if (m_Fade.Update())
	{
		Uninit();
		CAMERA->Init();
		Init(m_NextScene);
	}
	// フェードアウト開始
	if (Next != SCENE::NO)
	{
		m_NextScene = Next;
		m_Fade.FadeOut(30);
	}

	CAMERA->Update();
	LIGHT->Update();

	m_Effect.Update();
}

//==================================================
// 描画
//==================================================
void SceneManager::Draw()
{
	CAMERA->Bind();
	m_Scene[m_CurrentScene]->Draw();

	m_Effect.Draw();
	m_Fade.Draw();
}
