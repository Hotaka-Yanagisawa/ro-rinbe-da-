////////////////////////////////////////////////////////////////////////////////////////////
// WaitState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ‘Ò‹@ó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:e

private:
};