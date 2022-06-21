////////////////////////////////////////////////////////////////////////////////////////////
// WindState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �����グ�Ă����ԂɊւ��邱��
// @Hoisting
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:�e
	void Fire(EnemyPlayer *obj);
	void Loading(EnemyPlayer *obj);

private:
	Transform *m_Transform;
	Transform *PlayerTransform;

	float m_fIntervalCnt;
	bool m_bIntervalFlag;
};

