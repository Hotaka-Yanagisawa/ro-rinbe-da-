////////////////////////////////////////////////////////////////////////////////////////////
// FireState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ”­Ëó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:e

	void Fire(EnemyPlayer *obj);
private:

};