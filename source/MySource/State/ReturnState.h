////////////////////////////////////////////////////////////////////////////////////////////
// ReturnState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ���(�A��)��ԂɊւ��邱��
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:�e

private:
	
};