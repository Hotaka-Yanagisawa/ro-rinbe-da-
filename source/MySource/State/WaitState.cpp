////////////////////////////////////////////////////////////////////////////////////////////
// WaitState.cpp
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 待機状態に関すること
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "WaitState.h"
//#include "MoveState.h"
//#include "Enemy.h"
#include "HierarchyEnemyState.h"
#include "EnemyPlayer.h"
#include "../Object.h"
#include "../Field.h"


void WaitState::Init(EnemyPlayer *obj)
{
	obj->GetTransform()->Move = 0;
	obj->SetNewTransformRotate(0, 0, 0);
	obj->m_nReuseCnt = (rand() % 5 + 5) * 60;
}

void WaitState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	//木に使うかもエネミーじゃないけど
	//使いまわす


	if (obj->m_Parent->m_Tag == OBJECT::TREE)
	{
		return;
	}

	if ((obj->m_Parent->m_Tag == OBJECT::ENEMY1)
		|| (obj->m_Parent->m_Tag == OBJECT::ENEMY2)
		|| (obj->m_Parent->m_Tag == OBJECT::ENEMY3))
	{
		//if (EnemyPlayer::m_ReuseQueue.front() != obj)		return;
		//else		cnt++;

		if (!EnemyPlayer::m_ReuseQueue.empty())
		{
			if (obj->m_nReuseCnt < 1)	
			{
				float r = rand() % 150 + FIELD_RANGE;
				float Angle = rand() * (3.141529f * 180.0f);
				Float3 Position = { cosf(Angle) * r, 0, sinf(Angle) * r };
				//std::pair<float, float> pair = RecalculationMacro(RecalculationMacro(), RecalculationMacro());
				obj->Init();
				obj->GetTransform()->Position = Position;
				EnemyPlayer::m_ReuseQueue.pop();
			}
			else
			{
				obj->m_nReuseCnt--;
			}
		}
	}
}
