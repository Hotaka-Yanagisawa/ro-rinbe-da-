////////////////////////////////////////////////////////////////////////////////////////////
// InvasionState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// N—ªó‘Ô‚ÌŠK‘w
//-----------------------------------------------------------------------------------------
// 2020/11/24	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class EnemyPlayer;

// Šª‚«ã‚°ó‘Ô
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

