////////////////////////////////////////////////////////////////////////////////////////////
// FireState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ���ˏ�ԂɊւ��邱��
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:�e

	void Fire(EnemyPlayer *obj);
private:

};