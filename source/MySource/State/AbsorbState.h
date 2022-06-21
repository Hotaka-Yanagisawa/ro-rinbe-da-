////////////////////////////////////////////////////////////////////////////////////////////
// AbsorbState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// エネルギー吸収状態に関すること
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "EnemyState.h"
#include "../Vitality.h"

class EnemyPlayer;

class AbsorbState : public EnemyState
{
public:

	static AbsorbState *GetInstance()
	{
		static AbsorbState instance;
		return &instance;
	}

	virtual ~AbsorbState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:親

private:

	Vitality *TempleVitality;
};