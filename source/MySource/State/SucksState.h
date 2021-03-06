////////////////////////////////////////////////////////////////////////////////////////////
// SucksState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 待機状態に関すること
// @Hoisting
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "EnemyState.h"
#include "../Transform.h"

class EnemyPlayer;

class SucksState : public EnemyState
{
public:

	static SucksState *GetInstance()
	{
		static SucksState instance;
		return &instance;
	}

	virtual ~SucksState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:親

private:
	Transform *PlayerTransform;
	
};