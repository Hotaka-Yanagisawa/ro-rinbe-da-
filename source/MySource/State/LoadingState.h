////////////////////////////////////////////////////////////////////////////////////////////
// LoadingState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// “Z‚ß‚Ä”­Ë‚³‚ê‚é‘O‚Ìó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
// @Hoist
//-----------------------------------------------------------------------------------------
// 2020/012/03	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "EnemyState.h"
#include "../Transform.h"

class HierarchyEnemyState;

class LoadingState :public EnemyState
{
public:
	static LoadingState *GetInstance()
	{
		static LoadingState instance;
		return &instance;
	}

	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);

private:
	Transform *m_Transform;
	Transform *PlayerTransform;
};