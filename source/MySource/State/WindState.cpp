#include "WindState.h"
#include "FireState.h"
#include "LoadingState.h"
#include "EnemyPlayer.h"
#include "../GameScene.h"
#include "../Keyboard.h"
#include "../Controller.h"


void WindState::Init(EnemyPlayer *obj)
{
	m_Transform = obj->m_Parent->Get<Transform>();
	PlayerTransform = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>();
	
	m_Transform->Move = 0;
	obj->m_radius = 0;
	obj->m_xzAngle = 0;
	obj->m_yAngle = 0;
	obj->m_radius = 0;
	obj->m_Angle = 0;
	EnemyPlayer::m_TotalSucksNum++;
	//���̃X�e�[�g�ɂ���G�l�~�[�̐�
	EnemyPlayer::MyNum++;
	//m_fIntervalCnt = EnemyPlayer::MyNum * 0.2f;
	m_fIntervalCnt = 0.001;
	m_bIntervalFlag = false;
	//���̃X�e�[�g�ɗ�����L���[�ɒǉ��A���ˏ��ƂȂ�
	EnemyPlayer::m_FireQueue.push(obj);
	EnemyPlayer::m_fCapa += obj->m_fWeight;

	obj->m_Sound.m_pBuffer = obj->m_Sound.CreateSound("Assets/Sound/SE/Charge.mp3", false);
	obj->m_Sound.m_pSpeaker = obj->m_Sound.PlaySound(obj->m_Sound.m_pBuffer);
	obj->m_Sound.m_pSpeaker->SetVolume(0.0f);
	obj->m_Sound.m_bFade = false;
	obj->m_Sound.m_bFade = obj->m_Sound.Fade(0.0f, 0.1f);
}

