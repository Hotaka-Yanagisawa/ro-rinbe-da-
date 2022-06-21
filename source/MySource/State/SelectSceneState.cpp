#include "SelectSceneState.h"
#include "StartState.h"
#include "../Camera.h"
#include "../SceneManager.h"

void SelectSceneState::Init(Camera *obj)
{

	//obj->m_Position = (0, 0, -60);
	//obj->m_Look = (0, 0, 0);
	//obj->m_LateLook = obj->m_Look;
	//obj->m_Angle = 60.0f;
	//obj->m_xzAngle = 0.0f;
	//obj->m_yAngle = 10.0f;
	//obj->Bind(false);
	obj->m_Position = { 0, 0, -90 };
	obj->m_Look = 0;
	obj->m_Up = { 0, 1, 0 };
	obj->m_LatePosition = obj->m_Position;
	obj->m_LateLook = obj->m_Look;
	obj->m_Angle = 60.0f;
	obj->m_Near = 0.5f;
	obj->m_Far = 300.0f;
	obj->m_xzAngle = 0.0f;
	obj->m_yAngle = 10.0f;
	obj->m_radius = 35.0f;
	obj->m_pTarget = nullptr;
}

void SelectSceneState::Update(Camera *obj)
{
	if (SceneManager::GetInstance()->GetCurrentScene() == SCENE::TYPE::GAME)
	{
		ChangeState(obj, StartState::GetInstance());
	}
}

void SelectSceneState::ChangeState(Camera *obj, CameraState *newState)
{
	obj->m_State = newState;
	obj->m_State->Init(obj);
}
