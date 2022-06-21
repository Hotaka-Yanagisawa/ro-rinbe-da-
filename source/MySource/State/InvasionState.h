////////////////////////////////////////////////////////////////////////////////////////////
// InvasionState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �N����Ԃ̊K�w
//-----------------------------------------------------------------------------------------
// 2020/11/24	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class EnemyPlayer;

// �����グ���
class InvasionState : public HierarchyEnemyState
{
public:
	static InvasionState *GetInstance()
	{
		static InvasionState instance;
		return &instance;
	}

	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *);
	virtual void ChangeState(EnemyPlayer *, EnemyState *);

private:
	InvasionState() {}
};

