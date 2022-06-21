#include "SelectSceneState.h"
#include "GameState.h"
#include "ClearState.h"
#include "GameOverState.h"
#include "../Controller.h"
#include "../Keyboard.h"
#include "../Camera.h"
#include "../SceneManager.h"
#include "../GameScene.h"

void GameState::Init(Camera *obj)
{
	//obj->Bind(false);
	obj->m_Position = { 0, 0, -60 };
	obj->m_Look = 0;
	obj->m_Up = { 0, 1, 0 };
	obj->m_LatePosition = obj->m_Position;
	obj->m_LateLook = obj->m_Look;
	obj->m_Angle = 60.0f;
	obj->m_Near = 0.5f;
	obj->m_Far = 1000.0f;
	obj->m_xzAngle = 0.0f;
	obj->m_yAngle = 10.0f;
	obj->m_radius = 55.0f;
	//obj->m_pTarget = nullptr;

	m_bTracking = false;
}

void GameState::Update(Camera *obj)
{
	if (obj->m_pTarget == nullptr) return;

	const float AngleMove(1.0f);
	const float RAD = 3.141519f / 180.0f;

	// ボスとの距離反映
	DirectX::XMFLOAT3 PlayerPos = obj->m_pTarget->Get<Transform>()->Position.DXFloat3();
	DirectX::XMFLOAT3 BossPos = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Transform>()->Position.DXFloat3();
	DirectX::XMVECTOR PlayerV, BossV;
	PlayerV = DirectX::XMLoadFloat3(&PlayerPos);
	BossV = DirectX::XMLoadFloat3(&BossPos);
	DirectX::XMVECTOR dist = DirectX::XMVectorSubtract(BossV, PlayerV);
	DirectX::XMVECTOR len = DirectX::XMVector3Length(dist);
	float fLength;
	DirectX::XMStoreFloat(&fLength, len);
	obj->m_radius = 100 - fLength * 0.05f;
	// ターゲットオブジェクト追跡
	obj->m_Look = obj->m_pTarget->Get<Transform>()->Position;
	obj->m_Look.y += 65 - fLength / 12.0f;

	//// 視点変更
	//static bool bFar;
	//if (IsKeyTrigger('Q'))
	//{
	//	bFar ^= 1;
	//	if (bFar)
	//	{
	//		obj->m_radius = 260;
	//		obj->m_yAngle = 70;
	//	}
	//	else
	//	{
	//		obj->m_radius = 55;
	//		obj->m_yAngle = 10;
	//	}
	//}

	// 角度変更
	if (IsKeyPress(VK_LEFT) | PAD->IsRStickLeft())
	{
		obj->m_xzAngle += AngleMove;
		m_bTracking = false;
	}
	if (IsKeyPress(VK_RIGHT) | PAD->IsRStickRight())
	{
		obj->m_xzAngle -= AngleMove;
		m_bTracking = false;
	}

	//if (IsKeyPress(VK_UP) | PAD->IsRStickUp())
	//{
	//	obj->m_yAngle += AngleMove;
	//	m_bTracking = false;
	//	if (obj->m_yAngle >= 90.0f) obj->m_yAngle = 89.0f;
	//}

	//if (IsKeyPress(VK_DOWN) | PAD->IsRStickDown())
	//{
	//	obj->m_yAngle -= AngleMove;
	//	m_bTracking = false;
	//	if (obj->m_yAngle <= 5.0f) obj->m_yAngle = 6.0f;
	//}

	// カメラ位置計算
	float xzRad = obj->m_xzAngle * 3.141592f / 180.0f;
	float yRad = obj->m_yAngle * 3.141592f / 180.0f;
	obj->m_Position.x = (cos(yRad) * sin(xzRad) * obj->m_radius);
	obj->m_Position.z = (cos(yRad) * -cos(xzRad) * obj->m_radius);
	obj->m_Position.y = (sin(yRad) * obj->m_radius);
	obj->m_Position += obj->m_Look;

	// 遅れ表現用の倍率
	float fLate = 0.1f;
	Float3 Move;
	// 注視点の遅れ表現
	Move = obj->m_Look - obj->m_LateLook;
	Move *= fLate;
	obj->m_LateLook += Move;

	// カメラ座標の遅れ表現
	Move = obj->m_Position - obj->m_LatePosition;
	Move *= fLate;
	obj->m_LatePosition += Move;

	// ステート切り替え
	if (GameScene::m_Step == GAMESCENE::CLEAR)
	{
		ChangeState(obj, ClearState::GetInstance());
	}
	if (GameScene::m_Step == GAMESCENE::GOVER)
	{
		ChangeState(obj, GameOverState::GetInstance());
	}
	if (SceneManager::GetInstance()->GetCurrentScene() == SCENE::TYPE::RESULT)
	{
		ChangeState(obj, SelectSceneState::GetInstance());
	}
}

//void GameState::Uninit()
//{
//	m_Aim.Uninit();
//}
//
//void GameState::Draw()
//{
//	m_Aim.Draw();
//}

void GameState::ChangeState(Camera *obj, CameraState *newState)
{
	obj->m_State = newState;
	obj->m_State->Init(obj);
}
