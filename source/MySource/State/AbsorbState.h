////////////////////////////////////////////////////////////////////////////////////////////
// AbsorbState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �G�l���M�[�z����ԂɊւ��邱��
// @Invasion
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "EnemyState.h"
#include "../Vitality.h"

class EnemyPlayer;

class AbsorbState : public EnemyState
{
public:

	static AbsorbState *GetInstance()
	{
		static AbsorbState instance;
		return &instance;
	}

	virtual ~AbsorbState() {}
	virtual void Init(EnemyPlayer *);
	virtual void Update(EnemyPlayer *, HierarchyEnemyState *parent);	//parent:�e

private:

	Vitality *TempleVitality;
};