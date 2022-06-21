//=======================================================================
// SceneManager.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/29	作成
//		 12/10	いったんパーティクルを管理させる
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Scene.h"
#include "Fade.h"
#include "Effect.h"
#include "Camera.h"

//--- 定数
#define EFFECT (SceneManager::GetInstance()->m_Effect)

//--- クラス
class SceneManager
{
public:
	inline static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	void Init(SCENE::TYPE);
	void Uninit();

	void Update();
	void Draw();
	SCENE::TYPE GetCurrentScene() { return m_CurrentScene; }

	Scene* m_Scene[SCENE::MAX];

	Effect m_Effect;
	Fade m_Fade;

	SCENE::TYPE m_CurrentScene;

private:

	SCENE::TYPE m_NextScene;

	int m_nFadeCount;

	SceneManager();
	~SceneManager();
};
