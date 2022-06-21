////////////////////////////////////////////////////////////////////////////////////////////
// HierarchyEnemyState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// State���Ǘ����₷�����邽�ߊK�w���Ƃɕ����钊�ۃN���X
//-----------------------------------------------------------------------------------------
// 2020/11/24	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

//#define DISTANCE (250.0f)

class EnemyPlayer;
class EnemyState;

// �K�w�p����ԁ@�@�@���ۃN���X
class HierarchyEnemyState
{
public:
	virtual ~HierarchyEnemyState() {}

	virtual void Init       (EnemyPlayer *)          = 0;
	virtual void Update     (EnemyPlayer *)          = 0;
	virtual void ChangeState(EnemyPlayer *, EnemyState *) = 0;

protected:
};