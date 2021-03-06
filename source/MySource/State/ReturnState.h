////////////////////////////////////////////////////////////////////////////////////////////
// ReturnState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 後退(帰る)状態に関すること
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "EnemyState.h"
#include "../Transform.h"

class EnemyPlayer;

class ReturnState : public EnemyState
{
public:

	static ReturnState *GetInstance()
	{
		static ReturnState instance;
		return &instance;
	}

	virtual ~ReturnState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:親

private:
	
};