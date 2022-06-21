////////////////////////////////////////////////////////////////////////////////////////////
// ReturnState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// Œã‘Ş(‹A‚é)ó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:e

private:
	
};