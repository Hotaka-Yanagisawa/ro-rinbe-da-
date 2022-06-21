////////////////////////////////////////////////////////////////////////////////////////////
// MoveState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ˆÚ“®ó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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