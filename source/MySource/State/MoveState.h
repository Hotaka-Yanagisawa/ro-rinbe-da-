////////////////////////////////////////////////////////////////////////////////////////////
// MoveState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 移動状態に関すること
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "EnemyState.h"

class HierarchyEnemyState;

class MoveState :public EnemyState
{
public:
	static MoveState *GetInstance()
	{
		static MoveState instance;
		return &instance;
	}

	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);
};