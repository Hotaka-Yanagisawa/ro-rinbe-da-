////////////////////////////////////////////////////////////////////////////////////////////
// WindState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 巻き上げている状態に関すること
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

class WindState : public EnemyState
{
public:

	static WindState *GetInstance()
	{
		static WindState instance;
		return &instance;
	}

	virtual ~WindState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:親
	void Fire(EnemyPlayer *obj);
	void Loading(EnemyPlayer *obj);

private:
	Transform *m_Transform;
	Transform *PlayerTransform;

	float m_fIntervalCnt;
	bool m_bIntervalFlag;
};

