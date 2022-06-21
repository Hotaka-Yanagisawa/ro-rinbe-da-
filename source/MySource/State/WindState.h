////////////////////////////////////////////////////////////////////////////////////////////
// WindState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// Šª‚«ã‚°‚Ä‚¢‚éó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
// @Hoisting
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:e
	void Fire(EnemyPlayer *obj);
	void Loading(EnemyPlayer *obj);

private:
	Transform *m_Transform;
	Transform *PlayerTransform;

	float m_fIntervalCnt;
	bool m_bIntervalFlag;
};

