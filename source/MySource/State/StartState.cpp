#include "StartState.h"
#include "GameState.h"
#include "../Camera.h"
#include "../Keyboard.h"
#include "../GameScene.h"
#include "../Transform.h"
#include "../GameScene.h"
#include "../Control.h"
#include "../Controller.h"

int a, b;


void StartState::Init(Camera *obj)
{
	m_Phase = UFO;
	m_PhaseCnt = 280;
	m_PhaseQueue.push(TEMPLE);
	//m_PhaseQueue.push(ENEMY);
	//m_PhaseQueue.push(PLAYER);
	m_PhaseQueue.push(CNT_DOWN);
	m_PhaseQueue.push(END);
	//m_PhaseQueue.push(ENEMY);
	//--- Init ---
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
	//--- Init ---
	a = b = 0;

	//obj->m_Position = (obj->m_Look.x, obj->m_Look.y, obj->m_Look.z - 60);
	//obj->m_Position = (200);
}

void StartState::Update(Camera *obj)
{
	obj->m_LatePosition = obj->m_Position;
	obj->m_LateLook = obj->m_Look;
	// ターゲットオブジェクト追跡
	switch (m_Phase)
	{
	case StartState::UFO:
		obj->m_Look.x = 230 + a;
		obj->m_Look.y = 100;
		obj->m_Look.z = -150;
		a -= 1.f;
		break;
	case StartState::ENEMY:
		obj->m_Look = 0;
		obj->m_Look.x = -250;
		obj->m_Look.z = 250;
		break;
	case StartState::TEMPLE:
		b--;
		//obj->m_Position.y = 500;
		obj->m_Look.x = 0;
		obj->m_Look.y = 215 + b*2;
		obj->m_Look.z = -370 + -b * 3;
		break;
	case StartState::PLAYER:
		obj->m_Look.z = -80;
		break;
	case StartState::CNT_DOWN:
		obj->m_Look = obj->m_Position = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
		obj->m_Look.y += 10;
		obj->m_LatePosition = obj->m_Position;
		obj->m_LateLook = obj->m_Look;
		break;
	case StartState::END:
		//obj->m_State->ChangeState(obj, GameState::GetInstance());
		break;
	}
	m_PhaseCnt--;

	if (m_Phase < 4)
	{
		if (IsKeyTrigger(VK_RETURN) || PAD->IsButtonsTrigger(XINPUT_GAMEPAD_B))
		{
			while (!m_PhaseQueue.empty())
			{
				m_PhaseQueue.pop();
			}
			m_PhaseQueue.push(END);
			obj->m_Look = obj->m_Position = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Position;
			m_Phase = CNT_DOWN;
			m_PhaseCnt = 190;
			//obj->m_State->ChangeState(obj, GameState::GetInstance());
			return;
		}
	}
	if (m_PhaseCnt < 1)
	{
		if (m_Phase == END)
		{
			obj->m_State->ChangeState(obj, GameState::GetInstance());
			return;
		}
		m_PhaseCnt = 280;
		m_Phase = m_PhaseQueue.front();
		m_PhaseQueue.pop();
		if (m_Phase == TEMPLE)		m_PhaseCnt = 100;
		if (m_Phase == CNT_DOWN)	m_PhaseCnt = 190;
		if (m_Phase == END)			m_PhaseCnt = 60;
	}

	// カメラ位置計算
	float xzRad = obj->m_xzAngle * 3.141592f / 180.0f;
	float yRad = obj->m_yAngle * 3.141592f / 180.0f;

	obj->m_Position.x = (cos(yRad) * sin(xzRad) * obj->m_radius);
	obj->m_Position.z = (cos(yRad) * -cos(xzRad) * obj->m_radius);
	obj->m_Position.y = (sin(yRad) * obj->m_radius);

	obj->m_Position += obj->m_Look;

	// 遅れ表現用の倍率
	float fLate = 1.f;
	Float3 Move;
	// 注視点の遅れ表現
	Move = obj->m_Look - obj->m_LateLook;
	Move *= fLate;
	obj->m_LateLook += Move;

	// カメラ座標の遅れ表現
	Move = obj->m_Position - obj->m_LatePosition;
	Move *= fLate;
	obj->m_LatePosition += Move;

	GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>()->Rotate.y += 20 * 3.141592f / 180;
}

void StartState::ChangeState(Camera *obj, CameraState *newState)
{
	obj->m_State = newState;
	obj->m_State->Init(obj);
}
