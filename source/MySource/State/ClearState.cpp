#include "SelectSceneState.h"
#include "ClearState.h"
#include "GameState.h"
#include "../Camera.h"
#include "../Keyboard.h"
#include "../GameScene.h"
#include "../Transform.h"
#include "../GameScene.h"
#include "../Fly.h"


void ClearState::Init(Camera *obj)
{
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
	obj->m_radius = 100.0f;
}

void ClearState::Update(Camera *obj)
{
	obj->m_LatePosition = obj->m_Position = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Fly>()->m_Transform->Position;
	obj->m_LateLook = obj->m_Look = GameScene::GetObjectList()->Get(OBJECT::BOSS)->Get<Fly>()->m_Transform->Position;
	obj->m_LateLook.z = obj->m_Look.z -= 20;
	//obj->m_Look.x += 1;


	// ƒJƒƒ‰ˆÊ’uŒvŽZ
	float xzRad = obj->m_xzAngle * 3.141592f / 180.0f;
	float yRad = obj->m_yAngle * 3.141592f / 180.0f;

	obj->m_Position.x = (cos(yRad) * sin(xzRad) * obj->m_radius);
	obj->m_Position.z = (cos(yRad) * -cos(xzRad) * obj->m_radius);
	obj->m_Position.y = (sin(yRad) * obj->m_radius);

	obj->m_Position += obj->m_Look;

	// ’x‚ê•\Œ»—p‚Ì”{—¦
	float fLate = 1.f;
	Float3 Move;
	// ’Ž‹“_‚Ì’x‚ê•\Œ»
	Move = obj->m_Look - obj->m_LateLook;
	Move *= fLate;
	obj->m_LateLook += Move;

	// ƒJƒƒ‰À•W‚Ì’x‚ê•\Œ»
	Move = obj->m_Position - obj->m_LatePosition;
	Move *= fLate;
	obj->m_LatePosition += Move;
}

void ClearState::ChangeState(Camera *obj, CameraState *newState)
{
	obj->m_State = newState;
	obj->m_State->Init(obj);
}
