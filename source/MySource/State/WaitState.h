////////////////////////////////////////////////////////////////////////////////////////////
// WaitState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �ҋ@��ԂɊւ��邱��
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:�e

private:
};