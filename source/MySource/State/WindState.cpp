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
	//このステートにいるエネミーの数
	EnemyPlayer::MyNum++;
	//m_fIntervalCnt = EnemyPlayer::MyNum * 0.2f;
	m_fIntervalCnt = 0.001;
	m_bIntervalFlag = false;
	//このステートに来たらキューに追加、発射順となる
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
	// プレイヤーについていく
	m_Transform = obj->m_Parent->Get<Transform>();

	obj->m_xzAngle += float(rand() % 3 + 5);
	obj->m_yAngle += float(rand() % 10 + 1);
	obj->m_Angle += float(rand() % 5);
	//描く円の半径
	obj->m_radius += 2.0f / 60.0f;
	
	//描く円の半径の上限
	if (obj->m_radius > 3.0f) obj->m_radius = 3.0f;
	//回転速度が変わる？
	if (obj->m_yAngle >= 120.0f)	obj->m_yAngle = 120.0f;

	//πはラジアン角の180度　度の180で割ることにより１となりラジアンに変換
	float xzRad = obj->m_xzAngle * 3.141592f / 180.0f;
	float yRad = obj->m_yAngle * 3.141592f / 180.0f;
	float Rad = obj->m_Angle * 3.141592f / 180.0f;

	//上昇気流的なの
	m_Transform->Move = Float3(cosf(yRad) * sinf(xzRad) * obj->m_radius,
								m_Transform->Move.y,
								cosf(yRad) * -cosf(xzRad)  * obj->m_radius);
	m_Transform->Move.y += (PlayerTransform->Size.y * 5.0f) / 180.0f;
	
	//無限に上に行かないように制御: 
	if (m_Transform->Move.y > PlayerTransform->Size.y * 3.0f)
		m_Transform->Move.y = PlayerTransform->Size.y * 3.0f;

	m_Transform->Rotate.x += 0.1f;
	m_Transform->Rotate.y += 0.1f;
	m_Transform->Rotate.z += 0.1f;

	m_Transform->Position.x += PlayerTransform->Move.x + m_Transform->Move.x;
	//sinfで上下移動　moveで一定距離まで上昇
	m_Transform->Position.y = sinf(Rad) * 5.0f + m_Transform->Move.y;
	m_Transform->Position.z += PlayerTransform->Move.z + m_Transform->Move.z;
	// 吹き飛ばす
	if ((IsKeyPress(VK_SPACE) || PAD->IsButtonsPress(XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_bIntervalFlag)
	{
		Fire(obj);
		m_bIntervalFlag = false;
	}


	// 纏める
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
	//キューを使用してこのステート来た順に発射できるようにする
	if (!EnemyPlayer::m_FireQueue.empty())
	{
		//キャパからオブジェクトの重さ引く
		EnemyPlayer::m_fCapa -= obj->m_fWeight;
		//ステート移行
		EnemyPlayer::m_FireQueue.front()->SetState(FireState::GetInstance());
		EnemyPlayer::m_FireQueue.front()->GetState()->Init(EnemyPlayer::m_FireQueue.front());
		//キューから外す
		EnemyPlayer::m_FireQueue.pop();
		//SE鳴らす
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
	//キューを使用してこのステート来た順に発射できるようにする
	if (!EnemyPlayer::m_FireQueue.empty())
	{
		//キューの先頭が木の場合処理を行わないため
		//キューの中身を入れ替える処理を行う
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
		//木は纏めない
		//if (EnemyPlayer::m_FireQueue.front()->m_Parent->m_Tag == OBJECT::TREE) return;
		//キャパから重さ減らす
		EnemyPlayer::m_fCapa -= EnemyPlayer::m_FireQueue.front()->m_fWeight;
		//ステート移行
		EnemyPlayer::m_FireQueue.front()->SetState(LoadingState::GetInstance());
		EnemyPlayer::m_FireQueue.front()->GetState()->Init(EnemyPlayer::m_FireQueue.front());
		//装弾キューに追加
		EnemyPlayer::m_LoadingQueue.push(EnemyPlayer::m_FireQueue.front());
		//SE鳴らす
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_pBuffer =
			EnemyPlayer::m_FireQueue.front()->m_Sound.CreateSound("Assets/Sound/SE/Charge.mp3", false);
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_pSpeaker =
			EnemyPlayer::m_FireQueue.front()->m_Sound.PlaySound
			(EnemyPlayer::m_FireQueue.front()->m_Sound.m_pBuffer);
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_pSpeaker->SetVolume(0.0f);
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_bFade = false;
		EnemyPlayer::m_FireQueue.front()->m_Sound.m_bFade =
			EnemyPlayer::m_FireQueue.front()->m_Sound.Fade(2.0f, 0.1f);
		//発射キューから外す
		EnemyPlayer::m_FireQueue.pop();
		//装填弾数増やす
		EnemyPlayer::m_nLoadingNum++;
		m_fIntervalCnt = 0.5f;
	}
}
