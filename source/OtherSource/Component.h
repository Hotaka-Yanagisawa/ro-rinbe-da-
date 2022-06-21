//=======================================================================
// Component.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/15	作成 Init, Update, Draw
//			18	OnCollision実装
//			23	OnCollisionの引数で衝突相手の識別
//				OnCollisionEnter作成
//			24	Remove用変数, Uninit追加
//
//=======================================================================
#pragma once

//--- 前方宣言
class Object;

//--- クラス
class Component		// コンポーネント基底クラス
{
public:

	Component() {}
	virtual ~Component() {}

	virtual void Init() {}
	virtual void Uninit() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual void OnCollision(Object* pObj) {}
	virtual void OnCollisionEnter(Object* pObj) {}

	Object* m_Parent = nullptr;

	bool m_bRemove = false;
private:

};
