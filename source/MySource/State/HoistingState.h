////////////////////////////////////////////////////////////////////////////////////////////
// HoistingState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �����グ��Ԃ̊K�w
//-----------------------------------------------------------------------------------------
// 2020/11/24	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class EnemyPlayer;

// �����グ���
class HoistingState : public HierarchyEnemyState
{
public:
	static HoistingState *GetInstance()
	{
		static HoistingState instance;
		return &instance;
	}

	virtual void Init       (EnemyPlayer *);
	virtual void Update     (EnemyPlayer *);
	virtual void ChangeState(EnemyPlayer *, EnemyState *);

private:
	HoistingState() {}
};

