//--- �C���N���[�h
#include "SceneManager.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Camera.h"
#include "Light.h"
#include "Load.h"

//==================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
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
// ������
//==================================================
void SceneManager::Init(SCENE::TYPE Type)
{
	m_CurrentScene = Type;
	m_NextScene = SCENE::NO;
	m_Scene[m_CurrentScene]->Init();
}

//==================================================
// �I��
//==================================================
void SceneManager::Uninit()
{
	m_Scene[m_CurrentScene]->Uninit();
}

//==================================================
// �X�V
//==================================================
void SceneManager::Update()
{
	// �J�ڏ��擾
	SCENE::TYPE Next =
		m_Scene[m_CurrentScene]->Update();

	//--- �V�[���J��
	// �t�F�[�h�A�E�g����
	if (m_Fade.Update())
	{
		Uninit();
		CAMERA->Init();
		Init(m_NextScene);
	}
	// �t�F�[�h�A�E�g�J�n
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
// �`��
//==================================================
void SceneManager::Draw()
{
	CAMERA->Bind();
	m_Scene[m_CurrentScene]->Draw();

	m_Effect.Draw();
	m_Fade.Draw();
}
