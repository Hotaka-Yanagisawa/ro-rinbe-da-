//--- �C���N���[�h
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

//--- �ÓI�����o�ϐ�
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
// ������
//==================================================
void GameScene::Init()
{
	nWaitResult = 0;

	// �X�R�A
	Score::GetInstance()->Init();

	// �X�e�b�v
	m_Step = GAMESCENE::START;

	// �����蔻��Ǘ��N���X
	Collision::GetInstance()->Init();

	//--- �Q�[���I�u�W�F�N�g
	m_pObjList = new ObjectList;
	// �w�i
	m_pObjList->Create(OBJECT::BACK);
	// �t�B�[���h
	m_pObjList->Create(OBJECT::FIELD);
	// �G�l�~�[
	m_EnemyManager.Init();
	// ��D
	m_pObjList->Create(OBJECT::BOSS);
	//--- �v���C���[
	// ������A�J�����̃^�[�Q�b�g�ɐݒ�
	Object* pPlayer = m_pObjList->Create(OBJECT::PLAYER);
	Camera::GetInstance()->SetObject(pPlayer);
	// ��
	for (int i = 0; i < 50; i++)
		m_pObjList->Create(OBJECT::TREE);
	for (int i = 0; i < 200; i++)
		m_pObjList->Create(OBJECT::BTREE);
	//--- �_�a
	// �{��
	m_pObjList->Create(OBJECT::TEMPLE);
	// ��
	for (int i = 0; i < 4; ++i)
		m_pObjList->Create(OBJECT::PILLAR)->Get<Transform>()->Position
		= { 30 * (i % 2 * 2.0f - 1), 30, 25 * (i / 2 * 2.0f - 1) };
	// ��
	m_pObjList->Create(OBJECT::FLOOR1);
	m_pObjList->Create(OBJECT::FLOOR2);
	m_pObjList->Create(OBJECT::FLOOR3);
	// �R�A
	m_pObjList->Create(OBJECT::CORE);
	// UI
	m_UI.Init();
	// �^�C�}�[
	Timer::GetInstance()->SetTime(120 * 60);
	//�G�l�~�[�̃L���[��������
	EnemyPlayer::QueueClear();
	//�z�����񂾐��̍��v��������
	EnemyPlayer::m_TotalSucksNum = 0;
	//�z�����߂�e�ʂ̏�����
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
// �I��
//==================================================
void GameScene::Uninit()
{
	XAUDIO2_VOICE_STATE state;
	if (m_Sound.m_pSpeaker)
	{
		//�\�[�X�{�C�X�̏󋵂��擾
		m_Sound.m_pSpeaker->GetState(&state);
		//�Ȃ��Ă鉹����ȏ�Ȃ�X�g�b�v
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
// �X�V
//--------------------------------------------------
// �߂�l	: ���̃V�[��
//==================================================
SCENE::TYPE GameScene::Update()
{
	//Fade���Ă΂ꂽ��@�\����
	m_Sound.Update();
	// ���U���g�ҋ@����
	if (nWaitResult > 0)
	{
		--nWaitResult;

		m_pObjList->Get(OBJECT::BOSS)->Get<Fly>()->Update();

		if (nWaitResult == 0) return SCENE::RESULT;

		return SCENE::NO;
	}

	// UI�̍X�V
	switch (m_UI.Update())
	{
	// �|�[�Y��ʂ̂Ƃ��ȉ������s���Ȃ�
	case UISYS::PAUSE: return SCENE::NO;
	// �ăX�^�[�g
	case UISYS::RETRY: return SCENE::GAME;
	// �߂�
	case UISYS::EXIT: return SCENE::SELECT;
	default:
		break;
	}

	Score::GetInstance()->Update();

	// �^�C�}�[�̎擾
	int nTime = Timer::GetInstance()->GetTime();

	// �Q�[���N���A
	if (m_pObjList->Get(OBJECT::BOSS)->Get<Vitality>()->m_fHp <= 0)
	{
		m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
		m_Step = GAMESCENE::CLEAR;
		nWaitResult = 100;
	}
	// �Q�[���I�[�o�[
	if ((m_pObjList->Get(OBJECT::TEMPLE)->Get<Vitality>()->m_fHp <= 0)
		|| (nTime < 1))
	{
		m_Sound.m_bFade = m_Sound.Fade(0.0f, 0.1f);
		m_Step = GAMESCENE::GOVER;
		nWaitResult = 100;
	}
	// �Q�[���J�n
	if (m_Step == GAMESCENE::START && CAMERA->m_State == GameState::GetInstance())
	{
		//�T�E���h
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


	// �{�҂łȂ���Έȉ����s��Ȃ�
	if (m_Step != GAMESCENE::MAIN) return SCENE::NO;

	// �G�̐���
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

	// �����蔻��
	Collision::GetInstance()->Update();

	return SCENE::NO;
}

//==================================================
// �`��
//==================================================
void GameScene::Draw()
{
	m_pObjList->Draw();
	//MODEL->Draw();
	if (CAMERA->m_State == GameState::GetInstance())
	Score::GetInstance()->Draw();
	m_UI.Draw();
}
