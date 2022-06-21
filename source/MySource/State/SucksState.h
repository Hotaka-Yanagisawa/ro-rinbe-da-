////////////////////////////////////////////////////////////////////////////////////////////
// SucksState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ‘Ò‹@ó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:e

private:
	Transform *PlayerTransform;
	
};