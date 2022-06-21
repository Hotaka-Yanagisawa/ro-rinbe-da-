////////////////////////////////////////////////////////////////////////////////////////////
// LoadingState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Z�߂Ĕ��˂����O�̏�ԂɊւ��邱��
// @Hoist
//-----------------------------------------------------------------------------------------
// 2020/012/03	�쐬
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