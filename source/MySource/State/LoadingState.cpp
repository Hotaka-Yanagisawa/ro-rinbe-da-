#include "LoadingState.h"
#include "EnemyPlayer.h"
#include "FireState.h"
#include "../Object.h"
#include "../GameScene.h"
#include "../Keyboard.h"
#include "../Controller.h"

void LoadingState::Init(EnemyPlayer *obj)
{
	m_Transform = obj->m_Parent->Get<Transform>();
	PlayerTransform = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>();
}

void LoadingState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	m_Transform = obj->m_Parent->Get<Transform>();
	m_Transform->Position = PlayerTransform->Position;
	m_Transform->Position.y = PlayerTransform->Position.y + 30;
	m_Transform->Rotate.x += 0.2f;
	m_Transform->Rotate.y += 0.15f;
	m_Transform->Rotate.z += 0.4f;


	if (IsKeyTrigger(VK_SPACE) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		float Magnification = 1.0f;
		if (EnemyPlayer::m_nLoadingNum < 2)	Magnification = 1.0f;
		else if(EnemyPlayer::m_nLoadingNum  < 4)	Magnification = 1.25f;
		else if(EnemyPlayer::m_nLoadingNum < 7) Magnification = 1.5f;
		else if (EnemyPlayer::m_nLoadingNum < 10) Magnification = 1.75f;

		if (EnemyPlayer::m_nLoadingNum == 10)
		{
			Magnification = 2.0f;
		}
		
		while (!EnemyPlayer::m_LoadingQueue.empty())
		{
			EnemyPlayer::m_LoadingQueue.front()->SetState(FireState::GetInstance());
			EnemyPlayer::m_LoadingQueue.front()->GetState()->Init(EnemyPlayer::m_LoadingQueue.front());
			EnemyPlayer::m_LoadingQueue.front()->m_fAttack *= Magnification;
			EnemyPlayer::m_LoadingQueue.pop();
			EnemyPlayer::m_nLoadingNum--;
		}
		obj->m_Sound.m_pBuffer = obj->m_Sound.CreateSound("Assets/Sound/SE/Fire.mp3", false);
		obj->m_Sound.m_pSpeaker = obj->m_Sound.PlaySound(obj->m_Sound.m_pBuffer);
		obj->m_Sound.m_pSpeaker->SetVolume(0.0f);
		obj->m_Sound.m_bFade = false;
		obj->m_Sound.m_bFade = obj->m_Sound.Fade(2.0f, 0.1f);
	}
}
