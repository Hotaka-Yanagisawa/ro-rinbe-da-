#include "FireState.h"
#include "EnemyPlayer.h"
#include "InvasionState.h"
#include "MoveState.h"
#include "ReturnState.h"
#include "../Object.h"
#include "WaitState.h"
#include "../EnemyManager.h"

void FireState::Init(EnemyPlayer *obj)
{
	obj->GetTransform()->Move = 0;
	obj->m_bUse = true;
	EnemyPlayer::MyNum--;
	obj->m_bESC = false;

}

void FireState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	//”­ŽËŽž‚Ìˆ—‚ðs‚¤
	if (obj->m_bUse)
	{
		obj->GetTransform()->Move.y = 3.0f + rand() % 10 / 10.0f;
		obj->m_bUse = false;
		if (obj->m_Parent->m_Tag == OBJECT::TREE)
		{
			obj->GetTransform()->Rotate.x = (rand() % 40 + 190) * 3.14f / 180.0f;
			//obj->GetTransform()->Rotate.z = (rand() % 40 + 160) * 3.14f / 180.0f;
		}
	}

	if (obj->GetTransform()->Move.y <= 0 && obj->GetTransform()->Position.y <= 4.0f)
	{
		obj->GetTransform()->Position.y = 0;
		//obj->m_bUse = true;
		if (obj->GetAbsorbTotal() < 1.0f)
		{
			switch (obj->m_Parent->m_Tag)
			{
			case OBJECT::ENEMY1:
			case OBJECT::ENEMY2:
			case OBJECT::ENEMY3:
				obj->m_Transform->Position = obj->SetNewTransformPos(999, 0, 999);
				EnemyPlayer::m_ReuseQueue.push(obj);
				parent->ChangeState(obj, WaitState::GetInstance());

				//obj->SetState(obj, WaitState::GetInstance());
				//m_State = WaitState::GetInstance();
				//m_State->Init(this);
				//EnemyManager::GetInstance()->Destroy(obj->m_Parent);

				//obj->SetHierarchyState(InvasionState::GetInstance());
				//parent->ChangeState(obj, MoveState::GetInstance());
				break;
			case OBJECT::TREE:
				//obj->SetHierarchyState(InvasionState::GetInstance());
				//parent->ChangeState(obj, WaitState::GetInstance());
				break;
			}
			
		}
		else
		{
			switch (obj->m_Parent->m_Tag)
			{
			case OBJECT::ENEMY1:
			case OBJECT::ENEMY2:
			case OBJECT::ENEMY3:
				obj->m_Transform->Position = obj->SetNewTransformPos(999, 0, 999);
				EnemyPlayer::m_ReuseQueue.push(obj);
				parent->ChangeState(obj, WaitState::GetInstance());

				//EnemyManager::GetInstance()->Destroy(obj->m_Parent);
				//obj->SetHierarchyState(InvasionState::GetInstance());
				//parent->ChangeState(obj, ReturnState::GetInstance());
				break;
			case OBJECT::TREE:
				//obj->GetTransform()->Rotate.x = (rand() % 40 + 160) * 3.14f / 180.0f;
				//obj->SetHierarchyState(InvasionState::GetInstance());
				//parent->ChangeState(obj, WaitState::GetInstance());
				break;
			}
		}
	}
}

