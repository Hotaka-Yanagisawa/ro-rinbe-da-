//=======================================================================
// EnemyManager.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/27	作成
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Object.h"

//--- 定数
#define MAX_ENEMY	(50)	// 画面上に出現する最大数

//--- クラス
class EnemyManager
{
public:
	inline static EnemyManager* GetInstance()
	{
		static EnemyManager instance;
		return &instance;
	}

	void Init();
	void Uninit();

	void Create();
	void Destroy(Object*);

	friend class GameScene;

private:
	EnemyManager() {}
	~EnemyManager() {}

	int m_nCount;

	Object* m_Enemy[MAX_ENEMY];
	bool m_bUse[MAX_ENEMY];
};
