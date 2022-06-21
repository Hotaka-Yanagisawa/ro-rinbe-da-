//改善の余地あり

#include "SucksState.h"
#include "WindState.h"
#include "MoveState.h"
#include "ReturnState.h"
#include "EnemyPlayer.h"
#include "InvasionState.h"
#include "../GameScene.h"


void SucksState::Init(EnemyPlayer *obj)
{
	obj->m_bPlusOrMinusX = false;
	obj->m_bPlusOrMinusZ = false;

	float ex = obj->GetTransform()->Position.x;
	float ez = obj->GetTransform()->Position.z;

	PlayerTransform = GameScene::GetObjectList()->Get(OBJECT::PLAYER)->Get<Transform>();
	float px = PlayerTransform->Position.x;
	float pz = PlayerTransform->Position.z;

	obj->m_DistanceX = ex - px;
	obj->m_DistanceZ = ez - pz;

	if (obj->m_DistanceX > 0) obj->m_bPlusOrMinusX = true;
	if (obj->m_DistanceZ > 0)obj->m_bPlusOrMinusZ = true;
}

void SucksState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	//ざっくり説明
	//吸い込みによってトルネードとエネミーが近くに来ると次のステートへ→WindState
	if (fabsf(obj->m_DistanceX) + fabsf(obj->m_DistanceZ) > 1.5f)
	{
		if (obj->m_bPlusOrMinusX)
		{
			obj->m_DistanceX -= 0.2f;
			if (obj->m_DistanceX < 0)
			{
				obj->m_DistanceX = 0;
			}
		}
		else
		{
			obj->m_DistanceX += 0.2f;
			if (obj->m_DistanceX > 0)
			{
				obj->m_DistanceX = 0;
			}
		}

		if (obj->m_bPlusOrMinusZ)
		{
			obj->m_DistanceZ -= 0.2f;
			if (obj->m_DistanceZ < 0)
			{
				obj->m_DistanceZ = 0;
			}
		}
		else
		{
			obj->m_DistanceZ += 0.2f;
			if (obj->m_DistanceZ > 0)
			{
				obj->m_DistanceZ = 0;
			}
		}

		obj->GetTransform()->Position.x = PlayerTransform->Position.x + obj->m_DistanceX;
		obj->GetTransform()->Position.z = PlayerTransform->Position.z + obj->m_DistanceZ;
	}
	else
	{
		float Capa;
		Capa = EnemyPlayer::m_fCapa + obj->m_fWeight;
		//重量120まで巻き上げられる
		if (Capa > 120)
		{
			if (obj->GetAbsorbTotal() < 1.0f)
			{
				obj->SetHierarchyState(InvasionState::GetInstance());
				obj->SetState(MoveState::GetInstance());
			}
			else
			{
				obj->SetHierarchyState(InvasionState::GetInstance());
				obj->SetState(ReturnState::GetInstance());
			}

			return;
		}

		parent->ChangeState(obj, WindState::GetInstance());
	}
}
