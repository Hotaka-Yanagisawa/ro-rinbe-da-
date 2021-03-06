////////////////////////////////////////////////////////////////////////////////////////////
// LoadingState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 纏めて発射される前の状態に関すること
// @Hoist
//-----------------------------------------------------------------------------------------
// 2020/012/03	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "EnemyState.h"
#include "../Transform.h"

class HierarchyEnemyState;

class LoadingState :public EnemyState
{
public:
	static LoadingState *GetInstance()
	{
		static LoadingState instance;
		return &instance;
	}

	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);

private:
	Transform *m_Transform;
	Transform *PlayerTransform;
};