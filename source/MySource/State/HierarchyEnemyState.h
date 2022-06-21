////////////////////////////////////////////////////////////////////////////////////////////
// HierarchyEnemyState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// Stateを管理しやすくするため階層ごとに分ける抽象クラス
//-----------------------------------------------------------------------------------------
// 2020/11/24	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

//#define DISTANCE (250.0f)

class EnemyPlayer;
class EnemyState;

// 階層用基底状態　　　抽象クラス
class HierarchyEnemyState
{
public:
	virtual ~HierarchyEnemyState() {}

	virtual void Init       (EnemyPlayer *)          = 0;
	virtual void Update     (EnemyPlayer *)          = 0;
	virtual void ChangeState(EnemyPlayer *, EnemyState *) = 0;

protected:
};