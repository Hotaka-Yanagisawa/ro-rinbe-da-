//=======================================================================
// Collision.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/12	授業内のを書き換え
//			19	プレイヤー主体な判定の取り方 仮
//			23	戻した
//			27	やっぱり戻した (当たり判定管理クラス)
//			
//=======================================================================
#pragma once

//--- インクルード部
#include "Object.h"
#include "Collider.h"

class Collision
{
public:

	inline static Collision* GetInstance()
	{
		static Collision instance;
		return &instance;
	}

	void Init();
	void Uninit();

	void Update();

	void Add(Collider*);

private:

	bool CheckCollision(Object*&, Object*&);

	std::list<Collider*> m_List;
};
