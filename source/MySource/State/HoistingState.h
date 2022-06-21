////////////////////////////////////////////////////////////////////////////////////////////
// HoistingState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// Šª‚«ã‚°ó‘Ô‚ÌŠK‘w
//-----------------------------------------------------------------------------------------
// 2020/11/24	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyEnemyState.h"

class EnemyPlayer;

// Šª‚«ã‚°ó‘Ô
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

