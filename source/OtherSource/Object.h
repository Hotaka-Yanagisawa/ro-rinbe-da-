//=======================================================================
// Object.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/15	クラス作成 コンポーネント実装
//			20	デフォルトでTransformを持つように設定
//			23	コンポーネント除外処理追加
//			24	↑の不具合修正			
//
//=======================================================================
#pragma once

//--- インクルード
#include "Component.h"
#include "Transform.h"
#include <list>

//--- 定数
namespace OBJECT
{
	enum TYPE	// 種類
	{
		NO = -1,
		PLAYER,	// 主人公
		ENEMY1,	// 敵中
		ENEMY2,	// 敵小
		ENEMY3,	// 敵大
		TREE,	// 木
		ROCK,	// 石
		BTREE,	// 後ろの木
		BOSS,	// 母艦
		FIELD,	// 地面
		//--- 神殿
		TEMPLE,	// 本体
		PILLAR,	// 柱
		CORE,	// コア
		FLOOR1,	// 床上
		FLOOR2,	// 床中
		FLOOR3,	// 床下
		BACK,	// 背景

		MAX
	};
}

//--- クラス
class Object
{
public:
	Object() { this->Add<Transform>(); }
	~Object() { m_List.clear(); }

	// 更新
	void Update()
	{
		// 削除
		for (auto it = m_List.begin(); it != m_List.end(); )
		{
			if ((*it)->m_bRemove)
			{
				(*it)->Uninit();
				delete *it;
				it = m_List.erase(it);
				continue;
			}
			it++;
		}
		// 更新
		for (auto i : m_List) i->Update();
	}
	// 描画
	void Draw() { for (auto i : m_List) i->Draw(); }
	// 衝突時
	void OnCollision(Object* pObj) { for (auto i : m_List) i->OnCollision(pObj); }
	void OnCollisionEnter(Object* pObj) { for (auto i : m_List) i->OnCollisionEnter(pObj); }

	// 追加
	template<class T>
	T* Add()
	{
		T* com = new T();
		com->m_Parent = this;
		m_List.push_back(com);
		com->Init();
		return com;
	}

	// 取得
	template<class T>
	T* Get()
	{
		for (auto i : m_List)
		{
			T* com = dynamic_cast<T*>(i);
			if (com != nullptr) return com;
		}
		return nullptr;
	}

	// 削除
	//void Remove(Component* com)
	//{
	//	com->m_bRemove = true;
	//}

	// リスト
	std::list<Component*> m_List;		// 更新対象

	// タグ
	OBJECT::TYPE m_Tag = OBJECT::NO;

	// 当たってる
	bool m_bHit = false;
	// 除外対象
	bool m_bRemove = false;

private:

};
