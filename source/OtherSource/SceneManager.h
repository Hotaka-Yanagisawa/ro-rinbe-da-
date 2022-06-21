//=======================================================================
// SceneManager.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/29	�쐬
//		 12/10	��������p�[�e�B�N�����Ǘ�������
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Scene.h"
#include "Fade.h"
#include "Effect.h"
#include "Camera.h"

//--- �萔
#define EFFECT (SceneManager::GetInstance()->m_Effect)

//--- �N���X
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
