//=======================================================================
// ObjectList.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/15	クラス作成
//			16	Add, Update, DrawをObjectからコピー
//				Addの仕様を変更 → Create
//			17	OBJECT::TYPE追加
//			18	FIELDとか追加したけど別のところに書きたい　/21 移した
//			22	Destroy実装
//			28	生成後すぐリストに追加しないパターン実装
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Object.h"
#include <list>

//--- クラス
class ObjectList
{
public:

	ObjectList() {}
	~ObjectList() { m_List.clear(); }

	void Update();
	void Draw();

	// 生成
	Object* Create(OBJECT::TYPE, bool Push = true);
	void Add(Object*);

	// 取得
	Object* Get(OBJECT::TYPE);

	// 消去
	void Destroy(Object* pObj);

	// リスト
	std::list<Object*> m_List;

private:

};
