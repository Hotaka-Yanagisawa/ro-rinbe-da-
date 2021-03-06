////////////////////////////////////////////////////////////////////////////////////////////
// WaitState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 待機状態に関すること
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "EnemyState.h"

class EnemyPlayer;

class WaitState : public EnemyState
{
public:

	static WaitState *GetInstance()
	{
		static WaitState instance;
		return &instance;
	}

	virtual ~WaitState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:親

private:
};