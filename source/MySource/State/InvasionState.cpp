#include "InvasionState.h"
#include "WaitState.h"
#include "EnemyPlayer.h"
#include "MoveState.h"
#include "../Object.h"


void InvasionState::Init(EnemyPlayer *obj)
{
	switch (obj->m_Parent->m_Tag)
	{
	case OBJECT::ENEMY1:
	case OBJECT::ENEMY2:
	case OBJECT::ENEMY3:
		ChangeState(obj, MoveState::GetInstance());
		break;
	case OBJECT::TREE:
		ChangeState(obj, WaitState::GetInstance());
		break;
	}
}

void InvasionState::Update(EnemyPlayer *obj)
{
	obj->GetState()->Update(obj, InvasionState::GetInstance());
}

void InvasionState::ChangeState(EnemyPlayer *obj, EnemyState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}