void WindState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	// �v���C���[�ɂ��Ă���
	m_Transform = obj->m_Parent->Get<Transform>();

	obj->m_xzAngle += float(rand() % 3 + 5);
	obj->m_yAngle += float(rand() % 10 + 1);
	obj->m_Angle += float(rand() % 5);
	//�`���~�̔��a
	obj->m_radius += 2.0f / 60.0f;
	
	//�`���~�̔��a�̏��
	if (obj->m_radius > 3.0f) obj->m_radius = 3.0f;
	//��]���x���ς��H
	if (obj->m_yAngle >= 120.0f)	obj->m_yAngle = 120.0f;

	//�΂̓��W�A���p��180�x�@�x��180�Ŋ��邱�Ƃɂ��P�ƂȂ胉�W�A���ɕϊ�
	float xzRad = obj->m_xzAngle * 3.141592f / 180.0f;
	float yRad = obj->m_yAngle * 3.141592f / 180.0f;
	float Rad = obj->m_Angle * 3.141592f / 180.0f;

	//�㏸�C���I�Ȃ�
	m_Transform->Move = Float3(cosf(yRad) * sinf(xzRad) * obj->m_radius,
								m_Transform->Move.y,
								cosf(yRad) * -cosf(xzRad)  * obj->m_radius);
	m_Transform->Move.y += (PlayerTransform->Size.y * 5.0f) / 180.0f;
	
	//�����ɏ�ɍs���Ȃ��悤�ɐ���: 
	if (m_Transform->Move.y > PlayerTransform->Size.y * 3.0f)
		m_Transform->Move.y = PlayerTransform->Size.y * 3.0f;

	m_Transform->Rotate.x += 0.1f;
	m_Transform->Rotate.y += 0.1f;
	m_Transform->Rotate.z += 0.1f;

	m_Transform->Position.x += PlayerTransform->Move.x + m_Transform->Move.x;
	//sinf�ŏ㉺�ړ��@move�ň�苗���܂ŏ㏸
	m_Transform->Position.y = sinf(Rad) * 5.0f + m_Transform->Move.y;
	m_Transform->Position.z += PlayerTransform->Move.z + m_Transform->Move.z;
	// ������΂�
	if ((IsKeyPress(VK_SPACE) || PAD->IsButtonsPress(XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_bIntervalFlag)
	{
		Fire(obj);
		m_bIntervalFlag = false;
	}


	// �Z�߂�
	if ((IsKeyPress(VK_SHIFT) || PAD->IsButtonsPress(XINPUT_GAMEPAD_LEFT_SHOULDER))&& m_bIntervalFlag)
	{
		Loading(obj);
		m_bIntervalFlag = false;
	}

	if (!m_bIntervalFlag)
	{
		if (m_fIntervalCnt >= 0)
		{
			m_fIntervalCnt -= 2.0f / 60.0f;
		}
	}
	if (m_fIntervalCnt < 0) m_bIntervalFlag = true;
	
}

void WindState::Fire(EnemyPlayer *obj)
{
	if (!m_bIntervalFlag) return;
	//�L���[���g�p���Ă��̃X�e�[�g�������ɔ��˂ł���悤�ɂ���
	if (!EnemyPlayer::m_FireQueue.empty())
	{
		//�L���p����I�u�W�F�N�g�̏d������
		EnemyPlayer::m_fCapa -= obj->m_fWeight;
		//�X�e�[�g�ڍs
		EnemyPlayer::m_FireQueue.front()->SetState(FireState::GetInstance());
		EnemyPlayer::m_FireQueue.front()->GetState()->Init(EnemyPlayer::m_FireQueue.front());
		//�L���[����O��
		EnemyPlayer::m_FireQueue.pop();
		//SE�炷
		obj->m_Sound.m_pBuffer = obj->m_Sound.CreateSound("Assets/Sound/SE/Fire.mp3", false);
		obj->m_Sound.m_pSpeaker = obj->m_Sound.PlaySound(obj->m_Sound.m_pBuffer);
		obj->m_Sound.m_pSpeaker->SetVolume(0.0f);
		obj->m_Sound.m_bFade = false;
		obj->m_Sound.m_bFade = obj->m_Sound.Fade(1.0f, 0.1f);

		m_fIntervalCnt = 0.5f;
	}
}

void WindState::Loading(EnemyPlayer *obj)
{
	//if (obj->m_Parent->m_Tag == OBJECT::TREE) return;
	if (!m_bIntervalFlag) return;
	if (EnemyPlayer::m_nLoadingNum >= 10) return;
	//�L���[���g�p���Ă��̃X�e�[�g�������ɔ��˂ł���悤�ɂ���
	if (!EnemyPlayer::m_FireQueue.empty())
	{
		//�L���[�̐擪���؂̏ꍇ�������s��Ȃ�����
		//�L���[�̒��g�����ւ��鏈�����s��
		if (EnemyPlayer::m_FireQueue.front()->m_Parent->m_Tag == OBJECT::TREE)
		{
			for (int i = 0; i < EnemyPlayer::m_FireQueue.size(); i++)
			{
				EnemyPlayer::m_FireQueue.push(EnemyPlayer::m_FireQueue.front());
				EnemyPlayer::m_FireQueue.pop();
				if (EnemyPlayer::m_FireQueue.front()->m_Parent->m_Tag != OBJECT::TREE)
				{
					break;
				}
			}
		}
		//�؂͓Z�߂Ȃ�
		//if (EnemyPlayer::m_FireQueue.front()->m_Parent->m_Tag == OBJECT::TREE) return;
		//�L���p����d�����炷
		EnemyPlayer::m_fCapa -= EnemyPlayer::m_FireQueue.front()->m_fWeight;
		//�X�e�[�g�ڍs
		EnemyPlayer::m_FireQueue.front()->SetState(LoadingState::GetInstance());
		EnemyPlayer::m_FireQueue.front()->GetState()->Init(EnemyPlayer::m_FireQueue.front());
		//���e�L���[�ɒǉ�
		EnemyPlayer::m_LoadingQueue.push(EnemyPlayer::m_FireQueue.front());
		//SE�炷
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_pBuffer =
			EnemyPlayer::m_FireQueue.front()->m_Sound.CreateSound("Assets/Sound/SE/Charge.mp3", false);
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_pSpeaker =
			EnemyPlayer::m_FireQueue.front()->m_Sound.PlaySound
			(EnemyPlayer::m_FireQueue.front()->m_Sound.m_pBuffer);
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_pSpeaker->SetVolume(0.0f);
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_bFade = false;
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_bFade =
			EnemyPlayer::m_FireQueue.front()->m_Sound.Fade(2.0f, 0.1f);
		//���˃L���[����O��
		EnemyPlayer::m_FireQueue.pop();
		//���U�e�����₷
		EnemyPlayer::m_nLoadingNum++;
		m_fIntervalCnt = 0.5f;
	}
}
