////////////////////////////////////////////////////////////////////////////////////////////
// FireState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 発射状態に関すること
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "EnemyState.h"

class EnemyPlayer;

class FireState : public EnemyState
{
public:

	static FireState *GetInstance()
	{
		static FireState instance;
		return &instance;
	}

	virtual ~FireState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:親

	void Fire(EnemyPlayer *obj);
private:

};